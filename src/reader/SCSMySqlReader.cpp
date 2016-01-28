#include <vector>
#include <string>
#include <algorithm>

#include "SCSMySqlReader.h"
#include "SCSPreparedSQLSet.h"
#include "util/SCSMySqlHelper.h"
#include "util/SCSConfigHelper.h"
#include "util/SCSUtilTools.h"

#include "DBLog.h"
#include "SCSGetFileRecord.h"

using namespace std;

bool CSCSMySqlReader::ReadNextTestCase(CSCSPreparedSQLSet &set)
{

    const STConfig *config = CSCSConfigHelper::GetInstance()->GetConfig();
    std::string msg;
    if(!mysql->IsConnect())
    {
        if (!mysql->ConnMySql(config->conCaseMysqlConnect.strIP.c_str(),
                             config->conCaseMysqlConnect.nPort,
                             config->conCaseMysqlConnect.strUser.c_str(),
                             config->conCaseMysqlConnect.strPwd.c_str(),
                             config->conCaseMysqlConnect.strDataBase.c_str(),
                             "UTF8",
                             msg))
        {
            LOG_ERROR(("open testcase srcMysql err:" + msg).c_str());
            return false;
        }
    }
    vector<vector<string> > testTable;
    vector<string> modules(SCSUtilTools::split(config->strModules, ","));

    string casesql = "select * from caseslist";
    casesql += " where caseid>" + SCSUtilTools::NumberToString(nTestCaseId);
    //按模块取出要执行的用例
    if (modules.end() == find(modules.begin(), modules.end(), "all"))
    {
        casesql += " and  modules in ('";
        casesql += SCSUtilTools::join(modules, "','");
        casesql += "')";
    }
    //每次取出一条
    casesql += " LIMIT 1";

    LOG_DEBUG(casesql.c_str());

    if (!mysql->Select(casesql.c_str(), &testTable, msg))
    {
        LOG_ERROR(("select caseslist err:" + msg).c_str());
        return false;
    }

    if (testTable.size() <= 1)
    {
        return false;
    }
    //获取用例
    vector<string> vecSrcCase;
    GetTestCase("mysqlcases", testTable, vecSrcCase);
    vector<string> vecDesCase;
    GetTestCase("scsdbcases", testTable, vecDesCase);
    //读取相关测试用例信息
    bool checkSequence = testTable[1][SCSUtilTools::GetColumnIndex("sequence_match", testTable[0])] == "1";
    std::string strModule = testTable[1][SCSUtilTools::GetColumnIndex("modules", testTable[0])];
    int nExecTimes = SCSUtilTools::StringToNumber<int>(
            testTable[1][SCSUtilTools::GetColumnIndex("cases_execution_times", testTable[0])]);
    bool checkDataNodes = testTable[1][SCSUtilTools::GetColumnIndex("datanodes_check", testTable[0])] == "1";
    bool init = testTable[1][SCSUtilTools::GetColumnIndex("init", testTable[0])] == "1";
    nTestCaseId = SCSUtilTools::StringToNumber<int>(testTable[1][SCSUtilTools::GetColumnIndex("caseid", testTable[0])]);
    std::string strSCSInit=testTable[1][SCSUtilTools::GetColumnIndex("scsdb_init",testTable[0])];
    std::string strMySqlInit=testTable[1][SCSUtilTools::GetColumnIndex("mysql_init",testTable[0])];

    //获取初始化语句
    if(init)
    {
        vector<string> vecPath= SCSUtilTools::split(strMySqlInit," ");
        if(vecPath.size()<=1)
        {
            return false;
        }
        std::string sourcePath=vecPath[1];
        if(sourcePath.empty())
        {
            return false;
        }
        CSCSGetFileRecord sourceRecord(sourcePath.c_str());
        if(sourceRecord.Init()!=0)
        {
            LOG_ERROR("MySqlReader reade mysql source file erro");
            return false;
        }
        std::string sql;
        std::string strMysqlsource;
        while (sourceRecord.GetSqlRecord(sql)==0)
        {
            strMysqlsource+=sql;
            strMysqlsource+=";";
        }
        vecSrcCase.insert(vecSrcCase.begin(),strMysqlsource);
        vecDesCase.insert(vecDesCase.begin(),strSCSInit);
    }

    set = CSCSPreparedSQLSet(0,vecSrcCase.size(),checkSequence,strModule,nExecTimes,checkDataNodes,init,nTestCaseId,vecSrcCase,vecDesCase);
    //获取用例总数
    vector<vector<string> > countTestTable;
    string countSql="select count(*) from caseslist";
    if (modules.end() == find(modules.begin(), modules.end(), "all"))
    {
        countSql += " modules in ('";
        countSql += SCSUtilTools::join(modules, "','");
        countSql += "')";
    }
    if(!mysql->Select(countSql.c_str(),&countTestTable,msg))
    {
        LOG_ERROR("count caseslist err");
        return false;
    }
    nTestCaseTotal=SCSUtilTools::StringToNumber<int>(countTestTable[1][0]);
    nTestCaseIndex++;
    return true;
}

bool CSCSMySqlReader::GetTestCase(const std::string &column, const std::vector<std::vector<std::string> > &vecTestTable,
                                  std::vector<std::string> &vecTestCase)
{
    int scsdbcaseIndex = SCSUtilTools::GetColumnIndex(column, vecTestTable[0]);
    if (scsdbcaseIndex == -1)
    {
        return false;
    }
    vecTestCase = SCSUtilTools::split(vecTestTable[1][scsdbcaseIndex], "###");

    return true;
}

CSCSMySqlReader::CSCSMySqlReader() : nTestCaseId(0),nTestCaseTotal(0),nTestCaseIndex(0),mysql(new CSCSMySqlHelper())
{

}

CSCSMySqlReader::~CSCSMySqlReader()
{
    mysql->CloseMySql();
}


int CSCSMySqlReader::GetTestCaseTotal()
{
    return nTestCaseTotal;
}

int CSCSMySqlReader::GetTestCaseIndex()
{
    return nTestCaseIndex;
}

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

    if (modules.end() == find(modules.begin(), modules.end(), "all"))
    {
        casesql += " and  modules in ('";
        casesql += SCSUtilTools::join(modules, "','");
        casesql += "')";
    }

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

    vector<string> vecSrcCase;
    GetTestCase("mysqlcases", testTable, vecSrcCase);
    vector<string> vecDesCase;
    GetTestCase("scsdbcases", testTable, vecDesCase);

    bool checkSequence = testTable[1][SCSUtilTools::GetColumnIndex("sequence_match", testTable[0])] == "1";
    std::string strModule = testTable[1][SCSUtilTools::GetColumnIndex("modules", testTable[0])];
    int nExecTimes = SCSUtilTools::StringToNumber<int>(
            testTable[1][SCSUtilTools::GetColumnIndex("cases_execution_times", testTable[0])]);
    bool checkDataNodes = testTable[1][SCSUtilTools::GetColumnIndex("datanodes_check", testTable[0])] == "1";
    bool init = testTable[1][SCSUtilTools::GetColumnIndex("init", testTable[0])] == "1";
    nTestCaseId = SCSUtilTools::StringToNumber<int>(testTable[1][SCSUtilTools::GetColumnIndex("caseid", testTable[0])]);
    std::string strSCSInit=testTable[1][SCSUtilTools::GetColumnIndex("scsdb_init",testTable[0])];
    std::string strMySqlInit=testTable[1][SCSUtilTools::GetColumnIndex("mysql_init",testTable[0])];

    if(init)
    {
        std::string sourcePath= SCSUtilTools::split(strMySqlInit," ")[1];
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

CSCSMySqlReader::CSCSMySqlReader() : nTestCaseId(0),mysql(new CSCSMySqlHelper())
{

}

CSCSMySqlReader::~CSCSMySqlReader()
{

}




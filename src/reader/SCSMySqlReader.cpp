#include <vector>
#include <string>
#include <algorithm>

#include "SCSMySqlReader.h"
#include "SCSPreparedSQLSet.h"
#include "util/SCSMySqlHelper.h"
#include "util/SCSConfigHelper.h"
#include "util/SCSUtilTools.h"

#include "DBLog.h"

using namespace std;

bool CSCSMySqlReader::ReadNextTestCase(CSCSPreparedSQLSet &set)
{
	CSCSMySqlHelper mysql;
	const STConfig *config =CSCSConfigHelper::GetInstance()->GetConfig();
	std::string msg;

	if(!mysql.ConnMySql(config->conCaseMysqlConnect.strIP.c_str(),
					config->conCaseMysqlConnect.nPort,
					config->conCaseMysqlConnect.strUser.c_str(),
					config->conCaseMysqlConnect.strPwd.c_str(),
					config->conCaseMysqlConnect.strDataBase.c_str(),
					"UTF8",
					msg))
	{
		LOG_ERROR(("open testcase srcMysql err:"+msg).c_str());
		return false;
	}

	vector<vector<string> > testTable;
	vector<string> modules(SCSUtilTools::split(config->strModules,","));

	string casesql = "select * from caseslist";
	casesql += " where caseid>"+SCSUtilTools::NumberToString(nTestCaseId);

	if(modules.end()==find(modules.begin(),modules.end(),"all"))
	{
		casesql +=" and  modules in ('";
		casesql += SCSUtilTools::join(modules,"','");
		casesql +="')";
	}
	
	casesql+=" LIMIT 1";

	LOG_DEBUG(casesql.c_str());

	if(!mysql.Select(casesql.c_str(),&testTable,msg))
	{
		LOG_ERROR(("select caseslist err:"+msg).c_str());
		return false;
	}

	if(testTable.size()<=1)
	{
		return false;
	}
	
	vector<string> vecSrcCase ;
	GetTestCase("scsdbcases",testTable,vecSrcCase);
	vector<string> vecDesCase;
	GetTestCase("mysqlcases",testTable,vecDesCase);

	bool checkSequence=testTable[1][SCSUtilTools::GetColumnIndex("sequence_match",testTable[0])]=="1";
	std::string  strModule=testTable[1][SCSUtilTools::GetColumnIndex("modules",testTable[0])];
	int nExecTimes=SCSUtilTools::StringToNumber<int>(testTable[1][SCSUtilTools::GetColumnIndex("cases_execution_times",testTable[0])]);
	bool checkDataNodes=testTable[1][SCSUtilTools::GetColumnIndex("datanodes_check",testTable[0])]=="1";
	bool init = testTable[1][SCSUtilTools::GetColumnIndex("init",testTable[0])]=="1";
	nTestCaseId=SCSUtilTools::StringToNumber<int>(testTable[1][SCSUtilTools::GetColumnIndex("caseid",testTable[0])]);

	set = CSCSPreparedSQLSet(vecSrcCase,vecDesCase,checkSequence,strModule,nExecTimes,checkDataNodes,init);

	return true;
}

bool CSCSMySqlReader::GetTestCase( const std::string &column,const std::vector<std::vector<std::string> > &vecTestTable,std::vector<std::string> &vecTestCase )
{
	int scsdbcaseIndex=SCSUtilTools::GetColumnIndex(column,vecTestTable[0]);
	if(scsdbcaseIndex==-1)
	{
		return false;
	}
	vecTestCase = SCSUtilTools::split(vecTestTable[1][scsdbcaseIndex],"###");

	return true;
}

CSCSMySqlReader::CSCSMySqlReader():nTestCaseId(0)
{

}

CSCSMySqlReader::~CSCSMySqlReader()
{

}




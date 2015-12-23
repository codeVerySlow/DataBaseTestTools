#include <vector>
#include <string>
#include <algorithm>

#include "SCSMySqlReader.h"
#include "SCSPreparedSQLSet.h"
#include "util/SCSMySqlHelper.h"
#include "util/SCSConfigHelper.h"
#include "util/SCSUtilTools.h"

using namespace std;

bool CSCSMySqlReader::ReadNextTestCase(CSCSPreparedSQLSet *set)
{
	CSCSMySqlHelper mysql;
	const STConfig *config =CSCSConfigHelper::GetInstance()->GetConfig();
	std::string msg;

	if(!mysql.ConnMySql(config->conSrcMysqlConnect.strIP.c_str(),
					SCSUtilTools::StringToNumber<int>(config->conSrcMysqlConnect.strPort),
					config->conSrcMysqlConnect.strUser.c_str(),
					config->conSrcMysqlConnect.strPwd.c_str(),
					config->conSrcConnect.strDataBase.c_str(),
					"UTF8",
					msg))
	{
		std::cerr<< "open testcase srcMysql err:" << msg;
		return false;
	}

	vector<vector<string> > testTable;
	string casesql = "Select * from caseslist where modules in ('";
	casesql += SCSUtilTools::join(SCSUtilTools::split(config->strModules,','),"','");
	casesql += "') and caseid>"+SCSUtilTools::NumberToString(nTestCaseId)+" LIMIT 1";

	std::cout << casesql << std::endl;

	if(!mysql.Select(casesql.c_str(),&testTable,msg))
	{
		std::cerr<<"select caseslist err:"<<msg;
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

	if(NULL != set)
	{
		delete set;
	}

	bool checkSequence=testTable[1][GetColumnIndex("sequence_match",testTable[0])]=="1";
	std::string  strModule=testTable[1][GetColumnIndex("modules",testTable[0])];
	int nExecTimes=SCSUtilTools::StringToNumber<int>(testTable[1][GetColumnIndex("cases_execution_times",testTable[0])]);
	bool checkDataNodes=testTable[1][GetColumnIndex("datanodes_check",testTable[0])]=="1";
	bool init = testTable[1][GetColumnIndex("init",testTable[0])]=="1";
	nTestCaseId=SCSUtilTools::StringToNumber<int>(testTable[1][GetColumnIndex("caseid",testTable[0])]);

	set = new CSCSPreparedSQLSet(vecSrcCase,vecDesCase,checkSequence,strModule,nExecTimes,checkDataNodes,init);

	return true;
}

bool CSCSMySqlReader::GetTestCase( const std::string &column,const std::vector<std::vector<std::string> > &vecTestTable,std::vector<std::string> &vecTestCase )
{
	int scsdbcaseIndex=GetColumnIndex(column,vecTestTable[0]);
	if(scsdbcaseIndex==-1)
	{
		return false;
	}
	vecTestCase = SCSUtilTools::split(vecTestTable[1][scsdbcaseIndex],',');

	return true;
}

CSCSMySqlReader::CSCSMySqlReader():nTestCaseId(0)
{

}

CSCSMySqlReader::~CSCSMySqlReader()
{

}

int CSCSMySqlReader::GetColumnIndex( const string &column,const vector<string> &vecTestColumn )
{
	vector<string>::const_iterator it = find(vecTestColumn.begin(),vecTestColumn.end(),column);

	if(it == vecTestColumn.end())
	{
		std::cerr<<"read testcase srcMysql err:can't find column"+column<<std::endl;
		return -1;
	}

	unsigned int scsdbcaseIndex = it - vecTestColumn.begin();

	if(scsdbcaseIndex >= vecTestColumn.size())
	{
		std::cerr<<"read testcase srcMysql err:can't find column"+column<<std::endl;
		return -1;
	}

	return scsdbcaseIndex;
}


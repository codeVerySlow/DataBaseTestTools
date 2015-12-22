#include <vector>
#include <string>

#include "SCSMySqlReader.h"
#include "SCSMySqlHelper.h"
#include "SCSConfigHelper.h"
#include "util/SCSUtilTools.h"
#include "DBLog.h"

using namespace std;

bool CSCSMySqlReader::ReadNextTestCase(CSCSPreparedSQLSet *set)
{
	CSCSMySqlHelper mysql;
	STConfig *config =CSCSConfigHelper::GetInstance().GetConfig();
	char *msg="";
	
	if(!mysql.ConnMySql(config->conSrcMysqlConnect.strIP,config->conSrcMysqlConnect.strPort,config->strCharset,msg))
	{
		std::cerr<< "open testcase srcMysql err:" << msg;
		return false;
	}

	vector<vector<string> > testTable;
	string casesql="Select * from caseslist where modules in ('"+SCSUtilTools::join(config->strModules,"','")+"') and caseid>"+SCSUtilTools::NumberToString(nTestCaseId)+" LIMIT 1";

	std::cout<<casesql<<std::endl;

	if(!mysql.Select(casesql,&testTable,msg))
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
	GetTestCase("mysqlcases",vecDesCase);

	if(NULL != set)
	{
		delete set;
	}

	bool checkSequence=testTable[1][GetColumnIndex("sequence_match")]=="1";
	std::string  strModule=testTable[1][GetColumnIndex("modules")];
	int nExecTimes=SCSUtilTools::StringToNumber<int>(testTable[1][GetColumnIndex("cases_execution_times"));
	bool checkDataNodes=testTable[1][GetColumnIndex("datanodes_check")

	set = new CSCSPreparedSQLSet(vecSrcCase,vecDesCase,checkSequence,strModule,nExecTimes,checkDataNodes);

	return true;
}

bool CSCSMySqlReader::GetTestCase( const std::string &column,const std::vector<std::vector<std::string> > &vecTestTable,std::vector<std::string> &vecTestCase )
{
	int scsdbcaseIndex=GetColumnIndex(column,vecTestTable);
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

int CSCSMySqlReader::GetColumnIndex( const std::string &column,const std::vector<std::string> &vecTestTable )
{
	vector<vector<string> >::iterator it;
	it = find(vecTestTable[0].begin(),vecTestTable[0].end(),column);

	if(it == vecTestTable[0].end())
	{
		std::cerr<<"read testcase srcMysql err:can't find column"+column<<std::endl;
		return -1;
	}

	int scsdbcaseIndex = it - vecTestTable[0].begin();

	if(scsdbcaseIndex >= vecTestTable[0].size())
	{
		std::cerr<<"read testcase srcMysql err:can't find column"+column<<std::endl;
		return -1;
	}

	return scsdbcaseIndex;
}






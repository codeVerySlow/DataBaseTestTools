#include "SCSMySqlReader.h"
#include "include/SCSMySqlHelper.h"
#include "include/SCSConfigHelper.h"

using namespace std;

CSCSPreparedSQLSet CSCSMySqlReader::ReadNextTestCase()
{
	CSCSMySqlHelper mysql;
	CSCSConfigHelper configHelper;

	STConfig *config =configHelper.Read();
	char *msg="";
	
	CSCSPreparedSQLSet sqlSet;
	if(!mysql.ConnMySql(config->SrcMysqlConnect.strIP,config->SrcMysqlConnect.strPort,config->Charset,msg))
	{
		vector<vector<string> > tests=mysql.Select("Select * from testinfo where caseid=",msg);
	}

	return sqlSet;

}

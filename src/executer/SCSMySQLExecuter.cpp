#include "SCSMySQLExecuter.h"
#include "SCSConfigHelper.h"
#include "SCSMySqlHelper.h"
#include "SCSUtilTools.h"

bool CSCSMySQLExecuter::OpenDataSource()
{	
	STConfig *config=CSCSConfigHelper::GetInstance()->GetConfig();
	std::string msg;

	if(!mysql.ConnMySql(config->conSrcMysqlConnect.strIP.c_str(),
				config->conSrcMysqlConnect.strPort,
				config->conSrcMysqlConnect.strUser.c_str(),
				config->conSrcMysqlConnect.strPwd.c_str(),
				config->conSrcMysqlConnect.strDataBase.c_str(),
				"UTF8",
				msg))
	{
		LOG_ERROR("Executer open mysql connect err");
		return false;
	}	

	return true;
}

CSCSResultIter CSCSMySQLExecuter::ExecuteSQL( const std::string &sql )
{
	std::string msg;
	mysql.InitSelect(sql.c_str(),msg);
	LOG_DEBUG(("mysql execute sql "+sql).c_str())
	return CSCSResultIter(this);
}

void CSCSMySQLExecuter::CloseDataSource()
{
	mysql.CloseMySql();
}

bool CSCSMySQLExecuter::GetNext( std::vector<std::string> &dataRow )
{
	return mysql.GetNextRow(&dataRow);
}

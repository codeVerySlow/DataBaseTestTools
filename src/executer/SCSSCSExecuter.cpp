#include "SCSSCSExecuter.h"
#include "SCSConfigHelper.h"
#include "SCSSCSHelper.h"
#include "SCSUtilTools.h"

bool CSCSMySQLExecuter::OpenDataSource()
{	
	STConfig *config=CSCSConfigHelper::GetInstance()->GetConfig();
	std::string msg;
	
	if(!scs.ConnMySql(config->conSrcMysqlConnect.strIP.c_str(),
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
	scs.InitSelect(sql.c_str(),msg);
	return CSCSResultIter(this);
}

void CSCSMySQLExecuter::CloseDataSource()
{
	scs.CloseSCS();
}

bool CSCSMySQLExecuter::GetNext( std::vector<std::string> &dataRow )
{
	return scs.GetNextRow(&dataRow);
}


#include "DBLog.h"
#include "SCSMySQLExecuter.h"
#include "SCSResultIter.h"
#include "util/SCSMySqlHelper.h"
#include "util/SCSConfigHelper.h"
bool CSCSMySQLExecuter::OpenDataSource() {
	std::string msg;
	if(!mysql->ConnMySql(m_pConnect->strIP.c_str(),
				m_pConnect->nPort,
				m_pConnect->strUser.c_str(),
				m_pConnect->strPwd.c_str(),
				m_pConnect->strDataBase.c_str(),
				"UTF8",
				msg))
	{
		LOG_ERROR(("Executer open mysql Connect err"+msg).c_str());
		return false;
	}

	return true;
}

boost::shared_ptr<CSCSResultIter> CSCSMySQLExecuter::ExecuteSQL(const std::string &sql, std::string &msg)
{
	std::string msg;
	mysql->InitSelect(sql.c_str(),msg);
	LOG_DEBUG(("mysql execute sql "+sql).c_str());
	return boost::shared_ptr<CSCSResultIter>(new CSCSResultIter(this));
}

void CSCSMySQLExecuter::CloseDataSource()
{
	mysql->CloseMySql();
}

bool CSCSMySQLExecuter::GetNext( std::vector<std::string> &dataRow )
{
	return mysql->GetNextRow(&dataRow);
}



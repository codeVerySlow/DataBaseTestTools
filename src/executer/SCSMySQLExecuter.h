#ifndef _EXECUTER_SCSMYSQLEXECUTER_H_
#define _EXECUTER_SCSMYSQLEXECUTER_H_

#include <boost/shared_ptr.hpp>
#include <util/SCSConfigHelper.h>
#include "SCSExecuter.h"

class CSCSMySqlHelper;

class CSCSMySQLExecuter:public CSCSExecuter
{
public:
	CSCSMySQLExecuter(const STConnect *connect):m_pConnect(connect){};
	bool OpenDataSource();
	boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql);
	void CloseDataSource();

	bool GetNext(std::vector<std::string> &dataRow);
private:
	boost::shared_ptr<CSCSMySqlHelper> mysql;
	const STConnect *m_pConnect;
};

#endif

#ifndef _EXECUTER_SCSSCSEXECUTER_H_
#define _EXECUTER_SCSSCSEXECUTER_H_

#include <boost/shared_ptr.hpp>
#include <util/SCSConfigHelper.h>
#include "SCSExecuter.h"

class CSCSSCSHelper;
struct STConnect;

class CSCSSCSExecuter:public CSCSExecuter
{
public:
	CSCSSCSExecuter(const STConnect *connect):m_pConnect(connect){};
	bool OpenDataSource();
	boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql);
	void CloseDataSource();

	bool GetNext(std::vector<std::string> &dataRow);
private:
	boost::shared_ptr<CSCSSCSHelper> scs;
	const STConnect *m_pConnect;
};

#endif
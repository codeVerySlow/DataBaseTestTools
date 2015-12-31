#ifndef _EXECUTER_SCSEXECUTERCHECKHANDLE_H_
#define _EXECUTER_SCSEXECUTERCHECKHANDLE_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class CSCSReport;

class CSCSExecuterCheckHandle
{
private:
	boost::shared_ptr<CSCSExecuterCheckHandle> nextHandle;
public:
	CSCSExecuterCheckHandle(){};
	virtual ~CSCSExecuterCheckHandle(){};
	void SetNextHandle(boost::shared_ptr<CSCSExecuterCheckHandle> handle);
	boost::shared_ptr<CSCSExecuterCheckHandle> GetNextHandle();
	virtual bool Check(std::vector<boost::shared_ptr<CSCSReport> > &report) =0;
};

#endif

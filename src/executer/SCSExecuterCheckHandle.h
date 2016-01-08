#ifndef _EXECUTER_SCSEXECUTERCHECKHANDLE_H_
#define _EXECUTER_SCSEXECUTERCHECKHANDLE_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <SCSPreparedSQLSet.h>

class CSCSReport;

class CSCSExecuterCheckHandle
{
private:
    boost::shared_ptr<CSCSExecuterCheckHandle> nextHandle;
public:
    CSCSExecuterCheckHandle():nextHandle()
    { };

    virtual ~CSCSExecuterCheckHandle()
    { };

    void SetNextHandle(boost::shared_ptr<CSCSExecuterCheckHandle> handle);

    boost::shared_ptr<CSCSExecuterCheckHandle> GetNextHandle();

    virtual bool Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports) = 0;
};

#endif

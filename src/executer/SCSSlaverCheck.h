#ifndef _EXECUTER_SCSSLAVERCHECK_H_
#define _EXECUTER_SCSSLAVERCHECK_H_

#include <vector>
#include <boost/shared_ptr.hpp>

#include "SCSExecuterCheckHandle.h"

class CSCSSCSHelper;
class CSCSPreparedSQLSet;

class CSCSSlaverCheck : public CSCSExecuterCheckHandle
{
public:
    CSCSSlaverCheck();

    bool Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports);

private:
    bool Error(const std::string &msg,const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    boost::shared_ptr<CSCSSCSHelper> m_pSCSHelper;
};

#endif
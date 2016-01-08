#ifndef _EXECUTER_SCSDATANODESCHECK_H
#define _EXECUTER_SCSDATANODESCHECK_H


#include "util/SCSSCSHelper.h"
#include "SCSExecuterCheckHandle.h"

class CSCSDataNodesCheck : public CSCSExecuterCheckHandle
{
public:

    CSCSDataNodesCheck() : m_pSCSHelper(new CSCSSCSHelper())
    { };

    ~CSCSDataNodesCheck()
    { };

    bool Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports);

private:
    bool Error(const std::string &msg, std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    boost::shared_ptr<CSCSSCSHelper> m_pSCSHelper;
};


#endif

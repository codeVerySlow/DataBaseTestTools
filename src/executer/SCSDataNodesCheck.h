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
    {
        m_pSCSHelper->CloseSCS();
    };
    //功能：节点检查
    //返回值：true 检查正常 false 检查异常
    //参数：set 用例集合 reports 报告集合
    bool Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports);

private:
    bool Error(const std::string &msg, std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    boost::shared_ptr<CSCSSCSHelper> m_pSCSHelper;
};


#endif

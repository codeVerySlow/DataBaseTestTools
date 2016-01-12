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
    //功能：检查SCSDB备份关系
    //返回值：true 检查正常 false 检查异常
    //参数：set 用例集合 reports 报告集合
    bool Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports);

private:
    bool Error(const std::string &msg,const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    boost::shared_ptr<CSCSSCSHelper> m_pSCSHelper;
};

#endif
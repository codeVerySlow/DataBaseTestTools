#ifndef _EXECUTER_SCSEXECUTERCHECKER_H_
#define _EXECUTER_SCSEXECUTERCHECKER_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class CSCSReport;
class CSCSDataNodesCheck;
class CSCSSlaverCheck;
class CSCSPreparedSQLSet;

class CSCSExecuterChecker
{
public:
    CSCSExecuterChecker();
    //功能：用例执行前将要执行的检查链
    //返回值：检查成功 true 检查失败 false
    //参数：set 测试用例 reports 报告集合
    bool BeforeTestCase(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);
    //功能：用例结束后执行的检查链
    //返回值：检查成功 true 检查失败 false
    //参数：set 测试用例 reports 报告集合
    bool AfterTestCase(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);
    //功能：sql执行前将要执行的检查链
    //返回值：检查成功 true 检查失败 false
    //参数：set 测试用例 reports 报告集合
    bool BeforeEachSql(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);
    //功能：sql执行后将要执行的检查链
    //返回值：检查成功 true 检查失败 false
    //参数：set 测试用例 reports 报告集合
    bool AfterEachSql(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);

private:
    boost::shared_ptr<CSCSDataNodesCheck> dataNodesCheck;
    boost::shared_ptr<CSCSSlaverCheck> slaverCheck;

};

#endif
#ifndef _INCLUDE_SCSEXECUTERWRAPPER_H_
#define _INCLUDE_SCSEXECUTERWRAPPER_H_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class CSCSExecuter;

class STSQLPair;

class CSCSResultIter;

class CSCSReport;
class CSCSExecuterChecker;
class CSCSPreparedSQLSet;

class CSCSExecuterWrapper
{
public:
    CSCSExecuterWrapper();

    ~CSCSExecuterWrapper();

    //功能：用例开始前的检查
    //返回值：bool 检查正常 true 检查异常 false
    //参数：set 读取的用例集 reports 结果报告集合
    bool BeforeTestCaseCheck(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);
    //功能：用例结束后的检查
    //返回值：bool 检查正常 true 检查异常 false
    //参数：set 读取的用例集 reports 结果报告集合
    bool AfterTestCaseCheck(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);
    //功能：执行单条SQL
    //返回值：bool 执行正常 true 执行错误 false
    //参数：set 读取的用例集 stsqlPair 要执行的sql语句 srcIter执行成功后返回结果迭代器 desIter执行成功后返回结果迭代器 reports测试用例报告集合 msg错误信息
    bool ExecuteSQL(const CSCSPreparedSQLSet &set,const STSQLPair &stsqlPair, boost::shared_ptr<CSCSResultIter> &srcIter,
                    boost::shared_ptr<CSCSResultIter> &desIter,
                    std::vector<boost::shared_ptr<const CSCSReport> > &reports, std::string &msg);

private:
    boost::shared_ptr<CSCSExecuter> srcExcuter;
    boost::shared_ptr<CSCSExecuter> desExcuter;
    boost::shared_ptr<CSCSExecuterChecker> checker;
};

#endif
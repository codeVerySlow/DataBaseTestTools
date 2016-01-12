#ifndef _INCLUDE_SCSCOMPARERWRAPPER_H_
#define _INCLUDE_SCSCOMPARERWRAPPER_H_
#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

class CSCSComparer;
class CSCSReport;
class CSCSPreparedSQLSet;
class STTestCaseReport;

class CSCSComparerWrapper
{
public:
    CSCSComparerWrapper();

    ~CSCSComparerWrapper();

    //功能：对比两个迭代器数据是否相同，相同返回ture，不相同返回false
    //返回值：bool 相同true 不相同false
    //参数：iter1 执行结果迭代器 iter2 执行结果迭代器
    bool Compare(boost::shared_ptr<CSCSResultIter> iter1,boost::shared_ptr<CSCSResultIter> iter2) ;

    //对比两个迭代器数据和顺序是否相同，相同返回true,不同返回false
    //返回值：bool 相同true 不相同false
    //参数：iter1 执行结果迭代器 iter2 执行结果迭代器
    bool CompareSequence(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2) ;

    //功能：获取该次对比后的结果
    //返回值：用例报告
    //参数：void
    boost::shared_ptr<STTestCaseReport> GetReport() const ;

private:
    boost::shared_ptr<CSCSComparer> m_compare;
};
#endif
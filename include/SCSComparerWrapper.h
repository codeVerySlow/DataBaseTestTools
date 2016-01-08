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

    //对比两个迭代器数据是否相同，相同返回ture，不相同返回false
    bool Compare(boost::shared_ptr<CSCSResultIter> iter1,boost::shared_ptr<CSCSResultIter> iter2) ;

    //对比两个迭代器数据和顺序是否相同，相同返回true,不同返回false
    bool CompareSequence(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2) ;

    boost::shared_ptr<STTestCaseReport> GetReport() const ;

private:
    boost::shared_ptr<CSCSComparer> m_compare;
};
#endif
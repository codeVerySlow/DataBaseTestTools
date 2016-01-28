#ifndef _COMPARER_SCSFILECOMPARER_H_
#define _COMPARER_SCSFILECOMPARER_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <string>
#include "SCSComparer.h"

class CSCSReport;
class CSCSSortCache;
class CSCSComparerReport;

class CSCSFileComparer : public CSCSComparer
{
public:
    CSCSFileComparer();
    //功能：对比两个迭代器数据是否相同，相同返回ture，不相同返回false
    //返回值：bool 对比一致true 对比不一致 false
    //参数：iter1 迭代器1 iter2 迭代器2 将要对比的两个迭代器
    bool Compare(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2);
    //功能：对比两个迭代器数据和顺序是否相同，相同返回true,不同返回false
    //返回值：bool 对比一致true 对比不一致 false
    //参数：iter1 iter2 将要对比的两个迭代器
    bool CompareSequence(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2);
    //功能：获取每次对比结果报告
    //返回值：对比报告
    //参数：void
    boost::shared_ptr<STTestCaseReport> GetReport() const;

private:
    void WriteCRCToCache(boost::shared_ptr<CSCSResultIter> iter, CSCSSortCache &fileName,std::vector<std::string> &column);

    boost::shared_ptr<STTestCaseReport> m_testcasereport;
};

#endif

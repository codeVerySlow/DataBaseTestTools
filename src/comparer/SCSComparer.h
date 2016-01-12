#ifndef _COMPARER_SCSCOMPARER_H_
#define _COMPARER_SCSCOMPARER_H_

#include<boost/shared_ptr.hpp>

class CSCSReport;
class CSCSResultIter;
struct STTestCaseReport;

class CSCSComparer
{
public:
    CSCSComparer()
    { };

    virtual ~CSCSComparer()
    { };

    //功能：对比两个迭代器数据是否相同，相同返回ture，不相同返回false
    //返回值：bool 对比一致true 对比不一致 false
    //参数：iter1 迭代器1 iter2 迭代器2 将要对比的两个迭代器
    virtual bool Compare(boost::shared_ptr<CSCSResultIter> iter1,boost::shared_ptr<CSCSResultIter> iter2) = 0;

    //功能：对比两个迭代器数据和顺序是否相同，相同返回true,不同返回false
    //返回值：bool 对比一致true 对比不一致 false
    //参数：iter1 iter2 将要对比的两个迭代器
    virtual bool CompareSequence(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2) = 0;
    //功能：获取每次对比结果报告
    //返回值：对比报告
    //参数：void
    virtual boost::shared_ptr<STTestCaseReport> GetReport() const = 0;
    //功能：创建对比算法实例
    //返回值：对比算法实例
    //参数：void 因为目前只有一种算法 所以不需要参数
    static boost::shared_ptr<CSCSComparer> Create();
};

#endif


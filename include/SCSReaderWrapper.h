#ifndef _INCLUDE_SCSREADERWRAPPER_H_
#define _INCLUDE_SCSREADERWRAPPER_H_

#include <string>
#include <boost/shared_ptr.hpp>

class CSCSReader;
class CSCSPreparedSQLSet;
//测试用例读取类
class CSCSReaderWrapper
{
public:
    CSCSReaderWrapper();

    ~CSCSReaderWrapper();
    //功能：读取下一条测试用例
    //返回值：bool 读取成功并且还有下一条记录 true 读取失败或者读取结束 false
    //参数：set 读取到的用例
    bool ReadNextTestCase(CSCSPreparedSQLSet &set);
    //功能：获取用例总个数
    //返回值：用例个数
    //参数：void
    int GetTestCaseTotal();
    //功能：获取当前用例是第几个
    //返回值：用例索引
    //参数：void
    int GetTestCaseIndex();

private:
    boost::shared_ptr<CSCSReader> m_reader;
};

#endif
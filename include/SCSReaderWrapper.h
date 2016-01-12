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

private:
    boost::shared_ptr<CSCSReader> reader;
};

#endif
#ifndef _INCLUDE_CSCSPREPAREDSQLSET_H_
#define _INCLUDE_CSCSPREPAREDSQLSET_H_

#include <string>
#include <boost/shared_ptr.hpp>

class CSCSPreparedSQLSet;

class CSCSReader
{
public:
    CSCSReader()
    { };

    virtual ~CSCSReader()
    { };
    //功能：读取下一条测试用例
    //返回值：true 读取正常并且有未读完数据 false 读取异常或者读取完成
    //参数：set 用例集合
    virtual bool ReadNextTestCase(CSCSPreparedSQLSet &set) = 0;
    //功能：获取用例总个数
    //返回值：用例个数
    //参数：void
    virtual int GetTestCaseTotal()=0;
    //功能：获取当前用例是第几个
    //返回值：用例索引
    //参数：void
    virtual int GetTestCaseIndex()=0;

    static boost::shared_ptr<CSCSReader> Create();
};

#endif

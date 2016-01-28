#ifndef _READER_CSCSMYSQLREADER_H_
#define _READER_CSCSMYSQLREADER_H_

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "SCSReader.h"

class CSCSPreparedSQLSet;
class CSCSMySqlHelper;

class CSCSMySqlReader : public CSCSReader
{
public:
    CSCSMySqlReader();

    ~CSCSMySqlReader();
    //功能：读取下一条测试用例
    //返回值：true 读取正常并且有未读完数据 false 读取异常或者读取完成
    //参数：set 用例集合
    bool ReadNextTestCase(CSCSPreparedSQLSet &set);


    virtual int GetTestCaseTotal();

    virtual int GetTestCaseIndex();

private:
    int nTestCaseId;
    int nTestCaseTotal;
    int nTestCaseIndex;
    boost::shared_ptr<CSCSMySqlHelper> mysql;
    bool GetTestCase(const std::string &column,
                     const std::vector<std::vector<std::string> > &vecTestTable,
                     std::vector<std::string> &vecTestCase);


};

#endif

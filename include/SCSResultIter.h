#ifndef _INCLUDE_SCSRESULTITER_H_
#define _INCLUDE_SCSRESULTITER_H_

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

class CSCSExecuter;
//执行结果迭代器
class CSCSResultIter
{
public:
    CSCSResultIter(CSCSExecuter *executer);
    ~CSCSResultIter();
    //功能：获取SQL结果集中下一行数据
    //返回值：bool 成功读取并且还有为读取数据 true 读取完成或者读取失败 false
    //参数：row 读取到的数据行
    bool GetNext(std::vector<std::string> &row);
private:
    CSCSExecuter *m_pExecuter;
};

#endif

#ifndef _EXECUTE_SCSEXECUTE_H_
#define _EXECUTE_SCSEXECUTE_H_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>


enum EMExecuterType
{
    ExecuterType_SCS,
    ExecuterType_MYSQL
};

class CSCSResultIter;

struct STConnect;

class CSCSExecuter
{
public:
    CSCSExecuter()
    { };

    virtual ~CSCSExecuter()
    { };
    //功能：执行SQL语句 结果集以迭代器形式返回
    //返回值：执行结果迭代器 错误时返回空指针
    //参数：sql语句 msg错误信息
    virtual boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql, std::string &msg) = 0;
    //功能：关闭数据源
    //返回值：void
    //参数：void
    virtual void CloseDataSource() = 0;
    //功能：获取下一条数据 建议直接使用迭代器
    //返回值：bool 获取成功并且有未读取数据
    //参数：dataRow 获取的数据
    virtual bool GetNext(std::vector<std::string> &dataRow) = 0;

    //功能：获取服务器版本
    //返回值：string 版本号
    //参数：void
    virtual std::string GetServerVersion()=0;

    //功能：根据条件获取执行器实例
    //返回值：返回执行器实例
    //参数：type 获取的执行器类型 connect 执行器的连接信息
    static boost::shared_ptr<CSCSExecuter> Create(EMExecuterType type, const STConnect *connect);

};

#endif


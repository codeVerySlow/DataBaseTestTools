#ifndef _EXECUTER_SCSSCSEXECUTER_H_
#define _EXECUTER_SCSSCSEXECUTER_H_

#include <boost/shared_ptr.hpp>
#include "util/SCSSCSHelper.h"
#include "SCSExecuter.h"

class CSCSSCSHelper;

struct STConnect;

class CSCSSCSExecuter : public CSCSExecuter
{
public:
    CSCSSCSExecuter(const STConnect *connect) : scs(new CSCSSCSHelper()),
                                                m_pConnect(connect),
                                                m_isClose(false)
    { };

    ~CSCSSCSExecuter()
    {
        if(!m_isClose)
            CloseDataSource();
    };
    //功能：执行SQL语句 结果集以迭代器形式返回
    //返回值：执行结果迭代器 错误时返回空指针
    //参数：sql语句 msg错误信息
    boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql, std::string &msg);

    std::string GetServerVersion() ;

    //功能：关闭数据源
    //返回值：void
    //参数：void
    void CloseDataSource();
    //功能：获取下一条数据 建议直接使用迭代器
    //返回值：bool 获取成功并且有未读取数据
    //参数：dataRow 获取的数据
    bool GetNext(std::vector<std::string> &dataRow);

private:
    boost::shared_ptr<CSCSSCSHelper> scs;
    const STConnect *m_pConnect;
    bool m_isClose;
};

#endif
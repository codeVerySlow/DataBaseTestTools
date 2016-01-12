#ifndef _EXECUTER_SCSEXECUTERCHECKHANDLE_H_
#define _EXECUTER_SCSEXECUTERCHECKHANDLE_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <SCSPreparedSQLSet.h>

class CSCSReport;

class CSCSExecuterCheckHandle
{
private:
    boost::shared_ptr<CSCSExecuterCheckHandle> nextHandle;
public:
    CSCSExecuterCheckHandle():nextHandle()
    { };

    virtual ~CSCSExecuterCheckHandle()
    { };

    //功能：设置职责链下一处理对象
    //返回值：void
    //参数：handle 下一处理对象
    void SetNextHandle(boost::shared_ptr<CSCSExecuterCheckHandle> handle);

    //功能：获取职责链下一处理对象
    //返回值：handle 下一处理对象
    //参数：void
    boost::shared_ptr<CSCSExecuterCheckHandle> GetNextHandle();

    //功能：执行处理
    //返回值：bool 处理成功 true 处理失败 false
    //参数：set 用例集合 reports 报告集合
    virtual bool Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports) = 0;
};

#endif

#ifndef _EXECUTER_SCSSERVICECHECK_H_
#define _EXECUTER_SCSSERVICECHECK_H_
#include <vector>
#include <boost/shared_ptr.hpp>
#include <sys/types.h>

#include "SCSExecuterCheckHandle.h"

class CSCSServiceCheck : public CSCSExecuterCheckHandle
{
public:
    //功能：检查SCSDB服务稳定性
    //返回值：true 检查正常 false 检查异常
    //参数：set 用例集合 reports 报告集合
    bool Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &report);

private:
    static int s_nReConnectTimes;
    static pid_t s_nLastPID;
};

int CSCSServiceCheck::s_nReConnectTimes = 0;
pid_t CSCSServiceCheck::s_nLastPID = -1;

#endif
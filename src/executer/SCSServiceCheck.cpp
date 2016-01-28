#include <util/SCSUtilTools.h>
#include <SCSPreparedSQLSet.h>
#include "SCSServiceCheck.h"

bool CSCSServiceCheck::Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &report)
{
    if (s_nLastPID == -1)
    {
        //TODO:等待scsdb的api支持查询进程id时完成该段代码。
    }
    return false;
}

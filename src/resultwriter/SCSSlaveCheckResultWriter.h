#ifndef _RESULTWRITER_SCSSLAVECHECKRESULTWRITER_H_
#define _RESULTWRITER_SCSSLAVECHECKRESULTWRITER_H_

#include "SCSResultWriter.h"

class CSCSSlaveCheckResultWriter : public CSCSResultWriter
{

public:
    //功能：将备份关系报告写入磁盘
    //返回值：true 写入正常 false 写入异常
    //参数：report 报告
    bool Write(boost::shared_ptr<const CSCSReport> report);
};


#endif
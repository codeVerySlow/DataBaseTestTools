#ifndef _RESULTWRITER_SCSDATANODECHECKRESULTWRITER_H_
#define _RESULTWRITER_SCSDATANODECHECKRESULTWRITER_H_


#include "SCSResultWriter.h"

class CSCSDataNodeCheckResultWriter : public CSCSResultWriter
{

public:
    //功能：将节点检查报告写入磁盘
    //返回值：true 写入正常 false 写入异常
    //参数：report 报告
    bool Write(boost::shared_ptr<const CSCSReport> report);

};


#endif 

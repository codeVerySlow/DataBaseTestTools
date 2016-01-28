#ifndef _RESULTWRITER_SCSTESTRESULTWRITER_H_
#define _RESULTWRITER_SCSTESTRESULTWRITER_H_

#include <fstream>
#include "SCSResultWriter.h"

class CSCSComparerReport;
class CSCSTestResultWriter : public CSCSResultWriter
{
public:
    //功能：将对比报告写入磁盘
    //返回值：true 写入正常 false 写入异常
    //参数：report 报告
    bool Write(const boost::shared_ptr<const CSCSReport> report);

private:
    void OutPutModulCount(const boost::shared_ptr<const CSCSComparerReport> &testReport, std::fstream &fs) const;
};


#endif
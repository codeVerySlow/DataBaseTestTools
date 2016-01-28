#ifndef _RESULTWRITER_SCSRESULTWRITER_H_
#define _RESULTWRITER_SCSRESULTWRITER_H_

#include <vector>
#include <boost/shared_ptr.hpp>
#include <time.h>
#include "util/SCSUtilTools.h"

enum EMWriterType
{
    WRITERTYPE_DATANODE,
    WRITERTYPE_SLAVECHECK,
    WRITERTYPE_TESTRESULT
};

class CSCSReport;

class CSCSResultWriter
{
public:
    CSCSResultWriter() : filePath("./report")
    {
        char filename[80];
        time_t rawtime = time(NULL);
        struct tm *timeinfo = localtime(&rawtime);
        strftime(filename, 80, "%Y%m%d%H%M%S", timeinfo);

        filePath = filePath + filename + "/";
        SCSUtilTools::createDirIfNotExist(filePath);
    };

    virtual ~CSCSResultWriter()
    { };

    //功能：将报告写入磁盘
    //返回值：true 写入正常 false 写入异常
    //参数：report 报告
    virtual bool Write(boost::shared_ptr<const CSCSReport> report) = 0;

    //功能：将报告批量写入磁盘
    //返回值：true 写入正常 false 写入异常
    //参数：reports 报告集合
    bool Write(std::vector<boost::shared_ptr<const CSCSReport> > &reports);

	static boost::shared_ptr<CSCSResultWriter> Create(EMWriterType type);

    std::string filePath;
};
#endif

#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "util/SCSUtilTools.h"
#include "executer/SCSSlaveCheckReport.h"
#include "SCSSlaveCheckResultWriter.h"
#include "DBLog.h"

bool CSCSSlaveCheckResultWriter::Write(boost::shared_ptr<const CSCSReport> report)
{
    boost::shared_ptr<const CSCSSlaveCheckReport> slaveReport;
    if (!(slaveReport = boost::dynamic_pointer_cast<const CSCSSlaveCheckReport>(report)))
    {
        LOG_ERROR("SlaveCheckResultWriter err:try to write err type which is not CSCSSlaveCheckReport");
        return false;
    }

    std::fstream fs((filePath+"slavestatus.report").c_str(), std::ios::out | std::ios::app);
    if (!fs)
    {
        LOG_ERROR(("DataNodeCheckResultWriter err:open file err " + filePath).c_str());
        return false;
    }

    if (fs.tellp() == std::ios::beg)
    {
        fs << "slavestatus报告" << std::endl;
        fs << "==========================================================================" << std::endl;
        fs << "开始时间:	" << SCSUtilTools::timeToString(slaveReport->getM_StartTime()) << std::endl;
        fs << "结束时间:	" << SCSUtilTools::timeToString(slaveReport->getM_EndTime()) << std::endl;
        fs << "运行时长:	" <<
        SCSUtilTools::spanTimeToString(slaveReport->getM_EndTime(), slaveReport->getM_StartTime()) << std::endl;
        fs << "当前SCSDB版本:	" << slaveReport->getM_strDesVersion() << std::endl;
        fs << "==========================================================================" << std::endl;
    }
    fs << "SCSDB环境备份关系出现异常" << std::endl;
    fs << "==========================================================================" << std::endl;
    fs << slaveReport->getM_strCurrentSql() << std::endl;
    fs << "==========================================================================" << std::endl;

    return true;
}


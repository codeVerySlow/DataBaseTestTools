#include <fstream>
#include <dirent.h>
#include "DBLog.h"
#include "SCSDataNodeCheckResultWriter.h"
#include "SCSReport.h"
#include "util/SCSUtilTools.h"
#include "executer/SCSDataNodeReport.h"


bool CSCSDataNodeCheckResultWriter::Write(boost::shared_ptr<const CSCSReport> report)
{
    boost::shared_ptr<const CSCSDataNodeReport> dataNodeReport;
    if (!(dataNodeReport = boost::dynamic_pointer_cast<const CSCSDataNodeReport>(report)))
    {
        LOG_ERROR("DataNodeCheckResultWriter err:try to write err type which is not CSCSDataNodeReport");
        return false;
    }

    char filename[80];
    time_t rawtime = dataNodeReport->getM_StartTime();
    struct tm *timeinfo = localtime(&rawtime);

    strftime(filename, 80, "DataNodesQuantity_%Y%m%d.report", timeinfo);

    std::string filePath = "./report/";
    if (!opendir(filePath.c_str()))
    {
        mkdir(filePath.c_str());
    }
    filePath += filename;
    std::fstream fs(filePath.c_str(), std::ios::out | std::ios::app);
    if (!fs)
    {
        LOG_ERROR(("DataNodeCheckResultWriter err:open file err " + filePath).c_str());
        return false;
    }
    if (fs.tellp() == std::ios::beg)
    {
        fs << "DataNodesQuantity报告" << std::endl;
        fs << "==========================================================================" << std::endl;
        fs << "开始时间:	" << SCSUtilTools::timeToString(dataNodeReport->getM_StartTime()) << std::endl;
        fs << "结束时间:	" << SCSUtilTools::timeToString(dataNodeReport->getM_StartTime()) << std::endl;
        fs << "运行时长:	" <<
        SCSUtilTools::spanTimeToString(dataNodeReport->getM_EndTime(), dataNodeReport->getM_StartTime()) << std::endl;
        fs << "当前SCSDB版本:	" << dataNodeReport->getM_strDesVersion() << std::endl;
        fs << "==========================================================================" << std::endl;
    }
    fs << dataNodeReport->getM_strCurrentSql() << std::endl;
    fs << "IP                     tablename		count" << std::endl;
    std::vector<STNode>::const_iterator nodeIter = dataNodeReport->getNodeCount().begin();
    while (nodeIter != dataNodeReport->getNodeCount().end())
    {
        fs << (*nodeIter).IP << ":" << (*nodeIter).Port << "		" << (*nodeIter).TableName << "			" <<
        (*nodeIter).Count << std::endl;
        nodeIter++;
    }
    fs << "==========================================================================" << std::endl;
    fs.close();
    return true;
}


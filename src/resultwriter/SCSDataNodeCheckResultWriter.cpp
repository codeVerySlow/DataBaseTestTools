#include <fstream>
#include <string.h>
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

    std::fstream fs((filePath+"DataNodesQuantity.report").c_str(), std::ios::out | std::ios::app);
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
        fs << "结束时间:	" << SCSUtilTools::timeToString(dataNodeReport->getM_EndTime()) << std::endl;
        fs << "运行时长:	" <<
        SCSUtilTools::spanTimeToString(dataNodeReport->getM_EndTime(), dataNodeReport->getM_StartTime()) << std::endl;
        fs << "当前SCSDB版本:	" << dataNodeReport->getM_strDesVersion() << std::endl;
        fs << "==========================================================================" << std::endl;
    }
    fs <<"["<<dataNodeReport->getM_strCurrentModel()<<"]"<<"["<<dataNodeReport->getM_strCurrentCaseID()<<"]"<< dataNodeReport->getM_strCurrentSql() << std::endl;
    fs << "IP                                         tablename		                        count" << std::endl;
    std::vector<STNode>::const_iterator nodeIter = dataNodeReport->getNodeCount().begin();
    char tablenamebuff[20];
    char nodecount[20];
    memset(tablenamebuff,0,20);
    memset(nodecount,0,20);
    while (nodeIter != dataNodeReport->getNodeCount().end())
    {
        //格式化右对齐
        sprintf(tablenamebuff,"%20s",(*nodeIter).TableName.c_str());
        sprintf(nodecount,"%20s",(*nodeIter).Count.c_str());
        fs << (*nodeIter).IP << ":" << (*nodeIter).Port << "		" << tablenamebuff << "			" <<
        nodecount << std::endl;
        nodeIter++;
    }
    fs << "==========================================================================" << std::endl;
    fs.close();
    return true;
}

#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "DBLog.h"
#include "SCSTestResultWriter.h"
#include "util/SCSUtilTools.h"
#include "comparer/SCSComparerReport.h"

bool CSCSTestResultWriter::Write(boost::shared_ptr<const CSCSReport> report)
{
    boost::shared_ptr<const CSCSComparerReport> testReport;
    if (!(testReport = boost::dynamic_pointer_cast<const CSCSComparerReport>(report)))
    {
        LOG_ERROR("TestResultWriter err:try to write err type which is not CSCSComparerReport");
        return false;
    }

    char filename[80];
    time_t rawtime = testReport->getM_StartTime();
    struct tm *timeinfo = localtime(&rawtime);

    strftime(filename, 80, "RoboTesterReport_%Y%m%d.report", timeinfo);

    std::string filePath = "./report/";

    if (!opendir(filePath.c_str()))
    {
        mkdir(filePath.c_str(),S_IRWXU);
    }
    std::fstream fs((filePath+filename).c_str(), std::ios::out | std::ios::app);
    if (!fs)
    {
        LOG_ERROR(("DataNodeCheckResultWriter err:open file err " + filePath).c_str());
        return false;
    }

    fs << "自动化测试报告" << std::endl;
    fs << "==========================================================================" << std::endl;
    fs << "开始时间:	" << SCSUtilTools::timeToString(testReport->getM_StartTime()) << std::endl;
    fs << "结束时间:	" << SCSUtilTools::timeToString(testReport->getM_StartTime()) << std::endl;
    fs << "运行时长:	" << SCSUtilTools::spanTimeToString(testReport->getM_EndTime(), testReport->getM_StartTime()) <<
    std::endl;
    fs << "当前SCSDB版本:	" << testReport->getM_strDesVersion() << std::endl;
    fs << "当前对比版本:    " << testReport->getM_strSrcVersion() << std::endl;
    fs << "==========================================================================" << std::endl;
    fs << "模块      执行总用例数     执行成功用例数      执行失败用例数" << std::endl;
    OutPutModulCount(testReport,"select", fs);
    OutPutModulCount(testReport,"insert", fs);
    OutPutModulCount(testReport,"delete", fs);
    OutPutModulCount(testReport,"update", fs);
    fs << "总计:	"
    << testReport->GetSuccess("select") + testReport->GetFail("select")
       + testReport->GetSuccess("insert") + testReport->GetFail("insert")
       + testReport->GetSuccess("delete") + testReport->GetFail("delete")
       + testReport->GetSuccess("update") + testReport->GetFail("update") << std::endl;

    std::vector<STTestCaseReport>::const_iterator iter = testReport->m_vecFailTestCase.begin();
    while (iter != testReport->m_vecFailTestCase.end())
    {
        fs << "==========================================================================" << std::endl;
        fs << "[" << iter->strModel << "][" << iter->nCaseID << "]" << iter->strDesCaseSql << std::endl;
        if(iter->m_emDisMatchType==DISMATCHTYPE_ROW)
            fs << "对比结果不一致原因：返回结果不一致" << std::endl;
        else if(iter->m_emDisMatchType==DISMATCHTYPE_SQLERR)
            fs<<"SQL语句执行错误"<<std::endl;
        else if(iter->m_emDisMatchType==DISMATCHTYPE_COLUM)
            fs<<"对比结果不一致原因：列个数不一致"<<std::endl;
        else if(iter->m_emDisMatchType==DISMATCHTYPE_ROWCOUNT)
            fs<<"对比结果不一致原因：受影响行数不一致"<<std::endl;
        fs << SCSUtilTools::join(iter->srcRow, ",") << std::endl;
        fs << SCSUtilTools::join(iter->desRow, ",") << std::endl;
        fs << iter->strErrMsg << std::endl;
        fs << "==========================================================================" << std::endl;
        iter++;
    }
    fs.close();
    return true;
}

void CSCSTestResultWriter::OutPutModulCount(const boost::shared_ptr<const CSCSComparerReport> &testReport,const std::string &module,
                                            std::fstream &fs) const
{
    fs << "["<<module<<"] 	" << testReport->GetSuccess(module) + testReport->GetFail(module)
    << "            " << testReport->GetSuccess(module)
    << "						" << testReport->GetFail(module) << endl;
}

#include <set>
#include <fstream>
#include <string.h>

#include "util/SCSConfigHelper.h"
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

    std::fstream fs((filePath+"RoboTesterReport.report").c_str(), std::ios::out | std::ios::app);
    if (!fs)
    {
        LOG_ERROR(("DataNodeCheckResultWriter err:open file err " + filePath).c_str());
        return false;
    }

    fs << "自动化测试报告" << std::endl;
    fs << "==========================================================================" << std::endl;
    fs << "开始时间:	" << SCSUtilTools::timeToString(testReport->getM_StartTime()) << std::endl;
    fs << "结束时间:	" << SCSUtilTools::timeToString(testReport->getM_EndTime()) << std::endl;
    fs << "运行时长:	" << SCSUtilTools::spanTimeToString(testReport->getM_EndTime(), testReport->getM_StartTime()) <<
    std::endl;
    fs << "dest_scsdb:	" << testReport->getM_strDesVersion() << std::endl;
    if(CSCSConfigHelper::GetInstance()->GetConfig()->emModel==Model_SCSDB_SCSDB)
    {
        fs << "src_scsdb:      " << testReport->getM_strSrcVersion() << std::endl;
    }
    else
    {
        fs << "src_mysql:      " << testReport->getM_strSrcVersion() << std::endl;
    }
    fs << "==========================================================================" << std::endl;
    fs << "模块      执行总用例数     执行成功用例数      执行失败用例数" << std::endl;

    OutPutModulCount(testReport, fs);
    fs << "总计:	"
    << testReport->GetSuccessTotal()+testReport->GetFailTotal() << std::endl;

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
        //fs << SCSUtilTools::join(iter->srcRow, ",") << std::endl;
        //fs << SCSUtilTools::join(iter->desRow, ",") << std::endl;
        fs << iter->strErrMsg << std::endl;
        fs << "==========================================================================" << std::endl;
        iter++;
    }
    fs.close();

    std::fstream csvfs((filePath+"result.csv").c_str(),std::ios::out | std::ios::app);
    int count=0;
    csvfs<<"执行结果对比不一致用例:,,,,"<<std::endl;
    iter = testReport->m_vecFailTestCase.begin();
    while (iter != testReport->m_vecFailTestCase.end())
    {

       csvfs<<",,,,"<<std::endl;
       csvfs<<"["<<++count<<"],,,,"<<std::endl;
       csvfs<<"########################################,##########,#########,#########,#########"<<std::endl;
       csvfs<<",,,,"<<std::endl;
       csvfs<<"dest_scsdb,"<<SCSUtilTools::join(iter->desColumn,",")<<std::endl;
       csvfs<<"[" << iter->strModel << "][" << iter->nCaseID << "]" << iter->strDesCaseSql<<","<<SCSUtilTools::join(iter->desRow,",")<<std::endl;
       csvfs<<"        ,,,,"<<std::endl;
        if(CSCSConfigHelper::GetInstance()->GetConfig()->emModel==Model_SCSDB_SCSDB)
        {
            csvfs << "src_scsdb,"<<SCSUtilTools::join(iter->srcColumn,",") << std::endl;
            csvfs <<"[" << iter->strModel << "][" << iter->nCaseID << "]" << iter->strDesCaseSql<<","<<SCSUtilTools::join(iter->srcRow,",")<< std::endl;
        }
        else
        {
            csvfs << "src_mysql,"<<SCSUtilTools::join(iter->srcColumn,",") << std::endl;
            csvfs <<"[" << iter->strModel << "][" << iter->nCaseID << "]" << iter->strSrcCaseSql<<","<<SCSUtilTools::join(iter->srcRow,",")<< std::endl;
        }

        csvfs<<"        ,,,,"<<std::endl;

        iter++;
    }
    csvfs.close();
    return true;
}

void CSCSTestResultWriter::OutPutModulCount(const boost::shared_ptr<const CSCSComparerReport> &testReport,
                                            std::fstream &fs) const
{
    std::set<std::string> models;
    for (std::map<std::string,int>::iterator it=testReport->m_success.begin(); it!=testReport->m_success.end(); ++it)
    {
        if(it->second!=0)
        {
            models.insert(it->first);
        }
    }
    for (std::map<std::string,int>::iterator it=testReport->m_fail.begin(); it!=testReport->m_fail.end(); ++it)
    {
        if(it->second!=0)
        {
            models.insert(it->first);
        }
    }
    for (std::set<std::string>::iterator it=models.begin(); it!=models.end(); ++it)
    {
        fs << "["<<*it<<"] 	" << testReport->GetSuccess(*it) + testReport->GetFail(*it)
        << "            " << testReport->GetSuccess(*it)
        << "						" << testReport->GetFail(*it) << endl;
    }

}


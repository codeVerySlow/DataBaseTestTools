#include <iostream>
#include <boost/shared_ptr.hpp>

#include "SCSExecuterWrapper.h"
#include "util/SCSUtilTools.h"
#include "util/SCSConfigHelper.h"
#include "SCSReaderWrapper.h"
#include "SCSComparerWrapper.h"
#include "SCSResultWriterWrapper.h"
#include "SCSPreparedSQLSet.h"
#include "comparer/SCSComparerReport.h"
#include "DBLog.h"

void run();

int main(int argc, char const *argv[])
{
    SCSUtilTools::initLog();
    if (!(argc > 1 ? CSCSConfigHelper::GetInstance()->Read(argv[1]) : CSCSConfigHelper::GetInstance()->Read()))
    {
        std::cout << "read config file err see log file" << std::endl;
        return 0;
    }

    int cycle = CSCSConfigHelper::GetInstance()->GetConfig()->nCycle;
    while (cycle-- > 0)
    {
        run();
    }
    return 0;
}

void run()
{
    CSCSReaderWrapper reader;
    CSCSExecuterWrapper executer;
    CSCSComparerWrapper comparer;
    CSCSResultWriterWrapper writer;

    CSCSPreparedSQLSet set;
    std::vector<boost::shared_ptr<const CSCSReport> > reports;
    std::string msg;
    boost::shared_ptr<CSCSComparerReport> report(new CSCSComparerReport());
    char progress[100];
    while (reader.ReadNextTestCase(set))
    {
        STSQLPair pair;
        boost::shared_ptr<CSCSResultIter> srcIter,desIter;
        bool ismatch = false;
        bool isstop=false;
        while (set.GetNext(pair))
        {
            if (!executer.ExecuteSQL(set, pair, srcIter, desIter, reports, msg,isstop))
            {
                report->AddTestCaseExecuteErrReport(set, msg);
                report->CountFail(set.m_strModule);
                ismatch=false;
                break;
            }

            ismatch = set.m_checkSequence ? comparer.CompareSequence(srcIter, desIter) : comparer.Compare(srcIter,desIter);
            if (!ismatch)
            {
                report->AddTestCaseFailReport(comparer.GetReport(), set);
                report->CountFail(set.m_strModule);
                break;
            }
        }
        if (ismatch)
        {
            report->CountSuccess(set.m_strModule);
        }
        executer.AfterTestCaseCheck(set, reports);
        sprintf(progress, "用例执行进度 %d/%d，对比结果一致用例数：%d，对比结果不一致用例数：%d", reader.GetTestCaseIndex(),
                reader.GetTestCaseTotal(), report->GetSuccessTotal(), report->GetFailTotal());
        LOG_INFO(progress);
        if(isstop)
        {
            break;
        }
    }
    executer.SetReportVersion(report);
    report->setM_EndTime(time(NULL));
    reports.push_back(report);
    writer.Write(reports);
}
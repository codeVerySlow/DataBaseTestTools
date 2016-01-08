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
    LOG_INIT_NORMAL("./", true);
    SET_LOGLEVEL(__SLL_DEBUG);
    assert(CSCSConfigHelper::GetInstance()->Read());

    int cycle = CSCSConfigHelper::GetInstance()->GetConfig()->nCycle;
    while (cycle--)
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
    while (reader.ReadNextTestCase(set))
    {
        std::cout << "==================>compare testcase id:" << set.m_nCaseID <<" <=================="<< std::endl;
        if(!executer.BeforeTestCaseCheck(set,reports))
        {
            std::cout<<"XXXXXXXXXXXXXXXX Before TestCaseCheck Erro XXXXXXXXXXXXXXXXXX"<<std::endl;
            continue;
        }
        STSQLPair pair;
        boost::shared_ptr<CSCSResultIter> srcIter;
        boost::shared_ptr<CSCSResultIter> desIter;
        bool ismatch = false;
        while (set.GetNext(pair))
        {
            std::cout << "*****************>compare sql :" << set.m_nCurrentIndex << "/" << set.m_nTotal <<" <*****************" <<std::endl;
            std::cout << "execute SCS sql :" << pair.strSQLDestination << std::endl;
            std::cout << "execute MySql sql :" << pair.strSQLSource << std::endl;
            if (!executer.ExecuteSQL(set,pair, srcIter, desIter,reports, msg))
            {
                std::cout << msg << std::endl;
                report->AddTestCaseExecuteErrReport(set,msg);
                report->CountFail(set.m_strModule);
                break;
            }

            ismatch = set.m_checkSequence ? comparer.CompareSequence(srcIter, desIter) : comparer.Compare(srcIter,
                                                                                                          desIter);
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
        if(!executer.AfterTestCaseCheck(set,reports))
        {
            std::cout<<"XXXXXXXXXXXXXXXX After TestCase Check Erro XXXXXXXXXXXXXXXX"<<std::endl;
            continue;
        }
    }
    report->setM_EndTime(time(NULL));
    reports.push_back(report);
    writer.Write(reports);
}
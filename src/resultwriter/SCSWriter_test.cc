#include <vector>
#include <boost/shared_ptr.hpp>
#include <util/SCSConfigHelper.h>

#include "SCSResultWriter.h"
#include "SCSDataNodeCheckResultWriter.h"
#include "SCSSlaveCheckResultWriter.h"
#include "SCSTestResultWriter.h"
#include "executer/SCSDataNodeReport.h"
#include "DBLog.h"

using namespace std;

int main()
{
    LOG_INIT_NORMAL("./", true);
    SET_LOGLEVEL(__SLL_INFO);
    assert(CSCSConfigHelper::GetInstance()->Read());

    vector<boost::shared_ptr<CSCSReport> > reports;
    vector<STNode> nodes;
    nodes.push_back(STNode("192.168.1.1", "1000", "test", "1000"));
    nodes.push_back(STNode("192.168.1.2", "1000", "test", "2000"));

    time_t now = time(NULL);
    struct tm *tomorrow = localtime(&now);
    tomorrow->tm_mday += 1;


    boost::shared_ptr<CSCSDataNodeReport> report(new CSCSDataNodeReport(nodes));
    report->setM_StartTime(now);
    report->setM_EndTime(mktime(tomorrow));
    report->setM_isSuccess(true);
    report->setM_strCaseID("111");
    report->setM_strCaseModule("select");
    report->setM_strCurrentSQL("select * from test");
    report->setM_strDesVersion("1.0");
    report->setM_strMessage("");
    report->setM_strSrcVersion("1.0");
    reports.push_back(report);


    CSCSResultWriter *writer = new CSCSDataNodeCheckResultWriter();

    //writer->Write(reports);
}

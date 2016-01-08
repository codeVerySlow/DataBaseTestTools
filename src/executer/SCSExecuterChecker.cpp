#include <SCSPreparedSQLSet.h>
#include <util/SCSConfigHelper.h>
#include "SCSReport.h"
#include "SCSExecuterChecker.h"
#include "SCSSlaverCheck.h"
#include "SCSDataNodesCheck.h"


bool CSCSExecuterChecker::BeforeTestCase(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    return true;
}

bool CSCSExecuterChecker::AfterTestCase(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    if(!set.m_checkDataNodes)
    {
        return true;
    }
    dataNodesCheck->SetNextHandle(boost::shared_ptr<CSCSExecuterCheckHandle>());
    return dataNodesCheck->Check(set, reports);
}

bool CSCSExecuterChecker::BeforeEachSql(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    if(!CSCSConfigHelper::GetInstance()->GetConfig()->checkSlavestatus)
    {
        return true;
    }
    slaverCheck->SetNextHandle(boost::shared_ptr<CSCSExecuterCheckHandle>());
    return slaverCheck->Check(set, reports);
}

bool CSCSExecuterChecker::AfterEachSql(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    return true;
}

CSCSExecuterChecker::CSCSExecuterChecker():dataNodesCheck(new CSCSDataNodesCheck()),slaverCheck(new CSCSSlaverCheck())
{

}

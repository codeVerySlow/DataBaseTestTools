#include "util/SCSConfigHelper.h"
#include "SCSPreparedSQLSet.h"
#include "SCSExecuterWrapper.h"
#include "executer/SCSExecuter.h"
#include "DBLog.h"
#include "SCSExecuterChecker.h"
#include "SCSReport.h"

CSCSExecuterWrapper::CSCSExecuterWrapper(): m_srcExcuter(), m_desExcuter(), m_checker(new CSCSExecuterChecker())
{
    //创建执行器
    const STConfig *config = CSCSConfigHelper::GetInstance()->GetConfig();
    switch (config->emModel)
    {
        case Model_SCSDB_SCSDB:
        {
            m_srcExcuter = CSCSExecuter::Create(ExecuterType_SCS, &(config->conSrcSCSDBConnect));
            m_desExcuter = CSCSExecuter::Create(ExecuterType_SCS, &(config->conDesConnect));
            break;
        }
        case Model_SCSDB_MYSQL:
        {
            m_srcExcuter = CSCSExecuter::Create(ExecuterType_MYSQL, &(config->conSrcMysqlConnect));
            m_desExcuter = CSCSExecuter::Create(ExecuterType_SCS, &(config->conDesConnect));
            break;
        }
    }
}

CSCSExecuterWrapper::~CSCSExecuterWrapper()
{
    m_srcExcuter->CloseDataSource();
    m_desExcuter->CloseDataSource();
}

bool CSCSExecuterWrapper::ExecuteSQL(const CSCSPreparedSQLSet &set,const STSQLPair &stsqlPair, boost::shared_ptr<CSCSResultIter> &srcIter,
                                     boost::shared_ptr<CSCSResultIter> &desIter,
                                     std::vector<boost::shared_ptr<const CSCSReport> > &reports, std::string &msg,bool &isStop)
{
    msg="";
    //执行sql前检查
    if (!m_checker->BeforeEachSql(set, reports))
    {
        isStop=true;
        return false;
    }
    if (!(srcIter = m_srcExcuter->ExecuteSQL(CSCSConfigHelper::GetInstance()->GetConfig()->emModel == Model_SCSDB_MYSQL ? stsqlPair.strSQLSource : stsqlPair.strSQLDestination, msg)))
    {
        return false;
    }
    if (!(desIter = m_desExcuter->ExecuteSQL(stsqlPair.strSQLDestination, msg)))
    {
        return false;
    }
    //执行sql后检查
    if (!m_checker->AfterEachSql(set, reports))
    {
        isStop= true;
        return false;
    }
    return true;
}

bool CSCSExecuterWrapper::BeforeTestCaseCheck(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    return m_checker->BeforeTestCase(set, reports);
}

bool CSCSExecuterWrapper::AfterTestCaseCheck(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    return m_checker->AfterTestCase(set, reports);
}

void CSCSExecuterWrapper::SetReportVersion(boost::shared_ptr<CSCSReport> report)
{
    report->setM_strSrcVersion(m_srcExcuter->GetServerVersion());
    report->setM_strDesVersion(m_desExcuter->GetServerVersion());
}

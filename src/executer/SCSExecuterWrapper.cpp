#include "util/SCSConfigHelper.h"
#include "SCSPreparedSQLSet.h"
#include "SCSExecuterWrapper.h"
#include "executer/SCSExecuter.h"
#include "DBLog.h"
#include "SCSExecuterChecker.h"

CSCSExecuterWrapper::CSCSExecuterWrapper():srcExcuter(),desExcuter(),checker(new CSCSExecuterChecker())
{
    const STConfig *config = CSCSConfigHelper::GetInstance()->GetConfig();
    switch (config->emModel)
    {
        case Model_SCSDB_SCSDB:
        {
            srcExcuter = CSCSExecuter::Create(ExecuterType_SCS, &(config->conSrcConnect));
            desExcuter = CSCSExecuter::Create(ExecuterType_SCS, &(config->conDesConnect));
            break;
        }
        case Model_SCSDB_MYSQL:
        {
            srcExcuter = CSCSExecuter::Create(ExecuterType_MYSQL, &(config->conSrcMysqlConnect));
            desExcuter = CSCSExecuter::Create(ExecuterType_SCS, &(config->conDesConnect));
            break;
        }
    }
}

CSCSExecuterWrapper::~CSCSExecuterWrapper()
{
    srcExcuter->CloseDataSource();
    desExcuter->CloseDataSource();
}

bool CSCSExecuterWrapper::ExecuteSQL(const CSCSPreparedSQLSet &set,const STSQLPair &stsqlPair, boost::shared_ptr<CSCSResultIter> &srcIter,
                                     boost::shared_ptr<CSCSResultIter> &desIter,
                                     std::vector<boost::shared_ptr<const CSCSReport> > &reports, std::string &msg)
{
    msg="";
    if (!checker->BeforeEachSql(set,reports))
    {
        msg="before each sql check false";
        return false;
    }
    if (!(srcIter = srcExcuter->ExecuteSQL(CSCSConfigHelper::GetInstance()->GetConfig()->emModel==Model_SCSDB_MYSQL?stsqlPair.strSQLSource:stsqlPair.strSQLDestination, msg)))
    {
        return false;
    }
    if (!(desIter = desExcuter->ExecuteSQL( stsqlPair.strSQLDestination, msg)))
    {
        return false;
    }
    if (!checker->AfterEachSql(set,reports))
    {
        msg="after each sql check false";
        return false;
    }
    return true;
}

bool CSCSExecuterWrapper::BeforeTestCaseCheck(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    return checker->BeforeTestCase(set,reports);
}

bool CSCSExecuterWrapper::AfterTestCaseCheck(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    return checker->AfterTestCase(set,reports);
}

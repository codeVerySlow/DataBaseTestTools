#include "SCSComparerReport.h"
#include "SCSPreparedSQLSet.h"
#include <boost/algorithm/string.hpp>

void CSCSComparerReport::AddTestCaseFailReport(boost::shared_ptr<STTestCaseReport> report,
                                               const CSCSPreparedSQLSet &set)
{
    report->nCaseID = set.m_nCaseID;
    report->strModel = set.m_strModule;
    report->strSrcCaseSql = set.GetCurrent().strSQLSource;
    report->strDesCaseSql = set.GetCurrent().strSQLDestination;

    m_vecFailTestCase.push_back(*report);
}

void CSCSComparerReport::CountSuccess(const std::string &model)
{
    m_success[model] += 1;
}

void CSCSComparerReport::CountFail(const std::string &model)
{
    m_fail[model] += 1;
}

void CSCSComparerReport::AddTestCaseExecuteErrReport(const CSCSPreparedSQLSet &set, const std::string &msg)
{
    STTestCaseReport report;
    report.strSrcCaseSql = set.GetCurrent().strSQLSource;
    report.strDesCaseSql = set.GetCurrent().strSQLDestination;
    report.strModel = set.m_strModule;
    report.m_emDisMatchType = DISMATCHTYPE_SQLERR;
    report.nCaseID = set.m_nCaseID;
    report.strErrMsg = msg;
    m_vecFailTestCase.push_back(report);
}

int CSCSComparerReport::GetSuccess(const std::string &module) const
{
    return m_success[module];
}

int CSCSComparerReport::GetFail(const std::string &module) const
{
    return m_fail[module];
}

#ifndef _COMPARER_SCSCOMPARERREPORT_H_
#define _COMPARER_SCSCOMPARERREPORT_H_

#include <map>
#include <boost/shared_ptr.hpp>
#include "SCSReport.h"

class CSCSPreparedSQLSet;


enum EMDisMatchType
{
    DISMATCHTYPE_COLUM,
    DISMATCHTYPE_ROW,
    DISMATCHTYPE_ROWCOUNT,
    DISMATCHTYPE_SQLERR
};

struct STTestCaseReport
{
    int nCaseID;
    std::string strModel;
    std::string strDesCaseSql;
    std::string strSrcCaseSql;
    std::vector<std::string> desRow;
    std::vector<std::string> srcRow;
    EMDisMatchType m_emDisMatchType;
    std::string strErrMsg;
};


class CSCSComparerReport : public CSCSReport
{
private:
    mutable std::map<std::string,int> m_success;
    mutable std::map<std::string,int> m_fail;
public:
    std::vector<STTestCaseReport> m_vecFailTestCase;


    void AddTestCaseFailReport(boost::shared_ptr<STTestCaseReport> report, const CSCSPreparedSQLSet &set);
    void AddTestCaseExecuteErrReport(const CSCSPreparedSQLSet &set,const std::string &msg);
    void CountSuccess(const std::string &model);
    void CountFail(const std::string &model);
    int GetSuccess(const std::string &module) const;
    int GetFail(const std::string &module) const;
};


#endif

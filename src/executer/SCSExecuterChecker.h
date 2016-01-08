#ifndef _EXECUTER_SCSEXECUTERCHECKER_H_
#define _EXECUTER_SCSEXECUTERCHECKER_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class CSCSReport;
class CSCSDataNodesCheck;
class CSCSSlaverCheck;
class CSCSPreparedSQLSet;

class CSCSExecuterChecker
{
public:
    CSCSExecuterChecker();
    bool BeforeTestCase(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    bool AfterTestCase(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    bool BeforeEachSql(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    bool AfterEachSql(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);

private:
    boost::shared_ptr<CSCSDataNodesCheck> dataNodesCheck;
    boost::shared_ptr<CSCSSlaverCheck> slaverCheck;

};

#endif
#ifndef _INCLUDE_SCSEXECUTERWRAPPER_H_
#define _INCLUDE_SCSEXECUTERWRAPPER_H_

#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class CSCSExecuter;

class STSQLPair;

class CSCSResultIter;

class CSCSReport;
class CSCSExecuterChecker;
class CSCSPreparedSQLSet;

class CSCSExecuterWrapper
{
public:
    CSCSExecuterWrapper();

    ~CSCSExecuterWrapper();

    bool BeforeTestCaseCheck(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);
    bool AfterTestCaseCheck(const CSCSPreparedSQLSet &set,std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    bool ExecuteSQL(const CSCSPreparedSQLSet &set,const STSQLPair &stsqlPair, boost::shared_ptr<CSCSResultIter> &srcIter,
                    boost::shared_ptr<CSCSResultIter> &desIter,
                    std::vector<boost::shared_ptr<const CSCSReport> > &reports, std::string &msg);

private:
    boost::shared_ptr<CSCSExecuter> srcExcuter;
    boost::shared_ptr<CSCSExecuter> desExcuter;
    boost::shared_ptr<CSCSExecuterChecker> checker;
};

#endif
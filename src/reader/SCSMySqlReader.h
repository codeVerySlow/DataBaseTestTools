#ifndef _READER_CSCSMYSQLREADER_H_
#define _READER_CSCSMYSQLREADER_H_

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

#include "SCSReader.h"

class CSCSPreparedSQLSet;
class CSCSMySqlHelper;

class CSCSMySqlReader : public CSCSReader
{
public:
    CSCSMySqlReader();

    ~CSCSMySqlReader();

    bool ReadNextTestCase(CSCSPreparedSQLSet &set);

private:
    int nTestCaseId;
    boost::shared_ptr<CSCSMySqlHelper> mysql;
    bool GetTestCase(const std::string &column,
                     const std::vector<std::vector<std::string> > &vecTestTable,
                     std::vector<std::string> &vecTestCase);


};

#endif

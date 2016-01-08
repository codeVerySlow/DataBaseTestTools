#ifndef _INCLUDE_SCSREADERWRAPPER_H_
#define _INCLUDE_SCSREADERWRAPPER_H_

#include <string>
#include <boost/shared_ptr.hpp>

class CSCSReader;
class CSCSPreparedSQLSet;

class CSCSReaderWrapper
{
public:
    CSCSReaderWrapper();

    ~CSCSReaderWrapper();

    bool ReadNextTestCase(CSCSPreparedSQLSet &set);

private:
    boost::shared_ptr<CSCSReader> reader;
};

#endif
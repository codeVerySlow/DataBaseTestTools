#ifndef _INCLUDE_CSCSPREPAREDSQLSET_H_
#define _INCLUDE_CSCSPREPAREDSQLSET_H_

#include <string>
#include <boost/shared_ptr.hpp>

class CSCSPreparedSQLSet;

class CSCSReader
{
public:
    CSCSReader()
    { };

    virtual ~CSCSReader()
    { };

    virtual bool ReadNextTestCase(CSCSPreparedSQLSet &set) = 0;

    static boost::shared_ptr<CSCSReader> Create();
};

#endif

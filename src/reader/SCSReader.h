#ifndef _INCLUDE_CSCSPREPAREDSQLSET_H_
#define _INCLUDE_CSCSPREPAREDSQLSET_H_
 
#include <string>

class CSCSPreparedSQLSet;

class CSCSReader{
public:
	CSCSReader() {};
	virtual ~CSCSReader() {};
    virtual	bool ReadNextTestCase(CSCSPreparedSQLSet *set)=0;
};

#endif

#ifndef _INCLUDE_SCSREADERWRAPPER_H_
#define _INCLUDE_SCSREADERWRAPPER_H_
#include <string>

class CSCSReader;
class CSCSPreparedSQLSet;

class CSCSReaderWrapper{
public:
	CSCSReaderWrapper();
	~CSCSReaderWrapper();
	CSCSPreparedSQLSet* ReadNextTestCase();
private:
	CSCSReader* reader;
};

#endif
#ifndef _READER_CSCSMYSQLREADER_H_
#define _READER_CSCSMYSQLREADER_H_
#include "SCSReader.h"
#include <vector>
#include <string>

class CSCSMySqlReader:public CSCSReader
{
	public:
		CSCSMySqlReader():nTestCaseId(0){};
		~CSCSMySqlReader();
		
		CSCSPreparedSQLSet ReadNextTestCase();
private:
	int nTestCaseId;
};

#endif

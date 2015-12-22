#ifndef _READER_CSCSMYSQLREADER_H_
#define _READER_CSCSMYSQLREADER_H_

#include <vector>
#include <string>

#include "SCSReader.h"

class CSCSMySqlReader:public CSCSReader
{
	public:
		CSCSMySqlReader();
		~CSCSMySqlReader();
		
		bool ReadNextTestCase(CSCSPreparedSQLSet *set);
private:
	int nTestCaseId;
	bool GetTestCase(const std::string &column,std::vector<std::string> &vecTestCase);
	int GetColumnIndex(const std::string &column,const std::vector<std::string> &vecTestCase);
};

#endif

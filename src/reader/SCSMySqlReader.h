#ifndef _READER_CSCSMYSQLREADER_H_
#define _READER_CSCSMYSQLREADER_H_
#include "SCSReader.h"


class CSCSMySqlReader:public CSCSReader
{
	public:
		CSCSMySqlReader();
		~CSCSMySqlReader();
		
		CSCSPreparedSQLSet ReadTestSQL();
};

#endif

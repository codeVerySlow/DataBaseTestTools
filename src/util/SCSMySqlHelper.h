#ifndef _UTIL_SCSMYSQLHELPER_H_
#define _UTIL_SCSMYSQLHELPER_H_
#include <string>
#include <vector>
#include "mysql/mysql.h"

class CSCSMySqlHelper
{
public:
	CSCSMySqlHelper(){};
	~CSCSMySqlHelper(){};
	bool ConnMySql(const char *host,const int port,const char *user,const char *pwd,const char *db,const char *charset,const char *msg);
	bool Select(const char *sql,std::vector<std::vector<std::string> > *result,const char *msg);
	void CloseMySql();
private:
	MYSQL mysql;
	CSCSMySqlHelper(const CSCSMySqlHelper&);
	void operator=(const CSCSMySqlHelper&);
};

#endif

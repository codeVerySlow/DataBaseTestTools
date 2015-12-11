#include <string>
#include <vector>
#include "lib/mysql/mysql.h"


class CSCSMySqlHelper
{
public:
	CSCSMySqlHelper(){};
	~CSCSMySqlHelper(){};
	int ConnMySql(const char *host,const char *port,const char *user,const char *pwd,const char *db,const char *charset,char *msg);
	std::vector<std::vector<std::string> > Select(const char *sql,char *msg);
	void CloseMySql();
private:
	MYSQL mysql;
	CSCSMySqlHelper(const CSCSMySqlHelper&);
	void operator=(const CSCSMySqlHelper&);
};
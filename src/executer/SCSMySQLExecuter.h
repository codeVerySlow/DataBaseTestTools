#include "SCSExecuter.h"

class CSCSMySqlHelper;

class CSCSMySQLExecuter:public CSCSExecuter
{
public:
	bool OpenDataSource();
	CSCSResultIter ExecuteSQL(const std::string &sql);
	void CloseDataSource();

	bool GetNext(std::vector<std::string> &dataRow);
private:
	CSCSMySqlHelper mysql;
};
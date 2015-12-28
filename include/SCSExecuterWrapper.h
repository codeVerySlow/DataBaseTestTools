#include <string>

class CSCSExecuter;
class CSCSResultIter;

class CSCSExecuterWrapper
{
public:	
	CSCSExecuterWrapper();
	~CSCSExecuterWrapper();
	bool OpenDataSource(const std::string &user,
						const std::string &password,
						const std::string &ip,
						const std::string &port,
						const std::string &database);
	CSCSResultIter* ExecuteSQL(const std::string &sql);	
	void CloseDatasource();	
private:
	CSCSExecuter* excuter;
};
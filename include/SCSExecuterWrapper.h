#include <string>
#include <boost/shared_ptr.hpp>

class CSCSExecuter;
class CSCSResultIter;

enum EMDataBaseType
{
	SCSDB,
	MYSQL,
	ORACL
};

class CSCSExecuterWrapper
{
public:	
	CSCSExecuterWrapper();
	~CSCSExecuterWrapper();
	bool OpenDataSource(const std::string &user,
						const std::strin &password,
						const std::string &ip,
						const std::string &database,
						const EMDataBaseType &databasetype);
	CSCSResultIter ExecuteSQL(const std::string &sql);	
	void CloseDatasource();	
private:
	boost::shared_ptr<CSCSExecuter> excuter;
};
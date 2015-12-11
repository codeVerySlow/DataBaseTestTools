#include <string>
#include <boost/shared_ptr.hpp>

class CSCSExecuter;
class CSCSResultIter;

class CSCSExecuterWrapper
{
public:	
	CSCSExecuterWrapper();
	~CSCSExecuterWrapper();
	bool OpenDataSource(const std::string &user,
						const std::strin &password,
						const std::string &ip,
						const std::string &port,
						const std::string &database);
	boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql);	
	void CloseDatasource();	
private:
	boost::shared_ptr<CSCSExecuter> excuter;
};
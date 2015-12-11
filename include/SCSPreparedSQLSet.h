#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

struct STSQLPair
{
	std::string strSQLSource;
	std::string strSQLDestination;
};

class CSCSPreparedSQLSet
{
public:
	int nCurrentIndex;
	int nTotal;
	bool checkSequence;
	int nExecTimes;
	bool checkDataNodes;
	STSQLPair GetNext();
private:
	std::vector<std::string> vecSQLSource;
	std::vector<std::string> vecSQLDestination;
};


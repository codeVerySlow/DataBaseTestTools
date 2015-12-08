#include <string>
#include <vector>

struct STSQLPair
{
	std::string strSQLSource;
	std::string strSQLDestination;
	int nCycle;
	bool isSequence;
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


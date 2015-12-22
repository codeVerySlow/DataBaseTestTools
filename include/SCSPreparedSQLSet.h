#ifndef _INCLUDE_SCSPREPAREDSQLSET_H_
#define _INCLUDE_SCSPREPAREDSQLSET_H_ 

#include <string>
#include <vector>

class CSCSConfigHelper;
enum EMModule;

struct STSQLPair
{
	std::string strSQLSource;
	std::string strSQLDestination;
};

class CSCSPreparedSQLSet
{
public:
	CSCSPreparedSQLSet( const std::vector<std::string> &vecSQLSource,
						const std::vector<std::string> &vecSQLDestination,
						bool checkSequence,
						std::string strModule,
						int nExecTimes,
						bool checkDataNodes);
	int m_nCurrentIndex;
	int m_nTotal;
	bool m_checkSequence;
	std::string m_strModule;
	int m_nExecTimes;
	bool m_checkDataNodes;
	bool GetNext(STSQLPair *pair);
private:
	std::vector<std::string> m_vecSQLSource;
	std::vector<std::string> m_vecSQLDestination;
};

#endif
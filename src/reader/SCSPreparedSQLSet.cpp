#include "SCSPreparedSQLSet.h"


bool CSCSPreparedSQLSet::GetNext(STSQLPair *pair)
{
	if(m_vecSQLSource.empty())
	{
		return false;
	}
	pair->strSQLSource = m_vecSQLSource.back();
	m_vecSQLSource.pop_back();
	
	if(m_vecSQLDestination.empty())
	{
		return false;
	}
	pair->strSQLDestination = m_vecSQLDestination.back();
	m_vecSQLDestination.pop_back();
	
	m_nCurrentIndex++;

	return true;
}

CSCSPreparedSQLSet::CSCSPreparedSQLSet(const std::vector<std::string> &vecSQLSource, 
									   const std::vector<std::string> &vecSQLDestination,
									   bool checkSequence, 
									   std::string strModule, 
									   int nExecTimes, 
									   bool checkDataNodes,
									   bool init)
	 :m_nCurrentIndex(0),
	 m_nTotal(vecSQLSource.size()),
	 m_checkSequence(checkSequence),
	 m_strModule(strModule),
	 m_nExecTimes(nExecTimes),
	 m_checkDataNodes(checkDataNodes),
	 m_init(init),
	 m_vecSQLSource(vecSQLSource),
	 m_vecSQLDestination(vecSQLDestination)
{

}

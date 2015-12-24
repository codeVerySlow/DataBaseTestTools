#include "SCSPreparedSQLSet.h"


bool CSCSPreparedSQLSet::GetNext(STSQLPair &pair)
{
	if((std::vector<std::string>::size_type)m_nCurrentIndex==m_vecSQLSource.size())
	{
		return false;
	}
	pair.strSQLSource = m_vecSQLSource[m_nCurrentIndex];
	
	if((std::vector<std::string>::size_type)m_nCurrentIndex==m_vecSQLDestination.size())
	{
		return false;
	}
	pair.strSQLDestination = m_vecSQLDestination[m_nCurrentIndex];
	
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

CSCSPreparedSQLSet::CSCSPreparedSQLSet()
	 :m_nCurrentIndex(0),
	 m_nTotal(0),
	 m_checkSequence(false),
	 m_strModule(),
	 m_nExecTimes(0),
	 m_checkDataNodes(false),
	 m_init(false),
	 m_vecSQLSource(),
	 m_vecSQLDestination()
{

}

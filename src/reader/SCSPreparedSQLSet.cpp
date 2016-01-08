#include "SCSPreparedSQLSet.h"


bool CSCSPreparedSQLSet::GetNext(STSQLPair &pair) const
{
    if ((std::vector<std::string>::size_type) m_nCurrentIndex == m_vecSQLSource.size())
    {
        if (--m_nExecTimes > 0)
        {
            m_nCurrentIndex = 0;
        }
        else
        {
            return false;
        }
    }
    pair.strSQLSource = m_vecSQLSource[m_nCurrentIndex];

    if ((std::vector<std::string>::size_type) m_nCurrentIndex == m_vecSQLDestination.size())
    {
        if (--m_nExecTimes > 0)
        {
            m_nCurrentIndex = 0;
        }
        else
        {
            return false;
        }
    }
    pair.strSQLDestination = m_vecSQLDestination[m_nCurrentIndex];

    m_nCurrentIndex++;

    return true;
}


STSQLPair CSCSPreparedSQLSet::GetCurrent() const
{
    STSQLPair pair;
    pair.strSQLDestination = m_vecSQLDestination[m_nCurrentIndex == 0 ? 0 : m_nCurrentIndex - 1];
    pair.strSQLSource = m_vecSQLSource[m_nCurrentIndex == 0 ? 0 : m_nCurrentIndex - 1];
    return pair;
}

#ifndef _INCLUDE_SCSPREPAREDSQLSET_H_
#define _INCLUDE_SCSPREPAREDSQLSET_H_

#include <string>
#include <vector>


struct STSQLPair
{
    std::string strSQLSource;
    std::string strSQLDestination;
};

class CSCSPreparedSQLSet
{
public:

    CSCSPreparedSQLSet(int m_nCurrentIndex, int m_nTotal, bool m_checkSequence, const std::string &m_strModule,
                       int m_nExecTimes, bool m_checkDataNodes, bool m_Init, int m_nCaseID,
                       const std::vector<std::string> &m_vecSQLSource,
                       const std::vector<std::string> &m_vecSQLDestination) : m_nCurrentIndex(m_nCurrentIndex),
                                                                              m_nTotal(m_nTotal),
                                                                              m_checkSequence(m_checkSequence),
                                                                              m_strModule(m_strModule),
                                                                              m_nExecTimes(m_nExecTimes),
                                                                              m_checkDataNodes(m_checkDataNodes),
                                                                              m_Init(m_Init), m_nCaseID(m_nCaseID),
                                                                              m_vecSQLSource(m_vecSQLSource),
                                                                              m_vecSQLDestination(m_vecSQLDestination)
    { };


    CSCSPreparedSQLSet() : m_nCurrentIndex(0),
                           m_nTotal(0),
                           m_checkSequence(false),
                           m_strModule(),
                           m_nExecTimes(0),
                           m_checkDataNodes(false),
                           m_Init(false),
                           m_nCaseID(0),
                           m_vecSQLSource(),
                           m_vecSQLDestination()
    { };

    mutable int m_nCurrentIndex;
    int m_nTotal;
    bool m_checkSequence;
    std::string m_strModule;
    mutable int m_nExecTimes;
    bool m_checkDataNodes;
    bool m_Init;
    int m_nCaseID;

    bool GetNext(STSQLPair &pair) const;

    STSQLPair GetCurrent() const;

private:
    std::vector<std::string> m_vecSQLSource;
    std::vector<std::string> m_vecSQLDestination;
};

#endif

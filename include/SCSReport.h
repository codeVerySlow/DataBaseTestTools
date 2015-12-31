#ifndef _INCLUDE_SCSREPORT_H_
#define _INCLUDE_SCSREPORT_H_

#include <vector>
#include <string>

class CSCSReport
{
public:
    bool m_isSuccess;
    std::string m_strMessage;
    std::string m_strSrcVersion;
    std::string m_strCaseID;
    std::string m_strCaseModule;
    std::string m_strCurrentSQL;
    std::string m_strDesVersion;
    struct tm m_StartTime;
    struct tm m_EndTime;
    struct tm m_RunningTime;

    CSCSReport(bool m_isSuccess, const std::string &m_strMessage, const std::string &m_strSrcVersion,
               const std::string &m_strCaseID, const std::string &m_strCaseModule, const std::string &m_strCurrentSQL,
               const std::string &m_strDesVersion, const tm &m_StartTime, const tm &m_EndTime, const tm &m_RunningTime)
            : m_isSuccess(m_isSuccess), m_strMessage(m_strMessage), m_strSrcVersion(m_strSrcVersion),
              m_strCaseID(m_strCaseID), m_strCaseModule(m_strCaseModule), m_strCurrentSQL(m_strCurrentSQL),
              m_strDesVersion(m_strDesVersion), m_StartTime(m_StartTime), m_EndTime(m_EndTime),
              m_RunningTime(m_RunningTime) { };

    CSCSReport() { };
};


#endif
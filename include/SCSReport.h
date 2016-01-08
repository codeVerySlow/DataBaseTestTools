#ifndef _INCLUDE_SCSREPORT_H_
#define _INCLUDE_SCSREPORT_H_

#include <vector>
#include <string>
#include <time.h>

class CSCSReport
{
public:
    bool isM_isSuccess() const
    {
        return m_isSuccess;
    }

    void setM_isSuccess(bool m_isSuccess)
    {
        CSCSReport::m_isSuccess = m_isSuccess;
    }

    const std::string &getM_strMessage() const
    {
        return m_strMessage;
    }

    void setM_strMessage(const std::string &m_strMessage)
    {
        CSCSReport::m_strMessage = m_strMessage;
    }

    const std::string &getM_strSrcVersion() const
    {
        return m_strSrcVersion;
    }

    void setM_strSrcVersion(const std::string &m_strSrcVersion)
    {
        CSCSReport::m_strSrcVersion = m_strSrcVersion;
    }

    const std::string &getM_strDesVersion() const
    {
        return m_strDesVersion;
    }

    void setM_strDesVersion(const std::string &m_strDesVersion)
    {
        CSCSReport::m_strDesVersion = m_strDesVersion;
    }

    time_t getM_StartTime() const
    {
        return m_StartTime;
    }

    void setM_StartTime(time_t m_StartTime)
    {
        CSCSReport::m_StartTime = m_StartTime;
    }

    time_t getM_EndTime() const
    {
        return m_EndTime;
    }

    void setM_EndTime(time_t m_EndTime)
    {
        CSCSReport::m_EndTime = m_EndTime;
    }

    const std::string &getM_strCurrentSql() const
    {
        return m_strCurrentSql;
    }

    void setM_strCurrentSql(const std::string &m_strCurrentSql)
    {
        CSCSReport::m_strCurrentSql = m_strCurrentSql;
    }

    CSCSReport(bool m_isSuccess, const std::string &m_strMessage, const std::string &m_strSrcVersion,
               const std::string &m_strDesVersion, const std::string &m_strCurrenSql,const time_t &m_StartTime, const time_t &m_EndTime)
            : m_isSuccess(m_isSuccess), m_strMessage(m_strMessage), m_strSrcVersion(m_strSrcVersion),
              m_strDesVersion(m_strDesVersion), m_strCurrentSql(m_strCurrenSql),m_StartTime(m_StartTime), m_EndTime(m_EndTime)
    { };

    CSCSReport() : m_isSuccess(false), m_strMessage(), m_strSrcVersion(), m_strDesVersion(),m_strCurrentSql(), m_StartTime(time(NULL)),m_EndTime(time(NULL))
    { };

    virtual  ~CSCSReport()
    { };

private:
    bool m_isSuccess;
    std::string m_strMessage;
    std::string m_strSrcVersion;
    std::string m_strDesVersion;
    std::string m_strCurrentSql;
    time_t m_StartTime;
    time_t m_EndTime;
};


#endif
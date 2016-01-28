#ifndef _INCLUDE_SCSREPORT_H_
#define _INCLUDE_SCSREPORT_H_

#include <vector>
#include <string>
#include <time.h>

//对比结果报告类
class CSCSReport
{
private:
    //是否成功
    bool m_isSuccess;
    //提示信息
    std::string m_strMessage;
    //源版本
    std::string m_strSrcVersion;
    //目标版本
    std::string m_strDesVersion;
    //当前执行的sql
    std::string m_strCurrentSql;
    //当前执行的用例id
    int m_strCurrentCaseID;
    //当前用例所属模块
    std::string m_strCurrentModel;
    //开始时间
    time_t m_StartTime;
    //结束时间
    time_t m_EndTime;
public:

    int getM_strCurrentCaseID() const
    {
        return m_strCurrentCaseID;
    }

    void setM_strCurrentCaseID(int m_strCurrentCaseID)
    {
        CSCSReport::m_strCurrentCaseID = m_strCurrentCaseID;
    }

    const std::string &getM_strCurrentModel() const
    {
        return m_strCurrentModel;
    }

    void setM_strCurrentModel(const std::string &m_strCurrentModel)
    {
        CSCSReport::m_strCurrentModel = m_strCurrentModel;
    }

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
    {
    };

    virtual  ~CSCSReport()
    { };


};


#endif
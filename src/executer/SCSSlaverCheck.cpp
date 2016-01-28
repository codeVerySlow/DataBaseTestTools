#include <SCSPreparedSQLSet.h>
#include "util/SCSUtilTools.h"
#include "DBLog.h"
#include "util/SCSConfigHelper.h"
#include "SCSReport.h"
#include "SCSSlaverCheck.h"
#include "util/SCSSCSHelper.h"
#include "SCSSlaveCheckReport.h"

bool CSCSSlaverCheck::Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    std::string msg;

    if (!m_pSCSHelper->IsConnect())
    {
        STConnect connect = CSCSConfigHelper::GetInstance()->GetConfig()->conDesConnect;
        if (!m_pSCSHelper->ConnSCS(connect.strIP.c_str(),
                                   connect.nPort,
                                   connect.strUser.c_str(),
                                   connect.strPwd.c_str(),
                                   connect.strDataBase.c_str(),
                                   "UTF8",
                                   msg))
        {
            return Error("SlaverCheck err:connect to SCSDB err:" + msg, set, reports);
        }
    }

    if (!m_pSCSHelper->InitSelect("show slave status", msg))
    {
        return Error("SlaverCheck err:execute check err:" + msg, set, reports);
    }

    //获取节点备份关系信息
    std::vector<std::string> rows;
    if (!m_pSCSHelper->GetNextRow(&rows))
    {
        return Error("SlaverCheck err:can not query slave status", set, reports);
    }
    int slaveIOIndex = SCSUtilTools::GetColumnIndex("Slave_IO_Running", rows);
    int slaveSQLIndex = SCSUtilTools::GetColumnIndex("Slave_SQL_Running", rows);
    while (m_pSCSHelper->GetNextRow(&rows))
    {
        //节点备份异常
        if (rows[slaveIOIndex] != "Yes" || rows[slaveSQLIndex] != "Yes")
        {
            boost::shared_ptr<CSCSSlaveCheckReport> report(new CSCSSlaveCheckReport(rows[0], rows[1]));
            report->setM_strCurrentSql(set.GetCurrent().strSQLDestination);
            report->setM_strDesVersion(m_pSCSHelper->GetServerVersion());
            reports.push_back(report);
            return false;
        }
    }

    if (GetNextHandle())
    {
        return GetNextHandle()->Check(set, reports);
    }

    return true;
}

CSCSSlaverCheck::CSCSSlaverCheck() : m_pSCSHelper(new CSCSSCSHelper())
{

}

bool CSCSSlaverCheck::Error(const std::string &msg, const CSCSPreparedSQLSet &set,
                            std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    boost::shared_ptr<CSCSSlaveCheckReport> report(new CSCSSlaveCheckReport());
    LOG_ERROR(msg.c_str());
    report->setM_isSuccess(false);
    report->setM_strMessage(msg);
    report->setM_strCurrentSql(set.GetCurrent().strSQLDestination);
    reports.push_back(report);
    return false;
}

CSCSSlaverCheck::~CSCSSlaverCheck()
{
    m_pSCSHelper->CloseSCS();
}

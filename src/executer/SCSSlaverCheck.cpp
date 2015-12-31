#include <util/SCSUtilTools.h>
#include <resultwriter/SCSSlaveCheckReport.h>
#include "DBLog.h"
#include "util/SCSConfigHelper.h"
#include "SCSReport.h"
#include "SCSSlaverCheck.h"
#include "util/SCSSCSHelper.h"
bool CSCSSlaverCheck::Check(std::vector<boost::shared_ptr<CSCSReport> > &reports)
{
    std::string msg;

    if(!m_pSCSHelper->IsConnect())
    {
        STConnect connect=CSCSConfigHelper::GetInstance()->GetConfig()->conDesConnect;
        if(!m_pSCSHelper->ConnSCS(connect.strIP.c_str(),
                              connect.nPort,
                              connect.strUser.c_str(),
                              connect.strPwd.c_str(),
                              connect.strDataBase.c_str(),
                              "UTF8",
                              msg))
        {
            return Error("SlaverCheck err:connect to SCSDB err:"+msg,reports);
        }
    }

    if(!m_pSCSHelper->InitSelect("show slave status",msg))
    {
        return Error("SlaverCheck err:execute check err:"+msg,reports);
    }

    std::vector<std::string> rows;
    if(!m_pSCSHelper->GetNextRow(&rows))
    {
        return Error("SlaverCheck err:can not query slave status",reports);
    }
    int slaveIOIndex=SCSUtilTools::GetColumnIndex("Slave_IO_Running",rows);
    int slaveSQLIndex=SCSUtilTools::GetColumnIndex("Slave_SQL_Running",rows);
    while(m_pSCSHelper->GetNextRow(&rows))
    {
        if(rows[slaveIOIndex]!="Yes"||rows[slaveSQLIndex]!="Yes")
        {
            boost::shared_ptr<CSCSSlaveCheckReport> report(new CSCSSlaveCheckReport(rows[0],rows[1]));
            return false;
        }
    }

    if(GetNextHandle())
    {
        return GetNextHandle()->Check(<#initializer#>);
    }

    return true;
}

CSCSSlaverCheck::CSCSSlaverCheck():m_pSCSHelper(new CSCSSCSHelper())
{

}

bool CSCSSlaverCheck::Error(const std::string &msg, std::vector<boost::shared_ptr<CSCSReport> > &reports) {
    boost::shared_ptr<CSCSSlaveCheckReport> report(new CSCSSlaveCheckReport());
    LOG_ERROR(msg.c_str());
    report->m_isSuccess=false;
    report->m_strMessage=msg;
    reports.push_back(report);
    return false;
}

#include <SCSPreparedSQLSet.h>
#include "util/SCSConfigHelper.h"
#include "util/SCSUtilTools.h"
#include "SCSSlaveCheckReport.h"
#include "SCSDataNodeReport.h"
#include "DBLog.h"
#include "SCSDataNodesCheck.h"

bool CSCSDataNodesCheck::Check(const CSCSPreparedSQLSet &set, std::vector<boost::shared_ptr<const CSCSReport> > &reports)
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
            return Error("SlaverCheck err:connect to SCSDB err:" + msg, reports);
        }
    }
    if (!m_pSCSHelper->InitSelect("show table status", msg))
    {
        return Error("DataNodesCheck err:execute check err:" + msg, reports);
    }

    std::vector<std::string> rows;
    if (!m_pSCSHelper->GetNextRow(&rows))
    {
        return Error("DataNodesCheck err:can not query data nodes", reports);
    }

    boost::shared_ptr<CSCSDataNodeReport> report(new CSCSDataNodeReport());
    std::vector<STNode> nodes;
    int rowsIndex = SCSUtilTools::GetColumnIndex("Rows", rows);
    int tableIndex = SCSUtilTools::GetColumnIndex("Name", rows);
    while (m_pSCSHelper->GetNextRow(&rows))
    {
        nodes.push_back(STNode(rows[0], rows[1], rows[tableIndex], rows[rowsIndex]));
    }
    report->setNodeCount(nodes);
    reports.push_back(report);
    if (GetNextHandle())
    {
        return GetNextHandle()->Check(set, reports);
    }

    return true;
}

bool CSCSDataNodesCheck::Error(const std::string &msg, std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    boost::shared_ptr<CSCSDataNodeReport> report(new CSCSDataNodeReport());
    report->setM_strMessage(msg);
    report->setM_isSuccess(false);
    reports.push_back(report);
    LOG_ERROR(msg.c_str());
    return false;
}

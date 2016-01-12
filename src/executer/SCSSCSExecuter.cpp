#include "DBLog.h"
#include "SCSSCSExecuter.h"
#include "SCSResultIter.h"
#include "util/SCSSCSHelper.h"
#include "util/SCSConfigHelper.h"

boost::shared_ptr<CSCSResultIter> CSCSSCSExecuter::ExecuteSQL(const std::string &sql, std::string &msg)
{
    if (!scs->IsConnect())
    {
        if (!scs->ConnSCS(m_pConnect->strIP.c_str(),
                          m_pConnect->nPort,
                          m_pConnect->strUser.c_str(),
                          m_pConnect->strPwd.c_str(),
                          m_pConnect->strDataBase.c_str(),
                          "UTF8",
                          msg))
        {
            LOG_ERROR(("Executer open mysql m_pConnect err" + msg).c_str());
            return boost::shared_ptr<CSCSResultIter>();
        }
    }
    LOG_DEBUG(("SCSDB Execute sql:" + sql).c_str());
    if (!scs->InitSelect(sql.c_str(), msg))
    {
        LOG_ERROR(("SCSDB Execute sql error:" + msg).c_str());
        return boost::shared_ptr<CSCSResultIter>();
    }
    return boost::shared_ptr<CSCSResultIter>(new CSCSResultIter(this));
}

void CSCSSCSExecuter::CloseDataSource()
{
    m_isClose=true;
    scs->CloseSCS();
}

bool CSCSSCSExecuter::GetNext(std::vector<std::string> &dataRow)
{
    return scs->GetNextRow(&dataRow);
}



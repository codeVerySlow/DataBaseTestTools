#include <string>
#include <vector>
#include <string.h>
#include "scsdbclient.h"
#include "scsdberror.h"

#include "SCSSCSHelper.h"
#include "SCSUtilTools.h"

bool CSCSSCSHelper::ConnSCS(const char *host, const int port, const char *user, const char *pwd, const char *db,
                            const char *charset, std::string &msg)
{
    if (NULL == (m_scsdb = scsdb_open(host, user, pwd, db)))
    {
        msg = "connect scsdb fail!";
        return false;
    }
    return true;
}

bool CSCSSCSHelper::InitSelect(const char *sql, std::string &msg)
{
    if(!m_isReadFinish)
    {
        scsdb_release(m_scsdb);
    }
    if (0 != scsdb_execute(m_scsdb, sql, strlen(sql)))
    {
        msg = scsdb_error_string(m_scsdb);
        m_nColNum=0;
        m_isReadColunm=true;
        m_isReadAffect=true;
        m_isReadFinish=true;
        return false;
    }
    m_nColNum = scsdb_colum_num(m_scsdb);
    m_isReadAffect=false;
    m_isReadColunm=false;
    m_isReadFinish= false;
    return true;
}

bool CSCSSCSHelper::GetNextRow(std::vector<std::string> *dataRow)
{
    dataRow->clear();
    if (m_nColNum > 0)
    {
        if (!m_isReadColunm)
        {
            int i=0;
            if(strcmp(scsdb_column_name(m_scsdb, 0),"scshashval")==0)
                i=1;
            for (; i < m_nColNum; i++)
            {
                dataRow->push_back(scsdb_column_name(m_scsdb, i));
            }
            m_isReadColunm = true;
            return true;
        }

        if (scsdb_read_row(m_scsdb) != __READ_ROW_END)
        {
            int i=0;
            if(strcmp(scsdb_column_name(m_scsdb, 0),"scshashval")==0)
                i=1;
            for (; i < m_nColNum; i++)
            {
                const char *row = scsdb_read_field(m_scsdb, i);
                dataRow->push_back(row == NULL ? "NULL" : row);
            }
            return true;
        }
        else
        {
            m_isReadFinish=true;
        }
    }
    else
    {
        if (!m_isReadAffect)
        {
            dataRow->push_back(SCSUtilTools::NumberToString<long long>(scsdb_affected_rows(m_scsdb)));
            m_isReadAffect = true;
            return true;
        }
    }
    scsdb_release(m_scsdb);
    return false;
}

void CSCSSCSHelper::CloseSCS()
{
    if(!m_isReadFinish)
    {
        scsdb_release(m_scsdb);
    }
    scsdb_close(m_scsdb);
    m_isClose=true;
}

bool CSCSSCSHelper::IsConnect()
{
    return m_scsdb != NULL;
}

std::string CSCSSCSHelper::GetServerVersion()
{
    if(!IsConnect())
        return "";
    return scsdb_get_ver(m_scsdb);
}

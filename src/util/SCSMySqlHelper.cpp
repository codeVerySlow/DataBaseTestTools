#include "SCSMySqlHelper.h"
#include "util/SCSUtilTools.h"

bool CSCSMySqlHelper::ConnMySql(const char *host, const int port, const char *user, const char *pwd, const char *db,
                                const char *charset, std::string &msg)
{
    if ((mysql = mysql_init(NULL)) == NULL)
    {
        msg = "mysql init err";
        return false;
    }

    if (mysql_real_connect(mysql, host, user, pwd, db, port, NULL, CLIENT_MULTI_STATEMENTS) == NULL)
    {
        msg = "connect to database error";
        return false;
    }

    if (mysql_set_character_set(mysql, charset) != 0)
    {
        msg = "mysql_set_character_set Error";
        return false;
    }

    return true;
}

bool CSCSMySqlHelper::Select(const char *sql, std::vector<std::vector<std::string> > *result, std::string &msg)
{
    InitSelect(sql, msg);

    std::vector<std::string> vecDatarow;
    while (GetNextRow(&vecDatarow))
    {
        result->push_back(vecDatarow);
    }

    return true;
}

void CSCSMySqlHelper::CloseMySql()
{
    if(!m_isReadFinish)
    {
        mysql_free_result(m_res);
    }
    mysql_close(mysql);
    m_isClose=true;
}

bool CSCSMySqlHelper::InitSelect(const char *sql, std::string &msg)
{
    if(!m_isReadFinish)
    {
        mysql_free_result(m_res);
    }
    if (mysql_query(mysql, sql))
    {
        msg = mysql_error(mysql);
        m_isSelect = true;
        m_isReadAffect = true;
        m_isReadFinish = true;
        return false;
    }

    m_isSelect = true;
    m_isReadAffect = false;
    m_isReadFinish = false;

    if (!(m_res = mysql_store_result(mysql)))
    {
        if (mysql_field_count(mysql) == 0)
        {
            m_isSelect = false;
        }
        else // mysql_store_result() should have returned data
        {
            msg = "store result error";
            return false;
        }
    }

    return true;
}

bool CSCSMySqlHelper::GetNextRow(std::vector<std::string> *dataRow)
{
    MYSQL_FIELD *fd;
    int i;
    dataRow->clear();

    if (!m_isSelect)
    {
        if (!m_isReadAffect)
        {
            dataRow->push_back(SCSUtilTools::NumberToString(mysql_affected_rows(mysql)));
            m_isReadAffect = true;
            return true;
        }
        while(mysql_next_result(mysql)==0)
        {
            m_res = mysql_store_result(mysql);
            if (m_res)
            {
                /* yes; process rows and free the result set */
                mysql_free_result(m_res);
            }
        }
        return false;
    }

    while ((fd = mysql_fetch_field(m_res)))
    {
        std::string column(fd->name);
        dataRow->push_back(column);
    }

    if (dataRow->size() > 0)
    {
        return true;
    }

    MYSQL_ROW sql_row;
    int j = mysql_num_fields(m_res);

    if ((sql_row = mysql_fetch_row(m_res)))
    {
        for (i = 0; i < j; i++)
        {
            std::string filed(sql_row[i] == NULL ? "NULL" : sql_row[i]);
            dataRow->push_back(filed);
        }
        return true;
    }
    else
    {
        m_isReadFinish = true;
    }

    mysql_free_result(m_res);
    return false;
}

bool CSCSMySqlHelper::IsConnect()
{
    return mysql != NULL;
}

std::string CSCSMySqlHelper::GetServerVersion()
{
    return mysql_get_server_info(mysql);
}

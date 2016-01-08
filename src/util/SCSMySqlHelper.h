#ifndef _UTIL_SCSMYSQLHELPER_H_
#define _UTIL_SCSMYSQLHELPER_H_

#include <string>
#include <vector>
#include <mysql/mysql.h>

class CSCSMySqlHelper
{
public:
    CSCSMySqlHelper():mysql(NULL),
                      m_res(NULL),
                      m_isSelect(false),
                      m_isReadAffect(true),
                      m_isReadFinish(true)
    { };

    ~CSCSMySqlHelper()
    { };

    bool ConnMySql(const char *host, const int port, const char *user, const char *pwd, const char *db,
                   const char *charset, std::string &msg);

    bool Select(const char *sql, std::vector<std::vector<std::string> > *result, std::string &msg);

    bool InitSelect(const char *sql, std::string &msg);

    bool GetNextRow(std::vector<std::string> *dataRow);

    void CloseMySql();

    bool IsConnect();

private:
    MYSQL *mysql;
    MYSQL_RES *m_res;
    bool m_isSelect;
    bool m_isReadAffect;
    bool m_isReadFinish;
    CSCSMySqlHelper(const CSCSMySqlHelper &);

    void operator=(const CSCSMySqlHelper &);
};

#endif

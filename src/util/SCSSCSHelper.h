#ifndef _UTIL_SCSSCSHELPER_H_
#define _UTIL_SCSSCSHELPER_H_

#include "scsdbclient.h"
#include "scsdberror.h"

class CSCSSCSHelper
{
public:
    CSCSSCSHelper():m_scsdb(NULL),
                    m_isReadColunm(false),
                    m_isReadAffect(false),
                    m_isReadFinish(true),
                    m_nColNum(0),
                    m_isClose(false)
    { };

    ~CSCSSCSHelper()
    {
        if(!m_isClose)
            CloseSCS();
    };

    bool ConnSCS(const char *host, const int port, const char *user, const char *pwd, const char *db,
                 const char *charset, std::string &msg);

    bool InitSelect(const char *sql, std::string &msg);

    bool GetNextRow(std::vector<std::string> *dataRow);

    std::string GetServerVersion();

    void CloseSCS();

    bool IsConnect();

private:
    SCSDB m_scsdb;
    bool m_isReadColunm;
    bool m_isReadAffect;
    bool m_isReadFinish;
    int m_nColNum;
    bool m_isClose;
};

#endif

#ifndef _UTIL_SCSSCSHELPER_H_
#define _UTIL_SCSSCSHELPER_H_
#include "scsdbclient.h"
#include "scsdberror.h"

class CSCSSCSHelper
{
public:
	CSCSSCSHelper(){};
	~CSCSSCSHelper(){};
	bool ConnSCS(const char *host,const int port,const char *user,const char *pwd,const char *db,const char *charset,std::string &msg);
	bool InitSelect(const char *sql,std::string &msg);
	bool GetNextRow(std::vector<std::string> *dataRow);
	void CloseSCS();
	bool IsConnect();
private:
	SCSDB m_scsdb;
	bool m_isReadColunm;
	bool m_isReadAffect;
	int m_nColNum;
};

#endif

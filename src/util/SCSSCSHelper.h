#ifndef _UTIL_SCSSCSHELPER_H_
#define _UTIL_SCSSCSHELPER_H_


class CSCSSCSHelper
{
public:
	CSCSSCSHelper(){};
	~CSCSSCSHelper(){};
	bool ConnSCS(const char *host,const int port,const char *user,const char *pwd,const char *db,const char *charset,std::string &msg);
	bool InitSelect(const char *sql,std::string &msg);
	bool GetNextRow(std::vector<std::string> *dataRow);
	void CloseSCS();
};

#endif

#include <iostream>
#include <string>
#include <map>

enum STModel
{
	scsdb=0,
	mysql=1
};

enum STCharset
{
	utf8=0,
	gbk=1,
	latin1=2
};

struct STConnect
{
	std::string strIP;
	std::string strUser;
	std::string strPwd;
	std::string strDataBase;
};

struct STConfig
{
	STConnect SrcConnect;
	STConnect DesConnect;
	STConnect SrcMysqlConnect;
	STModel Model;
	STCharset Charset;
	int Cycle;
	bool Loginfo;
	bool Slavestatus;
};

class CSCSConfigHelper
{
	public:
		const CSCSConfigHelper* GetInstance();
		~CSCSConfigHelper();
		const STConfig* Read();
	private:
		CSCSConfigHelper();
		static STConfig* config;
		static const  CSCSConfigHelper* instance;

		bool IsSpace(const char c);
		void Trim(std::string *str);
		bool IsCommentChar(const char c);
		bool AnalyseLine(const std::string &line,std::string *key,std::string *value);
		bool IsCategory(const std::string &line,std::string *category);

};


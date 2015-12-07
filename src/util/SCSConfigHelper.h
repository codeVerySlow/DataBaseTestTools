#include <iostream>
#include <string>
#include <map>

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
};


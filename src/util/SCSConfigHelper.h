#ifndef _UTIL_SCSCONFIGHELPER_H_
#define _UTIL_SCSCONFIGHELPER_H_
#include <iostream>
#include <string>
#include <map>
#include <vector>

template <class EnumType>
struct SEnumName
{
	static const int Count;
	static const char *List[];
};

enum EMDataBaseType
{
	DataBaseType_SCSDB,
	DataBaseType_MYSQL,
	DataBaseType_ORACL
};

enum EMModel
{
	Model_SCSDB_SCSDB,
	Model_SCSDB_MYSQL
};



struct STConnect
{
	std::string strIP;
	std::string strPort;
	std::string strUser;
	std::string strPwd;
	std::string strDataBase;
};

struct STConfig
{
	STConnect conSrcConnect;
	STConnect conDesConnect;
	STConnect conSrcMysqlConnect;
	EMModel emModel;
	std::string strCharset;
	int nCycle;
	bool checkSlavestatus;
	std::string strModules;
};

class CSCSConfigHelper
{
	public:
		static CSCSConfigHelper* GetInstance();
		~CSCSConfigHelper();
		bool Read();
		static const STConfig* GetConfig();
	private:
		CSCSConfigHelper();

		static STConfig* Config();
		bool IsSpace(const char c);
		void Trim(std::string *str);
		bool IsCommentChar(const char c);
		bool AnalyseLine(const std::string &line,std::string *key,std::string *value);
		bool IsCategory(const std::string &line,std::string *category);
		template <typename EnumType>
		EnumType ConvertStringToEnum( const char *pStr);
};

#endif

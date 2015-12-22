#ifndef _INCLUDE_SCSCONFIGHELPER_H_
#define _INCLUDE_SCSCONFIGHELPER_H_
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
	SCSDB,
	MYSQL,
	ORACL
};

enum EMModel
{
	SCSDB,
	MYSQL
};

template<>
const int SEnumName<EMModel>::Count=2;

template<>
const char*  SEnumName<EMModel>::List[]=
{
	"scsdb-scsdb",
	"scsdb-mysql"
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
		static const CSCSConfigHelper* GetInstance();
		~CSCSConfigHelper();
		bool Read() const;
		const STConfig* GetConfig() const;
	private:
		CSCSConfigHelper();
		static STConfig* config;
		static CSCSConfigHelper* const instance;

		bool IsSpace(const char c);
		void Trim(std::string *str);
		bool IsCommentChar(const char c);
		bool AnalyseLine(const std::string &line,std::string *key,std::string *value);
		bool IsCategory(const std::string &line,std::string *category);
		template <typename EnumType>
		EnumType ConvertStringToEnum( const char *pStr);
};

#endif

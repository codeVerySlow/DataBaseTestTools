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
	"scsdb",
	"mysql"
};

enum EMCharset
{
	UTF8,
	GBK,
	LATIN1
};

template<>
const int SEnumName<EMCharset>::Count=3;

template<>
const char* SEnumName<EMCharset>::List[]=
{
	"utf8",
	"gbk",
	"latin1"	
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
	STConnect SrcConnect;
	STConnect DesConnect;
	STConnect SrcMysqlConnect;
	EMModel Model;
	EMCharset Charset;
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
		template <typename EnumType>
			EnumType ConvertStringToEnum( const char *pStr);
};

#endif
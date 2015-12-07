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

enum STModel
{
	SCSDB,
	MYSQL
};

template<>
const int SEnumName<STModel>::Count=2;

template<>
const char*  SEnumName<STModel>::List[]=
{
	"scsdb",
	"mysql"
};

enum STCharset
{
	UTF8,
	GBK,
	LATIN1
};

template<>
const int SEnumName<STCharset>::Count=3;

template<>
const char* SEnumName<STCharset>::List[]=
{
	"utf8",
	"gbk",
	"latin1"	
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
		template <typename EnumType>
			EnumType ConvertStringToEnum( const char *pStr);
};


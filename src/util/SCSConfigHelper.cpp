#include <fstream>
#include <iostream>
#include <string.h>

#include "SCSConfigHelper.h"
#include "SCSUtilTools.h"
#include "DBLog.h"
#define COMMENT_CHAR '#'

template<>
const int SEnumName<EMModel>::Count=2;

template<>
const char*  SEnumName<EMModel>::List[]=
{
	"scsdb-scsdb",
	"scsdb-mysql"
};

CSCSConfigHelper::CSCSConfigHelper()
{
	
}

CSCSConfigHelper::~CSCSConfigHelper()
{

}


bool CSCSConfigHelper::Read() 
{
	std::map<std::string,std::map<std::string,std::string> > m;
	std::ifstream infile("/etc/scs/RoboTester.conf");
	if(!infile)
	{
		LOG_ERROR("Config file open error");
		return false;
	}
	LOG_DEBUG("read config file:");
	std::string line, category, key, value;
	while(getline(infile,line))
	{
		if(IsCategory(line,&category))
		{
			continue;
		}

		if(AnalyseLine(line,&key,&value))
		{
			m[category][key]=value;
			LOG_DEBUG((key+":"+m[category][key]).c_str());
		}
	}

	infile.close();

	Config()->conSrcConnect.strPwd=m["src_scsdb"]["pwd"];
	Config()->conSrcConnect.strIP=m["src_scsdb"]["hosts"];
	Config()->conSrcConnect.strUser=m["src_scsdb"]["user"];
	Config()->conSrcConnect.strDataBase=m["src_scsdb"]["db"];
	Config()->conSrcConnect.nPort =SCSUtilTools::StringToNumber<int>(m["src_scsdb"]["port"]);

	Config()->conDesConnect.strPwd=m["dest_scsdb"]["pwd"];
	Config()->conDesConnect.strIP=m["dest_scsdb"]["hosts"];
	Config()->conDesConnect.strUser=m["dest_scsdb"]["user"];
	Config()->conDesConnect.strDataBase=m["dest_scsdb"]["db"];
	Config()->conDesConnect.nPort =SCSUtilTools::StringToNumber<int>(m["dest_scsdb"]["port"]);

	Config()->conSrcMysqlConnect.strPwd=m["src_mysql"]["pwd"];
	Config()->conSrcMysqlConnect.strIP=m["src_mysql"]["host"];
	Config()->conSrcMysqlConnect.strUser=m["src_mysql"]["user"];
	Config()->conSrcMysqlConnect.strDataBase=m["src_mysql"]["db"];
	Config()->conSrcMysqlConnect.nPort =SCSUtilTools::StringToNumber<int>(m["src_mysql"]["port"]);

	Config()->conCaseMysqlConnect.strPwd=m["case_mysql"]["pwd"];
	Config()->conCaseMysqlConnect.strIP=m["case_mysql"]["host"];
	Config()->conCaseMysqlConnect.strUser=m["case_mysql"]["user"];
	Config()->conCaseMysqlConnect.strDataBase=m["case_mysql"]["db"];
	Config()->conCaseMysqlConnect.nPort =SCSUtilTools::StringToNumber<int>(m["case_mysql"]["port"]);


	Config()->emModel=ConvertStringToEnum<EMModel>(m["mode"]["mode"].c_str());	

	Config()->nCycle=SCSUtilTools::StringToNumber<int>(m["cycle"]["cycle"]);
	Config()->checkSlavestatus=(m["slavestatus"]["slavestatus"]=="on");
	
	Config()->strModules=m["modules"]["modules"];

	return true;
}

bool CSCSConfigHelper::IsSpace(const char c)
{
	return (' '==c)||('\t'==c);
}

void CSCSConfigHelper::Trim(std::string *str)
{
	if(str->empty())
	  return;

	unsigned int  i,begin,end;
	for(i=0;i<str->size();i++)
	{
		if(!IsSpace((*str)[i]))
		{
			begin=i;
			break;
		}
	}

	if(i==str->size())
	{
		*str="";
		return;
	}

	for(i=str->size();i>=1;i--)
	{
		if(!IsSpace((*str)[i]))
		{
			break;
		}
	}

	end=i;

	*str=str->substr(begin,end-begin+1);
	return;
}

bool CSCSConfigHelper::IsCommentChar(const char c)
{
	return c==COMMENT_CHAR;
}

bool CSCSConfigHelper::AnalyseLine(const std::string &line,std::string *key,std::string *value)
{
	if(line.empty())
	{
		return false;
	}

	int  pos=0,end=line.size()-1;	

	if((pos=line.find(COMMENT_CHAR))!=-1)
	{
		if(0==pos)
		{
			return false;
		}
		end=pos-1;		
	}

	std::string strconfig=line.substr(0,end+1);

	if((pos=strconfig.find('='))==-1)
	{
		return false;
	}

	*key=strconfig.substr(0,pos);
	*value=strconfig.substr(pos+1,end-pos-1);

	return true;
}

bool CSCSConfigHelper::IsCategory(const std::string &line,std::string *category)
{
	if(line.empty())
	{
		return false;
	}

	int pos=0,end=line.size()-1;
	if((pos=line.find('['))!=-1)
	{
		if((end=line.find(']'))!=-1)
		{
			*category=line.substr(pos+1,end-pos-1);
			return true;
		}
	}

	return false;
}

template <typename EnumType>
EnumType CSCSConfigHelper::ConvertStringToEnum(const char *pStr)
{
	EnumType fooEnum = static_cast <EnumType>(-1);
	int count = SEnumName<EnumType>::Count;

	for ( int i = 0; i < count; ++i)
	{	         
		if (strcmp(pStr,SEnumName<EnumType>::List[i]))
		{
			fooEnum = static_cast <EnumType>(i);
			break ;
		}
	}
	return fooEnum;
}

#include <fstream>
#include <iostream>
#include <string.h>

#include "DBLog.h"
#include "SCSConfigHelper.h"
#include "SCSCrc32c.h"
#define COMMENT_CHAR '#'

STConfig* CSCSConfigHelper::config=new STConfig;

CSCSConfigHelper* const CSCSConfigHelper::instance=new CSCSConfigHelper;

CSCSConfigHelper::CSCSConfigHelper()
{
	
}

CSCSConfigHelper::~CSCSConfigHelper()
{

}

const CSCSConfigHelper*  CSCSConfigHelper::GetInstance()
{
	return CSCSConfigHelper::instance;
}

bool CSCSConfigHelper::Read()
{
	std::map<std::string,std::map<std::string,std::string> > m;
	std::ifstream infile("/etc/scs/RoboTester.conf");
	if(!infile)
	{
		std::cerr<<"Config file open error"<<std::endl;
		return false;
	}

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
		}
	}

	infile.close();

	CSCSConfigHelper::config->conSrcConnect.strPwd=m["src_scsdb"]["pwd"];
	CSCSConfigHelper::config->conSrcConnect.strIP=m["src_scsdb"]["hosts"];
	CSCSConfigHelper::config->conSrcConnect.strUser=m["src_scsdb"]["user"];
	CSCSConfigHelper::config->conSrcConnect.strDataBase=m["src_scsdb"]["db"];
	CSCSConfigHelper::config->conSrcConnect.strPort=m["src_scsdb"]["port"];

	CSCSConfigHelper::config->conDesConnect.strPwd=m["dest_scsdb"]["pwd"];
	CSCSConfigHelper::config->conDesConnect.strIP=m["dest_scsdb"]["hosts"];
	CSCSConfigHelper::config->conDesConnect.strUser=m["dest_scsdb"]["user"];
	CSCSConfigHelper::config->conDesConnect.strDataBase=m["dest_scsdb"]["db"];
	CSCSConfigHelper::config->conDesConnect.strPort=m["dest_scsdb"]["port"];

	CSCSConfigHelper::config->emModel=ConvertStringToEnum<EMModel>(m["mode"]["mode"].c_str());	
	CSCSConfigHelper::config->strCharset=m["charset"]["charset"];

	CSCSConfigHelper::config->nCycle=crc32c::StringToNumber<int>(m["cycle"]["cycle"]);
	CSCSConfigHelper::config->checkSlavestatus=(m["slavestatus"]["slavestatus"]=="on");
	
	CSCSConfigHelper::config->strModules=m["modules"]["modules"];

	return true;
}

const STConfig* CSCSConfigHelper::GetConfig()
{
	return CSCSConfigHelper::config;
}

bool CSCSConfigHelper::IsSpace(const char c)
{
	return (' '==c)||('\t'==c);
}

void CSCSConfigHelper::Trim(std::string *str)
{
	if(str->empty())
	  return;

	long  i,begin,end;
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

	*key=strconfig.substr(0,pos+1);
	*value=strconfig.substr(pos,end-pos+1);

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
			*category=line.substr(pos,end-pos+1);
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

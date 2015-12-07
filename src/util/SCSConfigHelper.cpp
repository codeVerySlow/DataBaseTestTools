#include "SCSConfigHelper.h"
#define COMMENT_CHAR '#'
STConfig* CSCSConfigHelper::config=new STConfig;

const CSCSConfigHelper* CSCSConfigHelper::instance=new CSCSConfigHelper;

const CSCSConfigHelper*  CSCSConfigHelper::GetInstance()
{
	return CSCSConfigHelper::instance;
}

const STConfig* CSCSConfigHelper::Read()
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

	ulong  i,begin,end;
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

	key=strconfig.substr(0,pos+1);
	value=strconfig.substr(pos,end-pos+1);
}

#include <fstream>
#include <string>
#include <assert.h>
#include "SCSFileComparer.h"
#include "SCSResultIter.h"
#include "util/SCSSortCache.h"
#include "util/SCSCrc32c.h"

CSCSFileComparer::CSCSFileComparer()
{
}

bool CSCSFileComparer::Compare(CSCSResultIter *iter1,CSCSResultIter *iter2)
{
	SortResultIter(iter1,"sort_crc_1");
	SortResultIter(iter2,"sort_crc_2");

	std::ifstream file1("sort_crc_1");
	std::ifstream file2("sort_crc_2");
	std::string crc1;
	std::string crc2;

	while(1)
	{
		getline(file1,crc1);
		getline(file2,crc2);
		if(file1.eof()||file2.eof())
		{
			break;
		}

		if(crc1!=crc2)
		{
			return false;
		}
	}
	if(file1.eof()&&file2.eof())
	{
		file1.close();
		file2.close();
		return true;
	}
	else
	{
		file1.close();
		file2.close();
		return false;
	}
}

void CSCSFileComparer::SortResultIter(CSCSResultIter *iter,const std::string &fileName)
{

	unsigned int max,min,total,k=10240000;
	WriteCRCToCache(iter,"unsort_crc",&max,&min,&total);
}

void CSCSFileComparer::WriteCRCToCache(CSCSResultIter *iter,CSCSSortCache &cache)
{


	while(1)
	{
		std::vector<std::string> iterData=iter->GetNext();

		if(iterData.size()==0)
		{
			break;
		}

		std::vector<std::string>::iterator iterator=iterData.begin();
		std::string combinStr;

		while(iterator!=iterData.end())
		{
			combinStr+=*iterator++;	
			combinStr+=" ";
		}

		WriteToFile(combinStr,iter->GetCaseId());

		unsigned int crc=crc32c::Value(combinStr.c_str(),combinStr.size());

		cache<<crc;
	}
}


void CSCSFileComparer::WriteToFile(const std::string &data,const std::string &fileName)
{
	
}



bool CSCSFileComparer::CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2)
{
	while(1)
	{
		std::vector<std::string> iter1Data=iter1->GetNext();
		std::vector<std::string> iter2Data=iter2->GetNext();

		if(iter1Data.size()==0&&iter2Data.size()==0)
		{
			return true;
		}
		else if(iter1Data.size()!=iter2Data.size())
		{
			return false;
		}

		std::vector<std::string>::iterator iterator1=iter1Data.begin();
		std::vector<std::string>::iterator iterator2=iter2Data.begin();

		while(1)
		{
			if(*iterator1!=*iterator2)
			{
				*iterator1+="???";
				*iterator2+="???";
				return false;
			}

			if(++iterator1==iter1Data.end()||++iterator2==iter2Data.end())
			{
				break;
			}
		}

		if(iter1Data.size()!=iter2Data.size())
		{
			return false;
		}
	}
}

boost::shared_ptr<const CSCSReport> CSCSFileComparer::GetReport() const
{
	return boost::shared_ptr<const CSCSReport>();
}

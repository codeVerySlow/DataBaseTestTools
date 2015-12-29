#include <fstream>
#include <string>
#include <assert.h>

#include "SCSFileComparer.h"
#include "SCSResultIter.h"
#include "util/SCSSortCache.h"
#include "util/SCSCrc32c.h"
#include "SCSReport.h"

CSCSFileComparer::CSCSFileComparer()
{
}

bool CSCSFileComparer::Compare(CSCSResultIter *iter1,CSCSResultIter *iter2)
{
	CSCSSortCache cache1("sort_crc_1");
	CSCSSortCache cache2("sort_crc_2");

	WriteCRCToCache(iter1,cache1);
	WriteCRCToCache(iter2,cache2);
	
	cache1.Short();
	cache2.Short();

	unsigned int crc1;
	unsigned int crc2;

	while(1)
	{
		if(!cache1.Read(&crc1)||!cache2.Read(&crc2))
		{
			break;
		}

		if(crc1!=crc2)
		{
			return false;
		}
	}
	return !cache1.Read(&crc1)&&!cache2.Read(&crc2);
}

bool CSCSFileComparer::CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2)
{
	std::vector<std::string> iter1Data;
	std::vector<std::string> iter2Data;
	while(iter1->GetNext(iter1Data)&&iter2->GetNext(iter2Data))
	{
	    if(iter1Data.size()!=iter2Data.size())
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
	}
}

const CSCSReport* CSCSFileComparer::GetReport() const
{
	return new CSCSReport();
}

void CSCSFileComparer::WriteCRCToCache(CSCSResultIter *iter,CSCSSortCache &cache)
{
	std::vector<std::string> iterData;
	while(iter->GetNext(iterData))
	{

		std::vector<std::string>::iterator iterator=iterData.begin();
		std::string combinStr;

		while(iterator!=iterData.end())
		{
			combinStr+=*iterator++;	
			combinStr+=" ";
		}

		unsigned int crc=crc32c::Value(combinStr.c_str(),combinStr.size());

		cache<<crc;
	}
}

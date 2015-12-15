#include <fstream>
#include <string.h>
#include "SCSFileComparer.h"
#include "SCSResultIter.h"
#include "util/SCSConfigHelper.h"

CSCSFileComparer::CSCSFileComparer():Crc32Table()
{
	CRC32Init();
}

bool CSCSFileComparer::Compare(CSCSResultIter *iter1,CSCSResultIter *iter2)
{
	std::ofstream file1;
	file1.open("./temp/crc1",std::ios::out|std::ios::app|std::ios::trunc);
	
	std::ofstream file2;
	file2.open("./temp/crc2",std::ios::out|std::ios::app|std::ios::trunc);


	while(1)
	{
		std::vector<std::string> iter1Data=iter1->GetNext();
		std::vector<std::string> iter2Data=iter2->GetNext();
		std::vector<std::string>::iterator iterator1=iter1Data.begin();
		std::vector<std::string>::iterator iterator2=iter2Data.begin();
		std::string combinStr1;
		std::string combinStr2;

		while(iterator1!=iter1Data.end())
		{
			combinStr1+=*iterator1++;	
		}

		while(iterator2!=iter2Data.end())
		{
			combinStr2+=*iterator2++;
		}

		file1<<GetCRC32(combinStr1.c_str())<<"\n";
		file2<<GetCRC32(combinStr2.c_str())<<"\n";
	}
	file1.close();
	file2.close();
}

bool CSCSFileComparer::CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2)
{
	while(1)
	{
		std::vector<std::string> iter1Data=iter1->GetNext();
		std::vector<std::string> iter2Data=iter2->GetNext();
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

		if(iter1Data.size()==0&&iter2Data.size()==0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
}

unsigned int CSCSFileComparer::GetCRC32(const char *str)
{
	unsigned int Crc;
	unsigned int len=strlen(str);
	//开始计算CRC32校验值   
	Crc=0xffffffff;      
	for(unsigned int i=0; i<len; i++){        
		Crc = (Crc >> 8) ^ Crc32Table[(Crc & 0xFF) ^ str[i]];      
	}   

	Crc ^= 0xFFFFFFFF;   
	return Crc;      
}

void CSCSFileComparer::CRC32Init()
{
	int i,j;      
	unsigned int Crc;      
	for (i = 0; i < 256; i++){      
		Crc = i;      
		for (j = 0; j < 8; j++){      
			if (Crc & 1)      
			  Crc = (Crc >> 1) ^ 0xEDB88320;      
			else     
			  Crc >>= 1;    
		}      
		Crc32Table[i] = Crc;      
	}
}

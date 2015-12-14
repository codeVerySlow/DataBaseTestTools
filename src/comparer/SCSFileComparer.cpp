#include "SCSFileComparer.h"
#include "SCSResultIter.h"

bool CSCSFileComparer::Compare(CSCSResultIter *iter1,CSCSResultIter *iter2)
{
	std::vector<std::string> iter1Data;
	std::vector<std::string> iter2Data;

	std::vector<std::string>::iterator iterator1;
	std::vector<std::string>::iterator iterator2;

	if(iter1Data.size()!=iter2Data.size())
	{
		return false;
	}

	while(1)
	{
		if(*iterator1!=*iterator2)
		{
			*iterator1="???"+*iterator1;
			*iterator2="???"+*iterator2;
			return false;
		}
	}
}

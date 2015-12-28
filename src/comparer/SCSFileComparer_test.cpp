#include <iostream>
#include <assert.h>
#include "SCSFileComparer.h"
#include "util/SCSCrc32c.h"
#include "util/SCSSortCache.h"
#include "util/SCSUtilTools.h"

class CSCSResultIter{
	public:
		CSCSResultIter():index(0),total(50){};
		std::vector<std::string> GetNext();
		std::vector<std::string> GetCurrent();
		std::string GetCaseId();
	private:
		std::vector<std::string> m_vecCurrentData;
		int index;
		int total;
};

std::vector<std::string> CSCSResultIter::GetNext()
{
	m_vecCurrentData.clear();
	if(index>=total)
	{
		return m_vecCurrentData;
	}
	int i;
	for(i=0;i<50;i++)
	{
		m_vecCurrentData.push_back(SCSUtilTools::NumberToString(i+index));
	}
	index++;
	return m_vecCurrentData;
}

std::vector<std::string> CSCSResultIter::GetCurrent()
{
	return m_vecCurrentData;
}

std::string CSCSResultIter::GetCaseId()
{
	return "100";
}

int main(void)
{
	CSCSFileComparer c;
	CSCSResultIter iter1;
	CSCSResultIter iter2;

	assert(c.Compare(&iter1,&iter2));
	
	std::cout<<"success"<<std::endl;
	return 0;
}

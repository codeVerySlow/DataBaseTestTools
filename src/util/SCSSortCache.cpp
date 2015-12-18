#include <string>
#include <set>
#include <fstream>

#include "SCSSortCache.h"

const unsigned int CSCSSortCache::MEMORY_SET_MAX=10240000;

CSCSSortCache::CSCSSortCache(const std::string &cacheName)
	:m_cacheName(cacheName),
	m_setMemoryCache(),
	m_iterCurrent(m_setMemoryCache.begin()),
	m_fileCache(m_cacheName,std::ios::in|std::ios::out)
	isReadModel(false),
	max(0),
	min(0xFFFFFFFF),
	total(0)
{

}

bool CSCSSortCache::Append(const unsigned int &key)
{
	if(isReadModel)
	{
		return false;
	}

	if(total<MEMORY_SET_MAX)
	{
		m_setMemoryCache.insert(key);	
	}
	else
	{
		m_fileCache<<key;
	}

	if(key>*max)
	{
		*max=key;
	}
	if(key<*min)
	{
		*min=key;
	}
	(*total)++;

	return true;
}

bool CSCSSortCache::Short()
{
	if(total<MEMORY_SET_MAX)
	{
		return true;
	}

	std::ofstream file(m_cacheName.c_str());
	
	WriteMemoryCRCToFile(m_setMemoryCache,file);

	int i,group=(total+MEMORY_SET_MAX-1)/MEMORY_SET_MAX,split=(max-min+1)/group;

	for(i=1;i<group+1;i++)
	{
		std::vector<unsigned int> crcs=ReadCRCFromFile(min+split*i,min+split*(i+1)-1);
		std::sort (crcs.begin(), crcs.end()); 
		WriteSortCRCToFile(crcs,file);
	}
	file.close();
}

std::vector<unsigned int> CSCSSortCache::ReadCRCFromFile(unsigned int min,unsigned int max)
{
	std::string line;
	std::vector<unsigned int> result;

	while(getline(m_fileCache,line))
	{
		unsigned int uiline=crc32c::StringToNumber<unsigned int>(line);
		if(uiline>=min&&uiline<=max)
		{
			result.push_back(uiline);
		}
	}
	return result;
}

void CSCSSortCache::WriteSortCRCToFile(std::vector<unsigned int> vecCRC,std::ofstream &file)
{
	std::vector<unsigned int>::iterator iter=vecCRC.begin();

	while(iter!=vecCRC.end())
	{
		file<<*iter++<<"\n";
	}
}

void CSCSSortCache::WriteMemoryCRCToFile(std::multiset<unsigned int> setCRC,std::ofstream &file)
{
	std::multiset<unsigned int>::iterator iter=setCRC.begin();

	while(iter!=setCRC.end())
	{
		file<<*iter++<<"\n";
	}
}


bool CSCSSortCache::Read(std::string *key)
{	
	if(!isReadModel)
	{
		isReadModel=true;
		m_iterCurrent=m_setMemoryCache.begin();
	}

	if(m_setMemoryCache!=m_setMemoryCache.end())
	{
		*key=*m_iterCurrent++;
		return true;
	}
	else if(total>MEMORY_SET_MAX)
	{
		return getline(m_setMemoryCache,*key);
	}
	else
	{
		return false;
	}
}

void CSCSSortCache::Delete()
{
	m_setMemoryCache.clear();
}
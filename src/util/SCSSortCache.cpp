#include <string>
#include <algorithm> 
#include <iostream>

#include "SCSSortCache.h"
#include "SCSCrc32c.h"

const unsigned int CSCSSortCache::MEMORY_SET_MAX=40;

CSCSSortCache::CSCSSortCache(const std::string &cacheName)
		:m_cacheName(cacheName),
		m_setMemoryCache(),
		m_iterCurrent(m_setMemoryCache.begin()),
		m_fileCache((m_cacheName+"_cache").c_str(),std::ios::in|std::ios::out|std::ios::trunc),
		m_fileSortCache(m_cacheName.c_str(),std::ios::in|std::ios::out|std::ios::trunc),
		isReadModel(false),
		max(0),
		min(0xFFFFFFFF),
		total(0)
{
	if(!m_fileCache||!m_fileSortCache)
	{
		std::cout<<"err cache file"<<std::endl;
	}
}

CSCSSortCache::~CSCSSortCache()
{
	m_fileCache.close();
	m_fileSortCache.close();
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
		m_fileCache<<key<<std::endl;
	}

	if(key>max)
	{
		max=key;
	}
	if(key<min)
	{
		min=key;
	}
	total++;

	return true;
}

bool CSCSSortCache::Short()
{
	if(total<=MEMORY_SET_MAX)
	{
		return true;
	}

	int i,group=(total+MEMORY_SET_MAX-1)/MEMORY_SET_MAX,split=(max-min+1)/group;

	std::vector<unsigned int> crcs;
	m_iterCurrent=m_setMemoryCache.begin();
	m_fileCache.seekg(0,std::ios::beg);

	for(i=0;i<group;i++)
	{
		while(ReadCRCFromFile(min+split*i,min+split*(i+1),crcs))
		{
			std::sort (crcs.begin(), crcs.end()); 
			WriteSortCRCToFile(crcs);
		}
	}

	return true;
}

bool CSCSSortCache::ReadCRCFromFile(unsigned int min,unsigned int max,std::vector<unsigned int> &crcs)
{
	std::string line;
	unsigned int count=0;
	crcs.clear();
	while(count<MEMORY_SET_MAX && m_iterCurrent!=m_setMemoryCache.end())
	{
		if(*m_iterCurrent>=min&&*m_iterCurrent<=max)
		{
			crcs.push_back(*m_iterCurrent);
			count++;
		}
		m_iterCurrent++;
	}

	while(count<MEMORY_SET_MAX && getline(m_fileCache,line))
	{
		unsigned int uiline=crc32c::StringToNumber<unsigned int>(line);
		if(uiline>=min&&uiline<=max)
		{
			crcs.push_back(uiline);
			count++;
		}
	}

	if(m_fileCache.eof())
	{
		m_iterCurrent=m_setMemoryCache.begin();
		m_fileCache.clear();
		m_fileCache.seekg(0,std::ios::beg);
		return false;
	}

	return true;
}

void CSCSSortCache::WriteSortCRCToFile(std::vector<unsigned int> vecCRC)
{
	std::vector<unsigned int>::iterator iter=vecCRC.begin();

	while(iter!=vecCRC.end())
	{
		m_fileSortCache<<*iter++<<"\n";
	}
}

bool CSCSSortCache::Read(unsigned int *key)
{	
	if(!isReadModel)
	{
		isReadModel=true;
		m_iterCurrent=m_setMemoryCache.begin();
	}

	if(m_iterCurrent!=m_setMemoryCache.end())
	{
		*key=*m_iterCurrent++;
		return true;
	}
	else if(total>MEMORY_SET_MAX)
	{
		std::string line;
		if(getline(m_fileCache,line))
		{
			*key=crc32c::StringToNumber<unsigned int>(line);
			return true;
		}
	}

	return false;
}

void CSCSSortCache::Delete()
{
	m_setMemoryCache.clear();
}

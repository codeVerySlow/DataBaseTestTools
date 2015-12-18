#include <string>
#include <algorithm> 
#include <iostream>

#include "SCSSortCache.h"
#include "SCSCrc32c.h"
#include "SCSExternSort.h"

const unsigned int CSCSSortCache::MEMORY_SET_MAX=40;

CSCSSortCache::CSCSSortCache(const std::string &cacheName)
		:m_cacheName(cacheName),
		m_setMemoryCache(),
		m_iterCurrent(m_setMemoryCache.begin()),
		m_fileCache((m_cacheName+"_cache").c_str(),std::ios::in|std::ios::out|std::ios::trunc),
		isReadModel(false),
		total(0)
{
	if(!m_fileCache)
	{
		std::cout<<"err cache file"<<std::endl;
	}
}

CSCSSortCache::~CSCSSortCache()
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
	
	m_fileCache<<key<<std::endl;

	total++;

	return true;
}

bool CSCSSortCache::Short()
{
	m_fileCache.close();
	if(total<=MEMORY_SET_MAX)
	{
		return true;
	}	
	
	CSCSExternSort extSort((m_cacheName+"_cache").c_str(),m_cacheName.c_str(),total/100);
	extSort.sort()
	return true;
}

bool CSCSSortCache::Read(unsigned int *key)
{	
	if(!isReadModel)
	{
		isReadModel=true;
		m_iterCurrent=m_setMemoryCache.begin();
		m_fileCache.open(m_cacheName.c_str(),std::ios::in);
	}

	if(total<MEMORY_SET_MAX)
	{
		if(m_iterCurrent!=m_setMemoryCache.end())
		{
			*key=*m_iterCurrent++;
			return true;
		}
	}
	else 
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
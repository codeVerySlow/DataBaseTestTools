#include <string>
#include <algorithm> 
#include <iostream>

#include "SCSSortCache.h"
#include "SCSCrc32c.h"
#include "SCSExternSort.h"
#include "DBLog.h"

const unsigned int CSCSSortCache::MEMORY_SET_MAX = 40;

CSCSSortCache::CSCSSortCache(const std::string &cacheName)
        : m_cacheName(cacheName),
          m_setMemoryCache(),
          m_iterCurrent(m_setMemoryCache.begin()),
          m_fileCache((m_cacheName + "_cache").c_str(), std::ios::in | std::ios::out | std::ios::trunc),
          m_fileData((m_cacheName + "_data").c_str(), std::ios::in | std::ios::out | std::ios::trunc),
          isReadModel(false),
          total(0)
{
    if (!m_fileCache)
    {
        LOG_ERROR("CSCSSortCache fileCache open file");
    }
}

CSCSSortCache::~CSCSSortCache()
{
    m_fileCache.close();
    m_fileData.close();
}

bool CSCSSortCache::Append(const unsigned int &key)
{
    if (isReadModel)
    {
        return false;
    }

    if (total < MEMORY_SET_MAX)
    {
        m_setMemoryCache.insert(key);
    }

    m_fileCache << key << " ";

    total++;

    return true;
}

bool CSCSSortCache::Append(const std::vector<std::string> &key)
{
    std::vector<std::string>::const_iterator iterator = key.begin();
    std::string combinStr;

    while (iterator != key.end())
    {
        combinStr += *iterator++;
        combinStr += " ";
    }
    m_fileData << combinStr << std::endl;
    unsigned int crc = crc32c::Value(combinStr.c_str(), combinStr.size());

    return Append(crc);
}


bool CSCSSortCache::Short()
{
    m_fileCache.close();
    m_fileData.close();
    if (total <= MEMORY_SET_MAX)
    {
        return true;
    }

    CSCSExternSort extSort((m_cacheName + "_cache").c_str(), m_cacheName.c_str(), (total + 100 - 1) / 100);
    extSort.sort();
    return true;
}

bool CSCSSortCache::Read(unsigned int *key)
{
    if (!isReadModel)
    {
        isReadModel = true;
        m_iterCurrent = m_setMemoryCache.begin();
        m_fileCache.open(m_cacheName.c_str(), std::ios::in);
    }

    if (total < MEMORY_SET_MAX)
    {
        if (m_iterCurrent != m_setMemoryCache.end())
        {
            *key = *m_iterCurrent++;
            return true;
        }
    }
    else
    {
        return m_fileCache >> *key;
    }

    return false;
}

std::string CSCSSortCache::GetRealData(const unsigned int &key)
{
    std::fstream cache((m_cacheName + "_cache").c_str(), std::ios::in);
    if (!cache)
    {
        LOG_ERROR("SCSSortCache GetRealData open cache file err");
        return "";
    }

    unsigned int crc = 0;
    int pos = 0;
    while (cache >> crc)
    {
        if (key == crc)
        {
            break;
        }
        pos++;
    }
    if (pos == 0)
    {
        return "";
    }

    std::fstream data((m_cacheName + "_data").c_str(), std::ios::in);
    if (!data)
    {
        LOG_ERROR("SCSSortCache GetRealData open cache data file err");
        return "";
    }

    std::string result;
    while (pos-- >= 0 && getline(data, result)) ;

    cache.close();
    data.close();
    return result;
}



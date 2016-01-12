#ifndef _UTIL_SCSSORTCACHE_H_
#define _UTIL_SCSSORTCACHE_H_

#include <string>
#include <set>
#include <vector>
#include <fstream>

class CSCSSortCache
{
public:
    CSCSSortCache(const std::string &cacheName);

    ~CSCSSortCache();

    //将key写入排序缓存
    bool Append(const unsigned int &key);
    //将数据行写入排序缓存
    bool Append(const std::vector<std::string> &key);
    //读取已经排序好的key
    bool Read(unsigned int *key);
    //排序
    bool Short();
    //根据key查找之前未做CRC32的数据行
    std::string GetRealData(const unsigned int &key);
    //重载<<写入缓存
    CSCSSortCache &operator<<(const unsigned int &key)
    {
        Append(key);
        return *this;
    }
    //重载<<写入缓存
    CSCSSortCache &operator<<(const std::vector<std::string> &key)
    {
        Append(key);
        return *this;
    }


private:
    static const unsigned int MEMORY_SET_MAX;

    std::string m_cacheName;
    std::multiset<unsigned int> m_setMemoryCache;
    std::multiset<unsigned int>::iterator m_iterCurrent;
    std::fstream m_fileCache;
    std::fstream m_fileData;
    bool isReadModel;
    unsigned int total;
};

#endif

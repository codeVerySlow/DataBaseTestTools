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

    bool Append(const unsigned int &key);

    bool Read(unsigned int *key);

    bool Short();

    CSCSSortCache &operator<<(const unsigned int &key)
    {
        Append(key);
        return *this;
    }

    void Delete();

private:
    static const unsigned int MEMORY_SET_MAX;

    std::string m_cacheName;
    std::multiset<unsigned int> m_setMemoryCache;
    std::multiset<unsigned int>::iterator m_iterCurrent;
    std::fstream m_fileCache;
    std::fstream m_fileSortCache;
    bool isReadModel;
    unsigned int max, min, total;
};

#endif

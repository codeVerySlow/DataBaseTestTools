#ifndef _UTIL_SCSSORTCACHE_H_
#define _UTIL_SCSSORTCACHE_H_

#include <string>
#include <set>

class CSCSSortCache
{
public:
	CSCSSortCache(const std::string &cacheName);
	bool Append(const std::string &key);
	bool Read(std::string *key);
	CSCSSortCache& operator<<(const std::string &key){ Append(key);return *this;}
	void Delete();
private:
	static std::multiset<std::string> m_setMemoryCache;
	std::set<std::string>::iterator iterCurrent;
	bool isReadModel;
};

#endif

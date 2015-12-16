#ifndef _UTIL_SCSSORTCACHE_H_
#define _UTIL_SCSSORTCACHE_H_

#include <string>

class CSCSSortCache
{
public:
	CSCSSortCache(const std::string &cacheName);
	bool Append(const std::string &key);
	bool Read(std::string *key);
	CSCSSortCache& operator<<(const std::string &key){ Append(key);return *this;}
	void Delete();
};

#endif
#ifndef _UTIL_SCSSORTCACHE_H_
#define _UTIL_SCSSORTCACHE_H_

#include <string>
#include <set>

class CSCSSortCache
{
public:
	CSCSSortCache(const unsigned int &cacheName);
	bool Append(const unsigned int &key);
	bool Read(unsigned int *key);
	bool Short();
	CSCSSortCache& operator<<(const unsigned int &key){ Append(key);return *this;}
	void Delete();
private:
	static const unsigned int MEMORY_SET_MAX;
	std::vector<unsigned int> ReadCRCFromFile(const std::string &fileName,unsigned int min,unsigned int max);
	void WriteSortCRCToFile(std::vector<unsigned int> vecCRC,std::ofstream &file);
	void WriteMemoryCRCToFile(std::multiset<unsigned int> setCRC,std::ofstream &file);

	std::string m_cacheName;
	std::multiset<unsigned int> m_setMemoryCache;
	std::multiset<unsigned int>::iterator m_iterCurrent;
	std::fstream m_fileCache;
	bool isReadModel;
	unsigned int max,min,total;
};

#endif

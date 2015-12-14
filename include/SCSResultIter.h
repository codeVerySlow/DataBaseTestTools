#ifndef _INCLUDE_SCSRESULTITER_H_
#define _INCLUDE_SCSRESULTITER_H_ value

#include <vector>
#include <string>

class Executer;

class CSCSResultIter{
public:
	CSCSResultIter(Executer *executer);
	~CSCSResultIter();
	const std::vector<std::string>& GetNext() const;
	const std::vector<std::string>& GetCurrent() const;
private:
	std::vector<std::string> m_vecCurrentData;
};

#endif
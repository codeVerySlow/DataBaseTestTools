#ifndef _INCLUDE_SCSRESULTITER_H_
#define _INCLUDE_SCSRESULTITER_H_ value

#include <vector>
#include <string>

class Executer;

class CSCSResultIter{
public:
	CSCSResultIter(Executer *executer);
	~CSCSResultIter();
	std::vector<std::string> GetNext();
	std::vector<std::string> GetCurrent();
	std::string GetCaseId();
private:
	std::vector<std::string> m_vecCurrentData;
};

#endif

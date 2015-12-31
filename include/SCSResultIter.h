#ifndef _INCLUDE_SCSRESULTITER_H_
#define _INCLUDE_SCSRESULTITER_H_

#include <vector>
#include <string>
#include <boost/shared_ptr.hpp>

class CSCSExecuter;

class CSCSResultIter{
public:
	CSCSResultIter(CSCSExecuter *executer);
	~CSCSResultIter();
	bool GetNext(std::vector<std::string> &row);
private:
	CSCSExecuter *m_pExecuter;
};

#endif

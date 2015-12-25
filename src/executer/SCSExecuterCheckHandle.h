#ifndef _EXECUTER_SCSEXECUTERCHECKHANDLE_H_
#define _EXECUTER_SCSEXECUTERCHECKHANDLE_H_

#include <vector>

class CSCSReport
class CSCSExecuterCheckHandle
{
private:
	CSCSExecuterCheckHandle *nextHandle;
public:
	void SetNextHandle(CSCSExecuterCheckHandle *handle);
	virtual std::vector<CSCSReport> Check();
};

#endif

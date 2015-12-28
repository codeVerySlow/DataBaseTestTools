#ifndef _EXECUTER_SCSSLAVERCHECK_H_
#define _EXECUTER_SCSSLAVERCHECK_H_
#include <vector>

#include "SCSExecuterCheckHandle.h"

class CSCSSlaverCheck:public CSCSExecuterCheckHandle
{
public:
	std::vector<CSCSReport> Check();
};

#endif
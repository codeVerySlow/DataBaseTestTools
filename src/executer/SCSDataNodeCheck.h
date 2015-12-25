#include "SCSExecuterCheckHandle.h"

class CSCSDataNodeCheck:public CSCSExecuterCheckHandle
{
public:
	std::vector<CSCSReport> Check();
};
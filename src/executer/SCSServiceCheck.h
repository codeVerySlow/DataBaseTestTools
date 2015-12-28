#include <vector>

#include "SCSExecuterCheckHandle.h"

class CSCSServiceCheck :public CSCSExecuterCheckHandle
{
public:
	std::vector<CSCSReport> Check();
};
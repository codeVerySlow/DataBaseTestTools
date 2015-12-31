#include <vector>
#include <boost/shared_ptr.hpp>
#include <sys/types.h>

#include "SCSExecuterCheckHandle.h"

class CSCSServiceCheck :public CSCSExecuterCheckHandle
{
public:
	bool Check(std::vector<boost::shared_ptr<CSCSReport> > &report);

private:
	static int s_nReConnectTimes;
	static pid_t s_nLastPID;
};

int CSCSServiceCheck::s_nReConnectTimes=0;
pid_t CSCSServiceCheck::s_nLastPID=-1;
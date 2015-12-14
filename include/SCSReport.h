#ifndef _INCLUDE_SCSREPORT_H_
#define _INCLUDE_SCSREPORT_H_

#include <vector>
#include <string>

class CSCSReport
{
	public:
		int nTotal;
		int nPass;
		bool isSuccess;
		std::vector<std::string> vecFailData;
		std::string strMessage;
};


#endif
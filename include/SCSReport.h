#ifndef _INCLUDE_SCSREPORT_H_
#define _INCLUDE_SCSREPORT_H_

#include <vector>
#include <string>

class CSCSReport
{
	public:
		int m_nTotal;
		int m_nPass;
		bool m_isSuccess;
		std::vector<std::string> m_vecFailData;
		std::string m_strMessage;
};


#endif
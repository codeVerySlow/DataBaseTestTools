#ifndef _EXECUTER_SCSEXECUTERCHECKER_H_
#define _EXECUTER_SCSEXECUTERCHECKER_H_
#include <vector>

class CSCSReport;

class ExecuterChecker
{
public:
	std::vector<CSCSReport> BeforeCase();
	std::vector<CSCSReport> AfterCase();
	std::vector<CSCSReport> BeforeEachExecute();
	std::vector<CSCSReport> AfterEachExecute();
};
#endif
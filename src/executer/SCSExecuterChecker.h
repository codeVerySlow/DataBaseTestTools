#include <vector>
#include "SCSReport.h"

class ExecuterChecker
{
public:
	std::vector<CSCSReport> BeforeCase();
	std::vector<CSCSReport> AfterCase();
	std::vector<CSCSReport> BeforeEachExecute();
	std::vector<CSCSReport> AfterEachExecute();
};
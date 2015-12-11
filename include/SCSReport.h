#include <vector>
#include <string>

class STReport
{
	public:
		int nTotal;
		int nPass;
		bool isSuccess;
		std::vector<std::string> vecFailData;
		std::string strMessage;
};



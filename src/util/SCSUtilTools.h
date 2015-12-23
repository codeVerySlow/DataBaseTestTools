#include <string>
#include <vector>
#include <sstream>

namespace SCSUtilTools{

	template <typename T>
	std::string NumberToString ( T Number )
	{
		std::ostringstream ss;
		ss << Number;
		return ss.str();
	}

	template <typename T>
	T StringToNumber ( const std::string &Text )
	{
		std::istringstream ss(Text);
		T result;
		return ss >> result ? result : 0;
	}

	extern std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems);

	extern std::vector<std::string> split(const std::string &s, char delim);

	extern std::string join(const std::vector<std::string> &vec,const std::string &delim);

}

#include <string>
#include <vector>
#include <sstream>

namespace SCSUtilTools{
	std::vector<std::string>& split(const std::string &s, const std::string &delim, std::vector<std::string> &elems) {
		std::string item;

		std::string::size_type i,j,end=s.length()-1;

		for(i=0;i<=end;i++)
		{
			bool check=true;
			for(j=0;j<delim.length();j++)
			{
				if(s[i+j]!=delim[j])
				{
					check=false;
					break;
				}
			}
			if(check)
			{
				elems.push_back(item);
				item.clear();
				i+=delim.length()-1;
			}
			else
			{
				item.push_back(s[i]);
			}
		}

		elems.push_back(item);

		return elems;
	}


	std::vector<std::string> split(const std::string &s, const std::string &delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

	std::string join(const std::vector<std::string> &vec,const std::string &delim){
		std::vector<std::string>::const_iterator it;
		std::string str;
		for(it=vec.begin();it!=vec.end();it++)
		{
			if(it!=vec.begin())
			{
				str+=delim;
			}
			str+=*it;
		}
		return str;
	}
}

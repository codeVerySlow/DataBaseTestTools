
namespace SCSUtilTools{
	std::vector<std::string>& split(const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss(s);
		std::string item;
		while (std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
		return elems;
	}


	std::vector<std::string> split(const std::string &s, char delim) {
		std::vector<std::string> elems;
		split(s, delim, elems);
		return elems;
	}

	std::string join(const std::vector<std::string> &vec,const std::string &delim){
		std::vector<std::string>::iterator it;
		std::string str;
		for(it=vec.begin();it!=vec.end();it++)
		{
			if(it!=vec.begin())
			{
				str+=delim;
			}
			str+=it;
		}
		return str;
	}
}
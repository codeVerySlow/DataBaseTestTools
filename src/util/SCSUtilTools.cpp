#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <dirent.h>
#include <fstream>

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

	int GetColumnIndex( const std::string &column,const std::vector<std::string> &vecTestColumn ){
		std::vector<std::string>::const_iterator it = find(vecTestColumn.begin(),vecTestColumn.end(),column);

		if(it == vecTestColumn.end())
		{
			return -1;
		}

		unsigned int scsdbcaseIndex = it - vecTestColumn.begin();

		if(scsdbcaseIndex >= vecTestColumn.size())
		{
			return -1;
		}

		return scsdbcaseIndex;
	}

	int getProcIdByName(std::string procName)
	{
		int pid = -1;

		// Open the /proc directory
		DIR *dp = opendir("/proc");
		if (dp != NULL)
		{
			// Enumerate all entries in directory until process found
			struct dirent *dirp;
			while (pid < 0 && (dirp = readdir(dp)))
			{
				// Skip non-numeric entries
				int id = atoi(dirp->d_name);
				if (id > 0)
				{
					// Read contents of virtual /proc/{pid}/cmdline file
					std::string cmdPath = std::string("/proc/") + dirp->d_name + "/cmdline";
					std::ifstream cmdFile(cmdPath.c_str());
					std::string cmdLine;
					getline(cmdFile, cmdLine);
					if (!cmdLine.empty())
					{
						// Keep first cmdline item which contains the program path
						size_t pos = cmdLine.find('\0');
						if (pos != std::string::npos)
							cmdLine = cmdLine.substr(0, pos);
						// Keep program name only, removing the path
						pos = cmdLine.rfind('/');
						if (pos != std::string::npos)
							cmdLine = cmdLine.substr(pos + 1);
						// Compare against requested process name
						if (procName == cmdLine)
							pid = id;
					}
				}
			}
		}

		closedir(dp);

		return pid;
	}
}

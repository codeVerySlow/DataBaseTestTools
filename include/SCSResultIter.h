
#include <vector>
#include <string>

class Executer;

class CSCSResultIter{
public:
	CSCSResultIter(Executer *executer);
	~CSCSResultIter();
	const std::vector<std::string>& GetNext() const;
	const std::vector<std::string>& GetCurrent() const;
private:
	std::vector<std::string> m_vecCurrentData;
}
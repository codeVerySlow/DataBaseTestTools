#include <boost/shared_ptr.hpp>

class CSCSResultIter;
class CSCSComparer;

struct STReport
{
	int nTotal;
	int nPass;
	bool isSuccess;
	std::vector<std::string> vecFailData;
	std::string strMessage;
};

class CSCSComparerWrapper
{
public:
	CSCSComparerWrapper();
	~CSCSComparerWrapper();
	//对比两个迭代器数据是否相同，相同返回ture，不相同返回false
	bool Compare(CSCSResultIter *iter1,CSCSResultIter *iter2);
	//对比两个迭代器数据和顺序是否相同，相同返回true,不同返回false
	bool CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2);
	boost::shared_ptr<STReport> GetReport() const;
private:
	boost::shared_ptr<CSCSComparer> compare;
};


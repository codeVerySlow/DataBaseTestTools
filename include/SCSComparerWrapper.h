#include <vector>
#include <string>

class CSCSResultIter;
class CSCSComparer;
class CSCSReport;

class CSCSComparerWrapper
{
public:
	CSCSComparerWrapper();
	~CSCSComparerWrapper();
	//对比两个迭代器数据是否相同，相同返回ture，不相同返回false
	bool Compare(CSCSResultIter *iter1,CSCSResultIter *iter2);
	//对比两个迭代器数据和顺序是否相同，相同返回true,不同返回false
	bool CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2);
	CSCSReport* GetReport() const;
private:
	CSCSComparer* compare;
};


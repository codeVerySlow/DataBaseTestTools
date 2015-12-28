#ifndef _COMPARER_SCSCOMPARER_H_
#define _COMPARER_SCSCOMPARER_H_

class CSCSReport;
class CSCSResultIter;

class CSCSComparer
{
public:
	CSCSComparer() {};
	virtual ~CSCSComparer() {};
	//对比两个迭代器数据是否相同，相同返回ture，不相同返回false
	virtual bool Compare(CSCSResultIter *iter1,CSCSResultIter *iter2)=0;
	//对比两个迭代器数据和顺序是否相同，相同返回true,不同返回false
	virtual bool CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2)=0;
	virtual const CSCSReport* GetReport() const=0;

	static CSCSComparer* Create();
};

#endif

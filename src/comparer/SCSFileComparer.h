#include <boost/shared_ptr.hpp>
#include "SCSComparer.h"

class CSCSReport;

class CSCSFileComparer:public CSCSComparer
{
	public:
		CSCSFileComparer(){};
		~CSCSFileComparer(){};
		bool Compare(CSCSResultIter *iter1,CSCSResultIter *iter2);
		bool CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2);
		boost::shared_ptr<const CSCSReport> GetReport() const;
};

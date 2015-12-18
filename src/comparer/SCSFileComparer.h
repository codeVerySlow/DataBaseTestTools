#ifndef _COMPARER_SCSFILECOMPARER_H_
#define _COMPARER_SCSFILECOMPARER_H__
#include <boost/shared_ptr.hpp>
#include "SCSComparer.h"

class CSCSReport;
class CSCSSortCache;

class CSCSFileComparer:public CSCSComparer
{
	public:
		CSCSFileComparer();
		bool Compare(CSCSResultIter *iter1,CSCSResultIter *iter2);
		bool CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2);
		boost::shared_ptr<const CSCSReport> GetReport() const;
	private:
		void WriteCRCToCache(CSCSResultIter *iter,CSCSSortCache &fileName);
};
#endif

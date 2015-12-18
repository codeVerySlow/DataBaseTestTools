#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include <fstream>
#include "SCSComparer.h"

class CSCSReport;

class CSCSFileComparer:public CSCSComparer
{
	public:
		CSCSFileComparer();
		bool Compare(CSCSResultIter *iter1,CSCSResultIter *iter2);
		bool CompareSequence(CSCSResultIter *iter1,CSCSResultIter *iter2);
		boost::shared_ptr<const CSCSReport> GetReport() const;
	private:
		void WriteCRCToCache(CSCSResultIter *iter,const std::string &fileName,unsigned int *max,unsigned int *min,unsigned int *total);
};

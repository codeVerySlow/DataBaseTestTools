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
		void SortResultIter(CSCSResultIter *iter,const std::string &fileName);
		void WriteCRCToCache(CSCSResultIter *iter,const std::string &fileName,unsigned int *max,unsigned int *min,unsigned int *total);
		std::vector<unsigned int> ReadCRCFromCache(const std::string &fileName,unsigned int min,unsigned int max);
		void WriteSortCRCToFile(std::vector<unsigned int> vecCRC,std::ofstream &file);
		
		void WriteToFile(const std::string &data,const std::string &fileName);
};

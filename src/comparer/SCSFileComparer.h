#ifndef _COMPARER_SCSFILECOMPARER_H_
#define _COMPARER_SCSFILECOMPARER_H_

#include "SCSComparer.h"

class CSCSReport;
class CSCSSortCache;
class CSCSComparerReport;

class CSCSFileComparer : public CSCSComparer
{
public:
    CSCSFileComparer();

    bool Compare(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2);

    bool CompareSequence(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2);

    boost::shared_ptr<STTestCaseReport> GetReport() const;

private:
    void WriteCRCToCache(boost::shared_ptr<CSCSResultIter> iter, CSCSSortCache &fileName);

    boost::shared_ptr<STTestCaseReport> m_testcasereport;
};

#endif

#include "util/SCSUtilTools.h"
#include "SCSComparerReport.h"
#include "SCSExecuterWrapper.h"
#include "SCSComparerWrapper.h"
#include "SCSComparer.h"

CSCSComparerWrapper::CSCSComparerWrapper():m_compare(CSCSComparer::Create())
{

}

CSCSComparerWrapper::~CSCSComparerWrapper()
{

}

boost::shared_ptr<STTestCaseReport> CSCSComparerWrapper::GetReport() const
{
    return m_compare->GetReport();
}

bool CSCSComparerWrapper::Compare(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2)
{
    return m_compare->Compare(iter1,iter2);
}

bool CSCSComparerWrapper::CompareSequence(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2)
{
    return m_compare->CompareSequence(iter1,iter2);
}

#include "SCSResultIter.h"
#include "SCSExecuter.h"

CSCSResultIter::CSCSResultIter(CSCSExecuter *executer) : m_pExecuter(executer)
{
}

CSCSResultIter::~CSCSResultIter()
{

}

bool CSCSResultIter::GetNext(std::vector<std::string> &row)
{
    return m_pExecuter->GetNext(row);
}

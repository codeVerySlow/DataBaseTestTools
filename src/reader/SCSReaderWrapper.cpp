#include "SCSReaderWrapper.h"
#include "SCSReader.h"

CSCSReaderWrapper::CSCSReaderWrapper(): m_reader(CSCSReader::Create())
{

}

CSCSReaderWrapper::~CSCSReaderWrapper()
{

}

bool CSCSReaderWrapper::ReadNextTestCase(CSCSPreparedSQLSet &set)
{
    return m_reader->ReadNextTestCase(set);
}

int CSCSReaderWrapper::GetTestCaseTotal()
{
    return m_reader->GetTestCaseTotal();
}

int CSCSReaderWrapper::GetTestCaseIndex()
{
    return m_reader->GetTestCaseIndex();
}

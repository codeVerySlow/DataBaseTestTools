#include "SCSReaderWrapper.h"
#include "SCSReader.h"

CSCSReaderWrapper::CSCSReaderWrapper():reader(CSCSReader::Create())
{

}

CSCSReaderWrapper::~CSCSReaderWrapper()
{

}

bool CSCSReaderWrapper::ReadNextTestCase(CSCSPreparedSQLSet &set)
{
    return reader->ReadNextTestCase(set);
}

#include "SCSReader.h"
#include "SCSMySqlReader.h"

boost::shared_ptr<CSCSReader> CSCSReader::Create()
{
    return boost::shared_ptr<CSCSReader>(new CSCSMySqlReader());
}

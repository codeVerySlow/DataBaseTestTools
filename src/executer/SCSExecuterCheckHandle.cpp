#include <boost/shared_ptr.hpp>
#include "SCSExecuterCheckHandle.h"

void CSCSExecuterCheckHandle::SetNextHandle(boost::shared_ptr<CSCSExecuterCheckHandle> handle)
{
    this->nextHandle = handle;
}

boost::shared_ptr<CSCSExecuterCheckHandle> CSCSExecuterCheckHandle::GetNextHandle()
{
    return this->nextHandle;
}

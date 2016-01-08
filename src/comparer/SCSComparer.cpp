#include "SCSComparer.h"
#include "SCSFileComparer.h"

boost::shared_ptr<CSCSComparer> CSCSComparer::Create()
{
    return boost::shared_ptr<CSCSComparer>(new CSCSFileComparer);
}

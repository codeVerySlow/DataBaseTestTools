#include <boost/shared_ptr.hpp>
#include "SCSExecuter.h"
#include "SCSMySQLExecuter.h"
#include "SCSSCSExecuter.h"

boost::shared_ptr<CSCSExecuter> CSCSExecuter::Create(EMExecuterType type,const STConnect *connect){
	switch (type)
	{
		case ExecuterType_SCS:
			return boost::shared_ptr<CSCSExecuter>(new CSCSSCSExecuter(connect));
		case ExecuterType_MYSQL:
			return boost::shared_ptr<CSCSExecuter>(new CSCSMySQLExecuter(connect));
	}
}

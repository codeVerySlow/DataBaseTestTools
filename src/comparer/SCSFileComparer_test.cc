#include <iostream>
#include <assert.h>
#include <boost/shared_ptr.hpp>
#include "util/SCSConfigHelper.h"
#include "SCSResultIter.h"
#include "executer/SCSExecuter.h"
#include "SCSFileComparer.h"
#include "DBLog.h"

int main(void)
{
    LOG_INIT_NORMAL("./", true);
    SET_LOGLEVEL(__SLL_INFO);
    assert(CSCSConfigHelper::GetInstance()->Read());

    CSCSFileComparer c;
    boost::shared_ptr<CSCSResultIter> iter1;
    boost::shared_ptr<CSCSResultIter> iter2;
    assert(c.Compare(iter1, iter2));

    std::cout << "success" << std::endl;
    return 0;
}

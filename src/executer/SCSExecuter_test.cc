#include <boost/shared_ptr.hpp>
#include <DBLog.h>
#include "SCSExecuter.h"
#include "SCSResultIter.h"
#include "util/SCSConfigHelper.h"
#include "SCSSCSExecuter.h"

void printIterator(boost::shared_ptr<CSCSResultIter> resultIter);

int main()
{
    LOG_INIT_NORMAL("./", true);
    SET_LOGLEVEL(__SLL_INFO);
    assert(CSCSConfigHelper::GetInstance()->Read());

    boost::shared_ptr<CSCSExecuter> srcExecuter(
            CSCSExecuter::Create(ExecuterType_SCS, &(CSCSConfigHelper::GetInstance()->GetConfig()->conDesConnect)));
    boost::shared_ptr<CSCSExecuter> desExecuter(CSCSExecuter::Create(ExecuterType_MYSQL,
                                                                     &(CSCSConfigHelper::GetInstance()->GetConfig()->conSrcMysqlConnect)));

    srcExecuter->OpenDataSource();
    desExecuter->OpenDataSource();
    std::string msg;
    boost::shared_ptr<CSCSResultIter> scsResultIter(
            srcExecuter->ExecuteSQL("select t.* from t(test)", msg));
    boost::shared_ptr<CSCSResultIter> mysqlResultIter(desExecuter->ExecuteSQL("select * from a", msg));

    printIterator(scsResultIter);
    printIterator(mysqlResultIter);

    srcExecuter->CloseDataSource();
    desExecuter->CloseDataSource();

    std::cout << "ok" << std::endl;
    return 0;
}

void printIterator(boost::shared_ptr<CSCSResultIter> resultIter)
{
    std::vector<std::string> scsrows;
    while (resultIter->GetNext(scsrows))
    {
        std::vector<std::string>::iterator iter = scsrows.begin();
        while (iter != scsrows.end())
        {
            std::cout << *iter++ << " ";
        }
        std::cout << std::endl;
    }
}
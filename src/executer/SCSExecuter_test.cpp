#include <boost/shared_ptr.hpp>
#include "SCSExecuter.h"
#include "SCSResultIter.h"
#include "util/SCSConfigHelper.h"
#include "SCSSCSExecuter.h"
#include "SCSMySQLExecuter.h"

void printIterator(boost::shared_ptr<CSCSResultIter> resultIter);

int main()
{
    //boost::shared_ptr<CSCSExecuter> scsExecuter(CSCSExecuter::Create(ExecuterType_SCS,&(CSCSConfigHelper::GetInstance()->GetConfig()->conDesConnect)));
    //boost::shared_ptr<CSCSExecuter> mysqlExecuter(CSCSExecuter::Create(ExecuterType_MYSQL,&(CSCSConfigHelper::GetInstance()->GetConfig()->conSrcMysqlConnect)));

    boost::shared_ptr<CSCSExecuter> scsExecuter(new CSCSSCSExecuter(&(CSCSConfigHelper::GetInstance()->GetConfig()->conDesConnect)));
    boost::shared_ptr<CSCSExecuter> mysqlExecuter(new CSCSMySQLExecuter(&(CSCSConfigHelper::GetInstance()->GetConfig()->conSrcMysqlConnect)));

    scsExecuter->OpenDataSource();
    mysqlExecuter->OpenDataSource();

    boost::shared_ptr<CSCSResultIter> scsResultIter(scsExecuter->ExecuteSQL("select * from a"));
    boost::shared_ptr<CSCSResultIter> mysqlResultIter(mysqlExecuter->ExecuteSQL("select * from a"));

    printIterator(scsResultIter);
    printIterator(mysqlResultIter);

    scsExecuter->CloseDataSource();
    mysqlExecuter->CloseDataSource();

}

void printIterator(boost::shared_ptr<CSCSResultIter> resultIter) {
    std::vector<std::string> scsrows;
    while(resultIter->GetNext(scsrows))
    {
        std::vector<std::string>::iterator iter=scsrows.begin();
        while (iter!=scsrows.end())
        {
            std::cout << *iter << " ";
        }
        std::cout << std::endl;
    }
}
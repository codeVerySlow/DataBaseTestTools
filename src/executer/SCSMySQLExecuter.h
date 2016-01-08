#ifndef _EXECUTER_SCSMYSQLEXECUTER_H_
#define _EXECUTER_SCSMYSQLEXECUTER_H_

#include <boost/shared_ptr.hpp>
#include "util/SCSMySqlHelper.h"
#include "SCSExecuter.h"

class CSCSMySqlHelper;

class CSCSMySQLExecuter : public CSCSExecuter
{
public:
    CSCSMySQLExecuter(const STConnect *connect) : mysql(new CSCSMySqlHelper()),
                                                  m_pConnect(connect)
    { };

    ~CSCSMySQLExecuter()
    { CloseDataSource(); };

    boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql, std::string &msg);

    void CloseDataSource();

    bool GetNext(std::vector<std::string> &dataRow);

private:
    boost::shared_ptr<CSCSMySqlHelper> mysql;
    const STConnect *m_pConnect;
};

#endif

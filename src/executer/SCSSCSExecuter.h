#ifndef _EXECUTER_SCSSCSEXECUTER_H_
#define _EXECUTER_SCSSCSEXECUTER_H_

#include <boost/shared_ptr.hpp>
#include "util/SCSSCSHelper.h"
#include "SCSExecuter.h"

class CSCSSCSHelper;

struct STConnect;

class CSCSSCSExecuter : public CSCSExecuter
{
public:
    CSCSSCSExecuter(const STConnect *connect) : scs(new CSCSSCSHelper()),
                                                m_pConnect(connect)
    { };

    ~CSCSSCSExecuter()
    { CloseDataSource(); };

    boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql, std::string &msg);

    void CloseDataSource();

    bool GetNext(std::vector<std::string> &dataRow);

private:
    boost::shared_ptr<CSCSSCSHelper> scs;
    const STConnect *m_pConnect;
};

#endif
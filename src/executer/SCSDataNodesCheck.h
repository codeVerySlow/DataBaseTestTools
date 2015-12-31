//
// Created by Administrator on 2015/12/31.
//

#ifndef _EXECUTER_SCSDATANODESCHECK_H
#define _EXECUTER_SCSDATANODESCHECK_H


#include <util/SCSSCSHelper.h>
#include "SCSExecuterCheckHandle.h"

class CSCSDataNodesCheck: public CSCSExecuterCheckHandle
{
public:

    CSCSDataNodesCheck():m_pSCSHelper(new CSCSSCSHelper()) { };

    ~CSCSDataNodesCheck() { };

    bool Check(std::vector<CSCSReport> &reports);

private:
    bool Error(const std::string &msg, std::vector<CSCSReport> &reports);
    boost::shared_ptr<CSCSSCSHelper> m_pSCSHelper;
};


#endif //PROGRAM_SCSDATANODESCHECK_H

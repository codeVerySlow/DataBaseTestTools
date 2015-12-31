//
// Created by Administrator on 2015/12/31.
//

#ifndef _RESULTWRITER_SCSDATANODEREPORT_H_
#define _RESULTWRITER_SCSDATANODEREPORT_H_


#include "SCSReport.h"

struct STNode
{

    STNode() { };


    STNode(const std::string &IP, const std::string &Port, const std::string &TableName, const std::string &Count) : IP(
            IP), Port(Port), TableName(TableName), Count(Count) { };

    std::string IP;
    std::string Port;
    std::string TableName;
    std::string Count;
};

class CSCSDataNodeReport: public CSCSReport
{
public:
    CSCSDataNodeReport() : CSCSReport() { };

    CSCSDataNodeReport(const std::vector<STNode> &m_vecNodeCount) : m_vecNodeCount(m_vecNodeCount) { }

    const std::vector<STNode> &getNodeCount() const {
        return m_vecNodeCount;
    }

    void setNodeCount(const std::vector<STNode> &nodeCount) {
        CSCSDataNodeReport::m_vecNodeCount = nodeCount;
    }

private:
    std::vector<STNode> m_vecNodeCount;
};

#endif //PROGRAM_SCSDATANODEREPORT_H

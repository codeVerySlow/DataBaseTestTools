//
// Created by Administrator on 2015/12/31.
//

#ifndef _RESULTWRITER_SCSSLAVECHECKREPORT_H_
#define _RESULTWRITER_SCSSLAVECHECKREPORT_H_

#include "SCSReport.h"

class CSCSSlaveCheckReport:public CSCSReport
{
private:
    std::string strIP;
    std::string strPort;
public:
    CSCSSlaveCheckReport(const std::string &strIP, const std::string &strPort) : strIP(strIP), strPort(strPort) { };

    CSCSSlaveCheckReport() : CSCSReport() { };

    const std::string &getStrIP() const {
        return strIP;
    }

    void setStrIP(const std::string &strIP) {
        CSCSSlaveCheckReport::strIP = strIP;
    }

    const std::string &getStrPort() const {
        return strPort;
    }

    void setStrPort(const std::string &strPort) {
        CSCSSlaveCheckReport::strPort = strPort;
    }
};


#endif //PROGRAM_SCSSLAVECHECKREPORT_H

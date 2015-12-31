//
// Created by Administrator on 2015/12/31.
//

#ifndef PROGRAM_SCSDATANODECHECKRESULTWRITER_H
#define PROGRAM_SCSDATANODECHECKRESULTWRITER_H


#include "SCSResultWriter.h"

class CSCSDataNodeCheckResultWriter: public CSCSResultWriter {

public:
    bool Write(const boost::shared_ptr<CSCSReport> report);

    bool Write(const std::vector<boost::shared_ptr<CSCSReport> > &reports);
};


#endif //PROGRAM_SCSDATANODECHECKRESULTWRITER_H

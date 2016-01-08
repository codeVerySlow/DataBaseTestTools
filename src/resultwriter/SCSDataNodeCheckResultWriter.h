#ifndef _RESULTWRITER_SCSDATANODECHECKRESULTWRITER_H_
#define _RESULTWRITER_SCSDATANODECHECKRESULTWRITER_H_


#include "SCSResultWriter.h"

class CSCSDataNodeCheckResultWriter : public CSCSResultWriter
{

public:
    bool Write(boost::shared_ptr<const CSCSReport> report);

};


#endif //PROGRAM_SCSDATANODECHECKRESULTWRITER_H

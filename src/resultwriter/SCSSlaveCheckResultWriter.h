#ifndef _RESULTWRITER_SCSSLAVECHECKRESULTWRITER_H_
#define _RESULTWRITER_SCSSLAVECHECKRESULTWRITER_H_

#include "SCSResultWriter.h"

class CSCSSlaveCheckResultWriter : public CSCSResultWriter
{

public:
    bool Write(boost::shared_ptr<const CSCSReport> report);
};


#endif
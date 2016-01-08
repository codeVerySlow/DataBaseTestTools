#ifndef _RESULTWRITER_SCSTESTRESULTWRITER_H_
#define _RESULTWRITER_SCSTESTRESULTWRITER_H_

#include<fstream>
#include "SCSResultWriter.h"

class CSCSComparerReport;
class CSCSTestResultWriter : public CSCSResultWriter
{
public:
    bool Write(const boost::shared_ptr<const CSCSReport> report);
private:
    void OutPutModulCount(const boost::shared_ptr<const CSCSComparerReport> &testReport,const std::string &module, std::fstream &fs) const;
};


#endif
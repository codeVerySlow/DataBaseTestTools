#ifndef _RESULTWRITER_SCSRESULTWRITER_H_
#define _RESULTWRITER_SCSRESULTWRITER_H_

#include <vector>
#include <boost/shared_ptr.hpp>

enum EMWriterType
{
    WRITERTYPE_DATANODE,
    WRITERTYPE_SLAVECHECK,
    WRITERTYPE_TESTRESULT
};

class CSCSReport;

class CSCSResultWriter
{
public:
    CSCSResultWriter()
    { };

    virtual ~CSCSResultWriter()
    { };

    virtual bool Write(boost::shared_ptr<const CSCSReport> report) = 0;

    bool Write(std::vector<boost::shared_ptr<const CSCSReport> > &reports);

    static boost::shared_ptr<CSCSResultWriter> Create(EMWriterType type);
};

#endif

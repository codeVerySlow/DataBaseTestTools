#include <vector>

#include "SCSResultWriter.h"
#include "SCSDataNodeCheckResultWriter.h"
#include "SCSSlaveCheckResultWriter.h"
#include "SCSTestResultWriter.h"

bool CSCSResultWriter::Write(std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    std::vector<boost::shared_ptr<const CSCSReport> >::iterator iter = reports.begin();
    while (iter != reports.end())
    {
        if (!Write(*iter++))
        {
            return false;
        }
    }
    return true;
}

boost::shared_ptr<CSCSResultWriter> CSCSResultWriter::Create(EMWriterType type)
{
    switch (type)
    {
        case WRITERTYPE_DATANODE:
            return boost::shared_ptr<CSCSResultWriter>(new CSCSDataNodeCheckResultWriter());
        case WRITERTYPE_SLAVECHECK:
            return boost::shared_ptr<CSCSResultWriter>(new CSCSSlaveCheckResultWriter());
        case WRITERTYPE_TESTRESULT:
            return boost::shared_ptr<CSCSResultWriter>(new CSCSTestResultWriter());
    }
    return boost::shared_ptr<CSCSResultWriter>();
}


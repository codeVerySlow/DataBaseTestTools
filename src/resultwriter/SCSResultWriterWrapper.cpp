#include "executer/SCSDataNodeReport.h"
#include "executer/SCSSlaveCheckReport.h"
#include "comparer/SCSComparerReport.h"
#include "SCSResultWriter.h"
#include "SCSResultWriterWrapper.h"

CSCSResultWriterWrapper::CSCSResultWriterWrapper():m_dataNodeWriter(CSCSResultWriter::Create(WRITERTYPE_DATANODE)),
                                                   m_slaveCheckWriter(CSCSResultWriter::Create(WRITERTYPE_SLAVECHECK)),
                                                   m_testResultWriter(CSCSResultWriter::Create(WRITERTYPE_TESTRESULT))
{

}

CSCSResultWriterWrapper::~CSCSResultWriterWrapper()
{

}

bool CSCSResultWriterWrapper::Write(std::vector<boost::shared_ptr<const CSCSReport> > &reports)
{
    std::vector<boost::shared_ptr<const CSCSReport> >::iterator iter = reports.begin();
    while (iter != reports.end())
    {
        if(boost::dynamic_pointer_cast<const CSCSDataNodeReport>(*iter))
        {
            if(!m_dataNodeWriter->Write(*iter))
            {
                return false;
            }
        }
        else if(boost::dynamic_pointer_cast<const CSCSSlaveCheckReport>(*iter))
        {
            if(!m_slaveCheckWriter->Write(*iter))
            {
                return  false;
            }
        }
        else if(boost::dynamic_pointer_cast<const CSCSComparerReport>(*iter))
        {
            if(!m_testResultWriter->Write(*iter))
            {
                return false;
            }
        }

        iter++;
    }
    return true;
}

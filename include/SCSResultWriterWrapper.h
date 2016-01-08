#ifndef _INCLUDE_SCSRESULTWRITERWRAPPER_H_
#define _INCLUDE_SCSRESULTWRITERWRAPPER_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class CSCSReport;
class CSCSResultWriter;

class CSCSResultWriterWrapper
{
public:
    CSCSResultWriterWrapper();

    ~CSCSResultWriterWrapper();

    bool Write(std::vector<boost::shared_ptr<const CSCSReport> > &reports);

private:
    boost::shared_ptr<CSCSResultWriter> m_dataNodeWriter;
    boost::shared_ptr<CSCSResultWriter> m_slaveCheckWriter;
    boost::shared_ptr<CSCSResultWriter> m_testResultWriter;
};

#endif
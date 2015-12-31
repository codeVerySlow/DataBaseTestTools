#ifndef _RESULTWRITER_SCSRESULTWRITER_H_
#define _RESULTWRITER_SCSRESULTWRITER_H_

#include <boost/shared_ptr.hpp>

class CSCSReport;

class CSCSResultWriter
{
public:
	CSCSResultWriter() {};
	virtual ~CSCSResultWriter() {};
	virtual bool Write(const boost::shared_ptr<CSCSReport> report)=0;
	virtual bool Write(const std::vector<boost::shared_ptr<CSCSReport> > &reports)=0;
};

#endif

#ifndef _RESULTWRITER_SCSRESULTWRITER_H_
#define _RESULTWRITER_SCSRESULTWRITER_H_ 

class CSCSReport;

class CSCSResultWriter
{
public:
	CSCSResultWriter() {};
	virtual ~CSCSResultWriter() {};
	virtual bool Write(const CSCSReport &report)=0;
};

#endif

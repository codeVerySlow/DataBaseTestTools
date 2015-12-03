
struct STReport;

class CSCSResultWriter
{
public:
	CSCSResultWriter() {};
	virtual ~CSCSResultWriter() {};
	virtual bool Write(const STReport &report)=0;
};
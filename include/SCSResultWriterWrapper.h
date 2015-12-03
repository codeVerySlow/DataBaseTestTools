
struct STReport;
class CSCSResultWriterWrapper
{
public:
	CSCSResultWriterWrapper();
	~CSCSResultWriterWrapper();
	bool Write(const STReport &report);
private:
	boost::shared_ptr<CSCSResultWriter> resultWriter;
};
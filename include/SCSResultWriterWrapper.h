
class CSCSReport;
class CSCSResultWriterWrapper
{
public:
	CSCSResultWriterWrapper();
	~CSCSResultWriterWrapper();
	bool Write(const CSCSReport &report);
private:
	boost::shared_ptr<CSCSResultWriter> resultWriter;
};
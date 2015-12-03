
#include <string>
#include <boost\shared_ptr.hpp> 

class CSCSPreparedSQLSet;

class CSCSReader{
public:
	Reader() {};
	virtual ~Reader() {};
	virtual STPreparedSQLSet ReadTestSQL()=0;
	virtual bool ValidateTestSQL()=0;
	virtual std::string GetReadPath()=0;
	virtual void SetReadPath(const std::string &path)=0;
	static boost::shared_ptr<Reader> Create();
}
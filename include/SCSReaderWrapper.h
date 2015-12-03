#include <string>
#include <boost/shared_ptr.hpp>

class CSCSReader;
class STPreparedSQLSet;

class CSCSReaderWrapper{
public:
	CSCSReaderWrapper();
	~CSCSReaderWrapper();
	STPreparedSQLSet ReadTestSQL();
	bool ValidateTestSQL();
private:
	boost::shared_ptr<CSCSReader> reader;
}
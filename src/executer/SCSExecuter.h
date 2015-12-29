#ifndef _EXECUTE_SCSEXECUTE_H_
#define _EXECUTE_SCSEXECUTE_H_
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>
#include <util/SCSConfigHelper.h>

enum EMExecuterType
{
	ExecuterType_SCS,
	ExecuterType_MYSQL
};

class CSCSResultIter;
struct STConnect;

class CSCSExecuter{
public:
	CSCSExecuter(){};
	virtual ~CSCSExecuter() {};
	virtual bool OpenDataSource()=0;
	virtual boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql)=0;
	virtual void CloseDataSource()=0;

	virtual bool GetNext(std::vector<std::string> &dataRow)=0;

	static boost::shared_ptr<CSCSExecuter> Create(EMExecuterType type,const STConnect *connect);
};

#endif


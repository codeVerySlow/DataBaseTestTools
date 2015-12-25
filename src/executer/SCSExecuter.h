#ifndef _EXECUTE_SCSEXECUTE_H_
#define _EXECUTE_SCSEXECUTE_H_
#include <string>
#include <vector>

class CSCSResultIter;

class CSCSExecuter{
public:
	CSCSExecuter() {};
	virtual ~CSCSExecuter() {};
	virtual bool OpenDataSource()=0;
	virtual CSCSResultIter ExecuteSQL(const std::string &sql)=0;
	virtual void CloseDataSource()=0;

	virtual bool GetNext(std::vector<std::string> &dataRow)=0;

	static boost::shared_ptr<CSCSExecuter> Create();
};

#endif
#ifndef _EXECUTE_SCSEXECUTE_H_
#define _EXECUTE_SCSEXECUTE_H_
#include <string>
#include <vector>

class CSCSResultIter;

class CSCSExecuter{
public:
	friend CSCSResultIter;
	CSCSExecuter() {};
	virtual ~CSCSExecuter() {};
	virtual bool OpenDataSource(const std::string &user,const std::strin &password,const std::string &ip,const std::string &database)=0;
	virtual CSCSResultIter ExecuteSQL(const std::string &sql)=0;
	virtual void CloseDataSource()=0;

	static boost::shared_ptr<CSCSExecuter> Create();
};

#endif
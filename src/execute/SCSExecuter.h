#ifndef _EXECUTE_SCSEXECUTE_H_
#define _EXECUTE_SCSEXECUTE_H_
#include <string>
#include <vector>
#include <boost/shared_ptr.hpp>

class CSCSResultIter;

class CSCSExecuter{
public:
	friend CSCSResultIter;
	CSCSExecuter() {};
	virtual ~CSCSExecuter() {};
	virtual bool OpenDataSource(const std::string &user,const std::strin &password,const std::string &ip,const std::string &database)=0;
	virtual boost::shared_ptr<CSCSResultIter> ExecuteSQL(const std::string &sql)=0;
	virtual void CloseDataSource()=0;

	static boost::shared_ptr<CSCSExecuter> Create();
private:
	virtual std::vector<std::string> GetNextRow()=0;
}

#endif
#ifndef _EXECUTER_SCSSCSEXECUTER_H_
#define _EXECUTER_SCSSCSEXECUTER_H_

#include "SCSExecuter.h"

class CSCSSCSHelper;

class CSCSSCSExecuter:public CSCSExecuter
{
public:
	bool OpenDataSource();
	CSCSResultIter ExecuteSQL(const std::string &sql);
	void CloseDataSource();

	bool GetNext(std::vector<std::string> &dataRow);
private:
	CSCSSCSHelper scs;
};

#endif
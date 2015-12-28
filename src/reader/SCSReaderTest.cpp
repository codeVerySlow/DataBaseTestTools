#include <assert.h>

#include "SCSMySqlReader.h"
#include "SCSPreparedSQLSet.h"
#include "../util/SCSConfigHelper.h"

int main()
{
	assert(CSCSConfigHelper::GetInstance()->Read());

	CSCSPreparedSQLSet set;
	STSQLPair pair;
	CSCSMySqlReader reader;

	while(reader.ReadNextTestCase(set))
	{
		std::cout<<"Get SQLSet Sucess"<<std::endl;
		std::cout<<"CheckSequence:"<<set.m_checkSequence<<std::endl;
		std::cout<<"CheckDataNodes:"<<set.m_checkDataNodes<<std::endl;
		std::cout<<"ExecTimes:"<<set.m_nExecTimes<<std::endl;
		std::cout<<"module:"<<set.m_strModule<<std::endl;
		while(set.GetNext(pair))
		{
			std::cout<<"srcSQL"<<pair.strSQLSource<<std::endl;
			std::cout<<"desSQL"<<pair.strSQLDestination<<std::endl;
		}
	} 
}

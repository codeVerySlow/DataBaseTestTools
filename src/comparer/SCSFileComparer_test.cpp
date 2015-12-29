#include <iostream>
#include <assert.h>
#include <SCSResultIter.h>
#include <executer/SCSExecuter.h>
#include "SCSFileComparer.h"

int main(void)
{
	CSCSFileComparer c;
	CSCSResultIter iter1(CSCSExecuter::Create(ExecuterType_SCS));
	CSCSResultIter iter2(CSCSExecuter::Create(ExecuterType_SCS));

	assert(c.Compare(&iter1,&iter2));
	
	std::cout<<"success"<<std::endl;
	return 0;
}

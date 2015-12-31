#include <fstream>
#include "executer/SCSDataNodeReport.h"
#include "DBLog.h"
#include "SCSDataNodeCheckResultWriter.h"

bool CSCSDataNodeCheckResultWriter::Write(const boost::shared_ptr<CSCSReport> report)
{
    boost::shared_ptr<CSCSDataNodeReport> dataNodeReport;
    if(!(dataNodeReport=boost::dynamic_pointer_cast<CSCSDataNodeReport>(report)))
    {
        LOG_ERROR("DataNodeCheckResultWriter err:try to write err type which is not CSCSDataNodeReport");
        return false;
    }

    std::string filePath ="./report/";
    filePath+="DataNodesQuantity_20151207.report";
    std::fstream fs(filePath,std::ios::in|std::ios::app);
    if(!fs)
    {
        LOG_ERROR(("DataNodeCheckResultWriter err:open file err "+filePath).c_str());
        return false;
    }

    fs<<"DataNodesQuantity报告"<<std::endl;
    fs<<"=========================================================================="<<std::endl;
    fs<<"开始时间:	"<<std::endl;
    fs<<"结束时间:	2015-12-13 10:00:00"<<std::endl;
    fs<<"运行时长:	24:06:00"<<std::endl;
    fs<<"当前SCSDB版本:	1.11.3"<<std::endl;
    fs<<"=========================================================================="<<std::endl;
    fs<<"[select][117]insert into test values (1,'remark')###select t.* from t(test)"<<std::endl;
    fs<<"IP                     tablename		count"<<std::endl;
    std::vector<STNode>::const_iterator nodeIter=dataNodeReport->getNodeCount().begin();
    while(nodeIter!=dataNodeReport->getNodeCount().end())
    {
        fs<<(*nodeIter).IP<<":"<<(*nodeIter).Port<<"		"<<(*nodeIter).TableName<<"			"<<(*nodeIter++).Count<<std::endl;
    }
    fs<<"=========================================================================="<<std::endl;

    return true;
}

bool CSCSDataNodeCheckResultWriter::Write(const std::vector<boost::shared_ptr<CSCSReport> > &reports) {
    std::vector<boost::shared_ptr<CSCSReport> >::const_iterator iter=reports.begin();
    while(iter!=reports.end())
    {
        if(!Write(*iter++))
        {
            return false;
        }
    }
    return true;
}

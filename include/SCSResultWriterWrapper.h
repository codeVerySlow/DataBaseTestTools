#ifndef _INCLUDE_SCSRESULTWRITERWRAPPER_H_
#define _INCLUDE_SCSRESULTWRITERWRAPPER_H_

#include <vector>
#include <boost/shared_ptr.hpp>

class CSCSReport;
class CSCSResultWriter;
//报告输出包装类
class CSCSResultWriterWrapper
{
public:
    CSCSResultWriterWrapper();

    ~CSCSResultWriterWrapper();
    //功能：将测试结果、监控结果等以报告的形式输出到磁盘
    //返回值：bool 写入成功 true 写入失败 false
    //参数：reports 报告结果集合
    bool Write(std::vector<boost::shared_ptr<const CSCSReport> > &reports);

private:
    boost::shared_ptr<CSCSResultWriter> m_dataNodeWriter;
    boost::shared_ptr<CSCSResultWriter> m_slaveCheckWriter;
    boost::shared_ptr<CSCSResultWriter> m_testResultWriter;
};

#endif
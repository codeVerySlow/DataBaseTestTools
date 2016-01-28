#include <fstream>
#include <string>
#include <assert.h>

#include "SCSFileComparer.h"
#include "SCSResultIter.h"
#include "util/SCSSortCache.h"
#include "util/SCSCrc32c.h"
#include "SCSComparerReport.h"
#include "util/SCSUtilTools.h"

CSCSFileComparer::CSCSFileComparer() : m_testcasereport(new STTestCaseReport)
{
}

bool CSCSFileComparer::Compare(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2)
{
    //新建测试报告
    m_testcasereport=boost::shared_ptr<STTestCaseReport>(new STTestCaseReport);
    //新建排序缓存
    CSCSSortCache cache1("sort_crc_1");
    CSCSSortCache cache2("sort_crc_2");

    std::vector<std::string> column1;
    std::vector<std::string> column2;
    //将数据写入缓存
    WriteCRCToCache(iter1, cache1,column1);
    WriteCRCToCache(iter2, cache2,column2);
    //填写报告里的列名数据
    m_testcasereport->srcColumn=column1;
    m_testcasereport->desColumn=column2;
    //对缓存进行排序（小数据量采用set自带的排序，大数据量采用多路归并排序）
    cache1.Short();
    cache2.Short();

    unsigned int crc1;
    unsigned int crc2;
    bool crc1Finish = false;
    bool crc2Finish = false;

    while (1)
    {
        //从缓存中读取已经排序好的数据
        crc1Finish = !cache1.Read(&crc1);
        crc2Finish = !cache2.Read(&crc2);
        if (crc1Finish || crc2Finish)
        {
            break;
        }
        //发现数据不一致
        if (crc1 != crc2)
        {
            m_testcasereport->m_emDisMatchType=DISMATCHTYPE_ROW;
            m_testcasereport->srcRow.push_back(cache1.GetRealData(crc1));
            m_testcasereport->desRow.push_back(cache2.GetRealData(crc2));
            return false;
        }
    }
    //发现两组数据数量不相等
    if(!(crc1Finish&&crc2Finish))
    {
        m_testcasereport->m_emDisMatchType=DISMATCHTYPE_ROWCOUNT;
        m_testcasereport->srcRow.push_back(SCSUtilTools::NumberToString(cache1.getTotal()));
        m_testcasereport->desRow.push_back(SCSUtilTools::NumberToString(cache2.getTotal()));
    }

    return crc1Finish && crc2Finish;
}

bool CSCSFileComparer::CompareSequence(boost::shared_ptr<CSCSResultIter> iter1, boost::shared_ptr<CSCSResultIter> iter2)
{
    m_testcasereport=boost::shared_ptr<STTestCaseReport>(new STTestCaseReport);

    std::vector<std::string> iter1Data;
    std::vector<std::string> iter2Data;

    int iter1Count=0;
    int iter2Count=0;

    bool iter1Finish = false;
    bool iter2Finish = false;
    while (1)
    {
        iter1Finish = !iter1->GetNext(iter1Data);
        iter2Finish = !iter2->GetNext(iter2Data);
        //如果有一个迭代器读完了就退出对比
        if(iter1Finish||iter2Finish)
        {
            break;
        }
        //列数不相同
        if (iter1Data.size() != iter2Data.size())
        {
            m_testcasereport->m_emDisMatchType=DISMATCHTYPE_COLUM;
            m_testcasereport->srcRow=iter1Data;
            m_testcasereport->desRow=iter2Data;
            return false;
        }

        std::vector<std::string>::iterator iterator1 = iter1Data.begin();
        std::vector<std::string>::iterator iterator2 = iter2Data.begin();

        while (iterator1 != iter1Data.end())
        {
            //数据不相同
            if (*iterator1 != *iterator2)
            {
                *iterator1 += "???";
                *iterator2 += "???";
                m_testcasereport->m_emDisMatchType=DISMATCHTYPE_ROW;
                m_testcasereport->srcRow=iter1Data;
                m_testcasereport->desRow=iter2Data;
                return false;
            }
            iterator1++;
            iterator2++;
        }
        iter1Count++;
        iter2Count++;
    }
    //如果数据没有读完 读完并且计行数
    if(!iter1Finish)
    {
        while (iter1->GetNext(iter1Data))
        {
            iter1Count++;
        }
    }
    //如果数据没有读完 读完并且计行数
    if(!iter2Finish)
    {
        while(iter2->GetNext(iter2Data))
        {
            iter2Count++;
        }
    }
    //数据总行数不一样
    if(!(iter1Finish&&iter2Finish))
    {
        m_testcasereport->m_emDisMatchType=DISMATCHTYPE_ROWCOUNT;
        m_testcasereport->srcRow.push_back(SCSUtilTools::NumberToString(iter1Count));
        m_testcasereport->desRow.push_back(SCSUtilTools::NumberToString(iter2Count));
    }

    return iter1Finish && iter2Finish;
}

boost::shared_ptr<STTestCaseReport> CSCSFileComparer::GetReport() const
{
    return m_testcasereport;
}

void CSCSFileComparer::WriteCRCToCache(boost::shared_ptr<CSCSResultIter> iter, CSCSSortCache &cache,std::vector<std::string> &column)
{
    bool isColumn=true;
    std::vector<std::string> iterData;
    while (iter->GetNext(iterData))
    {
        if(isColumn)
        {
            isColumn= false;
            column = iterData;
        }
        cache << iterData;
    }
}

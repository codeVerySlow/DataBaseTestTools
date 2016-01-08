#ifndef _UTIL_SCSEXTERNSORT_H_
#define _UTIL_SCSEXTERNSORT_H_
/* 
* �������������� 
* ��·�鲢���� 
*/

#include <stdio.h>

#define MIN 0//���￪ʼ��ʱ�������һ��BUG����������MIN���ڵ��ڴ����������������㷨���ִ���
#define MAX 0xFFFFFFFF//���ֵ�������ڹ鲢�ļ���β
typedef unsigned int *LoserTree;
typedef unsigned int *External;

class CSCSExternSort
{
public:
    void sort();

    //input_file:�����ļ���
    //out_file:����ļ���
    //count: ÿ�����ڴ����������������
    CSCSExternSort(const char *input_file, const char *out_file, int count);

    virtual ~CSCSExternSort();

private:
    int m_count; //���鳤��
    char *m_in_file;   //�����ļ���·��
    char *m_out_file; //����ļ���·��
    int k;
    //�鲢������������Ҫ������֮����ܵõ������������ls��b��ֻ�ܶ���Ϊָ��(ע�����������)
    LoserTree ls;
    //�����Ϊָ�룬֮��̬��������
    External b;

    //�����Ϊָ�룬�ڳ�Ա�����п��԰�����������ʹ��
    int read_data(FILE *f, unsigned int a[], int n);

    void write_data(FILE *f, unsigned int a[], int n);

    char *temp_filename(int index);

    static int cmp_int(const void *a, const void *b);

    int memory_sort();

    void Adjust(int s);

    void CreateLoserTree();

    void K_Merge();
};

#endif  

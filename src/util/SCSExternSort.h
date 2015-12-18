#include <iostream>  
#include <ctime>  
#include <fstream>  

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
//#include "ExternSort.h"  
using namespace std;  

//ʹ�ö�·�鲢�������������  
//ExternSort.h  

/* 
* �������������� 
* ��·�鲢���� 
* ��ǧ��������С��������Ϊ�� 
* һ���Ƚϼ򵥵����ӣ�û�н����ڴ滺���� 
*/  

#ifndef EXTERN_SORT_H  
#define EXTERN_SORT_H  

#include <cassert>  
//#define k 5  
#define MIN -1//���￪ʼ��ʱ�������һ��BUG����������MIN���ڵ��ڴ����������������㷨���ִ���
#define MAX 10000000//���ֵ�������ڹ鲢�ļ���β
typedef int* LoserTree;
typedef int* External;

class CSCSExternSort  
{  
public:  
	void sort() ;
	//input_file:�����ļ���  
	//out_file:����ļ���  
	//count: ÿ�����ڴ����������������  
	CSCSExternSort(const char *input_file, const char * out_file, int count);
	virtual ~CSCSExternSort();
private:  
	int m_count; //���鳤��  
	char *m_in_file;   //�����ļ���·��  
	char *m_out_file; //����ļ���·��  
	int k;//�鲢������������Ҫ������֮����ܵõ������������ls��b��ֻ�ܶ���Ϊָ��(ע�����������)
	LoserTree ls;//�����Ϊָ�룬֮��̬��������
	External b;//�����Ϊָ�룬�ڳ�Ա�����п��԰�����������ʹ��
	//int External[k];
protected:  
	int read_data(FILE* f, int a[], int n); 
	void write_data(FILE* f, int a[], int n) ; 
	char* temp_filename(int index); 
	static int cmp_int(const void *a, const void *b);  
	int memory_sort();
	void Adjust(int s);
	void CreateLoserTree();
	void K_Merge();
};  

#endif  
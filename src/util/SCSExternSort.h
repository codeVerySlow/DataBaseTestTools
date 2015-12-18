#ifndef EXTERN_SORT_H  
#define EXTERN_SORT_H
/* 
* 大数据量的排序 
* 多路归并排序 
*/ 

#include <stdio.h>

#define MIN 0//这里开始的时候出现了一个BUG，如果定义的MIN大于等于待排序的数，则会是算法出现错误
#define MAX 0xFFFFFFFF//最大值，附加在归并文件结尾
typedef unsigned int* LoserTree;
typedef unsigned int* External;

class CSCSExternSort  
{  
public:  
	void sort() ;
	//input_file:输入文件名  
	//out_file:输出文件名  
	//count: 每次在内存中排序的整数个数  
	CSCSExternSort(const char *input_file, const char * out_file, int count);
	virtual ~CSCSExternSort();
private:  
	int m_count; //数组长度  
	char *m_in_file;   //输入文件的路径  
	char *m_out_file; //输出文件的路径  
	int k;//归并数，此数必须要内排序之后才能得到，所以下面的ls和b都只能定义为指针(注意和书上区别)
	LoserTree ls;//定义成为指针，之后动态生成数组
	External b;//定义成为指针，在成员函数中可以把它当成数组使用
	int read_data(FILE* f, unsigned int a[], int n); 
	void write_data(FILE* f, unsigned int a[], int n) ; 
	char* temp_filename(int index); 
	static int cmp_int(const void *a, const void *b);  
	int memory_sort();
	void Adjust(int s);
	void CreateLoserTree();
	void K_Merge();
};  

#endif  

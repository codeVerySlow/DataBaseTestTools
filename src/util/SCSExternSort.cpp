#include <ctime>  
#include <fstream>  
#include <cassert> 
#include <iostream>

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "SCSExternSort.h"

using namespace std;

void CSCSExternSort::sort()
{
    clock_t t = clock();

    //将文件内容分块在内存中排序，并分别写入临时文件
    k = memory_sort();  //

    //归并临时文件内容到输出文件
    //merge_sort(file_count);
    ls = new unsigned int[k];
    b = new unsigned int[k + 1];
    K_Merge();
    delete[]ls;
    delete[]b;
    t=clock()-t;
    printf("sort total click:%ld (%f seconds)\n", t,((float)t)/CLOCKS_PER_SEC);
}

CSCSExternSort::CSCSExternSort(const char *input_file, const char *out_file, int count)
{
    m_count = count;
    m_in_file = new char[strlen(input_file) + 1];
    strcpy(m_in_file, input_file);
    m_out_file = new char[strlen(out_file) + 1];
    strcpy(m_out_file, out_file);
}

CSCSExternSort::~CSCSExternSort()
{
    delete[] m_in_file;
    delete[] m_out_file;
}

int CSCSExternSort::read_data(FILE *f, unsigned int a[], int n)
{
    int i = 0;
    while (i < n && (fscanf(f, "%u", &a[i]) != EOF))
    { i++; }
    //printf("read:%d integer\n", i);
    return i;
}

void CSCSExternSort::write_data(FILE *f, unsigned int a[], int n)
{
    for (int i = 0; i < n; ++i)
    {
        fprintf(f, "%u ", a[i]);
    }
    fprintf(f, "%u", MAX);//在最后写上一个最大值
}

char *CSCSExternSort::temp_filename(int index)
{
    char *tempfile = new char[100];
    sprintf(tempfile, "temp%d", index);
    return tempfile;
}

int CSCSExternSort::cmp_int(const void *a, const void *b)
{
    if (*(unsigned int *) a > *(unsigned int *) b)
    {
        return 1;
    }
    else if (*(unsigned int *) a == *(unsigned int *) b)
    {
        return 0;
    }
    else
    {
        return -1;
    }
}

int CSCSExternSort::memory_sort()
{
    FILE *fin = fopen(m_in_file, "rt");
    int n = 0, file_count = 0;
    unsigned int *array = new unsigned int[m_count];

    //每读入m_count个整数就在内存中做一次排序，并写入临时文件
    while ((n = read_data(fin, array, m_count)) > 0)
    {
        qsort(array, n, sizeof(unsigned int), cmp_int);
        char *fileName = temp_filename(file_count++);
        FILE *tempFile = fopen(fileName, "w");
        free(fileName);
        write_data(tempFile, array, n);
        fclose(tempFile);
    }

    delete[] array;
    fclose(fin);

    return file_count;
}

void CSCSExternSort::Adjust(int s)
{
    //沿从叶子节点b[s]到根节点ls[0]的路径调整败者树
    int t = (s + k) / 2;//ls[t]是b[s]的父节点
    while (t > 0)
    {
        if (b[s] > b[ls[t]])//如果失败，则失败者位置s留下，s指向新的胜利者
        {
            int tmp = s;
            s = ls[t];
            ls[t] = tmp;
        }
        t = t / 2;
    }
    ls[0] = s;//ls[0]存放调整后的最大值的位置
}

void CSCSExternSort::CreateLoserTree()
{
    b[k] = MIN;//额外的存储一个最小值
    int i;
    for (i = 0; i < k; i++)
    { ls[i] = k; }//先初始化为指向最小值，这样后面的调整才是正确的
                  //这样能保证非叶子节点都是子树中的“二把手”
    for (i = k - 1; i >= 0; i--)
    {
        Adjust(i);//依次从b[k-1],b[k-2]...b[0]出发调整败者树
    }
}

void CSCSExternSort::K_Merge()
{
    //利用败者数把k个输入归并段归并到输出段中
    //b中前k个变量存放k个输入段中当前记录的元素
    //归并临时文件
    FILE *fout = fopen(m_out_file, "wt");
    FILE **farray = new FILE *[k];
    int i;
    for (i = 0; i < k; ++i)  //打开所有k路输入文件
    {
        char *fileName = temp_filename(i);
        farray[i] = fopen(fileName, "rt");
        free(fileName);
    }

    for (i = 0; i < k; ++i)  //初始读取
    {
        if (fscanf(farray[i], "%u", &b[i]) == EOF)//读每个文件的第一个数到data数组
        {
            //printf("there is no %d file to merge!",k);
            return;
        }
    }
    //    for(int i=0;i<k;i++)input(b[i]);

    CreateLoserTree();
    int q;
    while (b[ls[0]] != MAX)//
    {
        q = ls[0];//q用来存储b中最小值的位置，同时也对应一路文件
        //output(q);
        fprintf(fout, "%u ", b[q]);
        //input(b[q],q);
        fscanf(farray[q], "%u", &b[q]);
        Adjust(q);
    }
    //output(ls[0]);
    fprintf(fout, "%u ", b[ls[0]]);
    //delete [] hasNext;
    //delete [] data;

    for (i = 0; i < k; ++i) //清理工作
    {
        fclose(farray[i]);
    }
    delete[] farray;
    fclose(fout);
}

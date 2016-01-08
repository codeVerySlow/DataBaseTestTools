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

    //���ļ����ݷֿ����ڴ������򣬲��ֱ�д����ʱ�ļ�
    k = memory_sort();  //

    //�鲢��ʱ�ļ����ݵ�����ļ�
    //merge_sort(file_count);
    ls = new unsigned int[k];
    b = new unsigned int[k + 1];
    K_Merge();
    delete[]ls;
    delete[]b;
    t=clock()-t;
    printf("total click:%ld (%f seconds)\n", t,((float)t)/CLOCKS_PER_SEC);
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
    fprintf(f, "%u", MAX);//�����д��һ�����ֵ
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

    //ÿ����m_count�����������ڴ�����һ�����򣬲�д����ʱ�ļ�
    while ((n = read_data(fin, array, m_count)) > 0)
    {
        qsort(array, n, sizeof(unsigned int), cmp_int);
        //��������˿⺯�������ڵ��Ľڵ�cʵ������ٵ���qsort��
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
{//�ش�Ҷ�ӽڵ�b[s]�����ڵ�ls[0]��·������������
    int t = (s + k) / 2;//ls[t]��b[s]��˫�׽ڵ�
    while (t > 0)
    {
        if (b[s] > b[ls[t]])//���ʧ�ܣ���ʧ����λ��s���£�sָ���µ�ʤ����
        {
            int tmp = s;
            s = ls[t];
            ls[t] = tmp;
        }
        t = t / 2;
    }
    ls[0] = s;//ls[0]��ŵ���������ֵ��λ��
}

void CSCSExternSort::CreateLoserTree()
{
    b[k] = MIN;//����Ĵ洢һ����Сֵ
    int i;
    for (i = 0; i < k; i++)
    { ls[i] = k; }//�ȳ�ʼ��Ϊָ����Сֵ����������ĵ���������ȷ��
    //�����ܱ�֤��Ҷ�ӽڵ㶼�������еġ������֡�
    for (i = k - 1; i >= 0; i--)
    {
        Adjust(i);
    }//���δ�b[k-1],b[k-2]...b[0]��������������
}

void CSCSExternSort::K_Merge()
{//���ð�������k������鲢�ι鲢���������
    //b��ǰk���������k��������е�ǰ��¼��Ԫ��
    //�鲢��ʱ�ļ�
    FILE *fout = fopen(m_out_file, "wt");
    FILE **farray = new FILE *[k];
    int i;
    for (i = 0; i < k; ++i)  //������k·�����ļ�
    {
        char *fileName = temp_filename(i);
        farray[i] = fopen(fileName, "rt");
        free(fileName);
    }

    for (i = 0; i < k; ++i)  //��ʼ��ȡ
    {
        if (fscanf(farray[i], "%u", &b[i]) == EOF)//��ÿ���ļ��ĵ�һ������data����
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
        q = ls[0];//q�����洢b����Сֵ��λ�ã�ͬʱҲ��Ӧһ·�ļ�
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

    for (i = 0; i < k; ++i)  //������
    {
        fclose(farray[i]);
    }
    delete[] farray;
    fclose(fout);
}

/*******************************************************
�������ܣ� ��ȡԭʼ���ݵ����� 

*******************************************************/
#include "exportdata.h"
#include "public.h"
#include "stdlib.h"
#include "stdio.h"
double ori_arrdata[CUSTOMNUM][INDEXNUM] = {0.0};
void  Get_OriData(FILE **pfile_in,FILE **pfile_out) 
{
	*pfile_in=fopen("FisherScorein.txt","r");
	if(*pfile_in==NULL)
	{
		printf("Can't open file FisherScorein.txt.\n");
		exit(1);
	}
	*pfile_out=fopen("Result.txt","w");
	if(*pfile_out==NULL)
	{
		fprintf(stderr,"Can't open file Result.txt!\n");
		exit(2);
	}	
} 

/**************��ȡ�ļ�����**************************/
unsigned int Get_Line_Num(FILE *pfile)
{
	char c = 0,cb = '\0';//cbΪ��ǰ�ַ�����һ���ַ� 
	int line_num = 0;
	while((c = fgetc(pfile)) != EOF)
	{
		if(c=='\n')
		{
			line_num++;
		}
		cb = c;
	} 
	if(cb != '\n')//���һ��ûд����պ�д��û���е������ҲҪ��һ�� 
		line_num++;	
	fclose(pfile);	
	return line_num;
 } 
 
 
 unsigned int Get_Row_Num(FILE *pfile)
 {

 }
 
 /******************************************************
�������ܣ� ���ı��ַ�����ת�浽���������� 
�������ƣ�
����˵����    pfile  ȫ���ļ�ָ�룬ֱ�Ӳ����ı��ڵ�����
              index_num  ָ�����
			  cus_num    �ͻ����� 
******************************************************/
double Text_To_Arry(FILE *pfile,double arr[CUSTOMNUM][INDEXNUM])
{
	int i = 0,j = 0;
	char ctempstr[12];//��ʱ�����ַ����洢 
	double dtemp;//��ʱ����ת�����ݣ� 
	for(i = 0;i < CUSTOMNUM;i++)
	{
		for(j = 0;j < INDEXNUM;j++)
		{ 
			fscanf(pfile,"%s",ctempstr);//˵������������Զ������ļ�ָ����Ѱ��һ���ַ����Ĺ��� 
			dtemp = atof(ctempstr);
			arr[i][j] = dtemp;
						
		} 
	}	
} 


/******************************************************
�������ܣ�  ��ӡ�����ļ����ݺ�����飬ӡ֤�����Ƿ��ȡ��ȷ 
�������ƣ�
����˵����   
*******************************************************/  
double Print_Arr(double arr[CUSTOMNUM][INDEXNUM])
{
	int i = 0,j = 0;
	for(i = 0;i < CUSTOMNUM;i++)
	{	 
		for(j = 0;j < INDEXNUM;j++)
		{
			printf("%.9lf\t",arr[i][j]);//���ҲС�����9λ��ʾ 
		}		
	}
}

/******************************************************
�������ܣ�  ��ӡָ��ṹ�� 
�������ƣ�
����˵����   
*******************************************************/  
void Print_ST(void)
{
	int i = 0,j = 0;
	 
	for(j = 0;j < INDEXNUM;j++)
	{
		 for(i = 0;i < CUSTOMNUM;i++)
		{
        	printf("%.9lf\t",st_index[j].pindex_data[i]);
		}
		printf("\n");
	}		
}
/*****************��ӡ����ĳһָ�������*********************/
void Print_x_Index(INDEX_ATTRI_ST  *st_index,int index_num,int from_cus_start,int from_cus_end)
{
	int i = 0;
	 
	for(i = from_cus_start-1;i < from_cus_end;i++)
	{
    	printf("%.9lf\t",st_index[index_num-1].pindex_data[i]);
	}
	printf("\n");	
}


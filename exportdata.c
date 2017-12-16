/*******************************************************
函数功能： 获取原始数据到数组 

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

/**************获取文件行数**************************/
unsigned int Get_Line_Num(FILE *pfile)
{
	char c = 0,cb = '\0';//cb为当前字符的上一个字符 
	int line_num = 0;
	while((c = fgetc(pfile)) != EOF)
	{
		if(c=='\n')
		{
			line_num++;
		}
		cb = c;
	} 
	if(cb != '\n')//最后一行没写满或刚好写满没换行的情况，也要算一行 
		line_num++;	
	fclose(pfile);	
	return line_num;
 } 
 
 
 unsigned int Get_Row_Num(FILE *pfile)
 {

 }
 
 /******************************************************
函数功能： 将文本字符数据转存到浮点数组中 
函数名称：
参数说明：    pfile  全局文件指针，直接操作文本内的数据
              index_num  指标个数
			  cus_num    客户个数 
******************************************************/
double Text_To_Arry(FILE *pfile,double arr[CUSTOMNUM][INDEXNUM])
{
	int i = 0,j = 0;
	char ctempstr[12];//临时浮点字符串存储 
	double dtemp;//临时浮点转存数据； 
	for(i = 0;i < CUSTOMNUM;i++)
	{
		for(j = 0;j < INDEXNUM;j++)
		{ 
			fscanf(pfile,"%s",ctempstr);//说明这个函数有自动根据文件指针搜寻下一个字符串的功能 
			dtemp = atof(ctempstr);
			arr[i][j] = dtemp;
						
		} 
	}	
} 


/******************************************************
函数功能：  打印拷贝文件内容后的数组，印证数据是否获取正确 
函数名称：
参数说明：   
*******************************************************/  
double Print_Arr(double arr[CUSTOMNUM][INDEXNUM])
{
	int i = 0,j = 0;
	for(i = 0;i < CUSTOMNUM;i++)
	{	 
		for(j = 0;j < INDEXNUM;j++)
		{
			printf("%.9lf\t",arr[i][j]);//输出也小数点后9位显示 
		}		
	}
}

/******************************************************
函数功能：  打印指标结构体 
函数名称：
参数说明：   
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
/*****************打印具体某一指标的数据*********************/
void Print_x_Index(INDEX_ATTRI_ST  *st_index,int index_num,int from_cus_start,int from_cus_end)
{
	int i = 0;
	 
	for(i = from_cus_start-1;i < from_cus_end;i++)
	{
    	printf("%.9lf\t",st_index[index_num-1].pindex_data[i]);
	}
	printf("\n");	
}


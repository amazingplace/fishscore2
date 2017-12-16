#ifndef _PUBLIC_H
#define _PUBLIC_H
#include "algorithm.h"
#include "exportdata.h"
#include "stdio.h"
#define   INDEXNUM  66  //定义指标总量 
#define   CUSTOMNUM 3045   //定义客户人数 
#define   PER_GET   20  //定义每次取的指标 

typedef struct index_arr
{
	char index;//
	struct index_arr *pnext;
}index_suffix,*pindex_suffix;//下标结构体 
typedef struct
{
	unsigned char index_usedflag:1;//被使用标志位，指在循环中被使用 
	unsigned char index_chosedflag:1;//被选择标志位，指从多个指标中选择出来计算。 
	unsigned char reserved:6; 
}INDEX_FLAG; 

typedef struct
{ 
    INDEX_FLAG    index_flag;
    double        *pindex_data;    //指向指标对应的客户数据数组的指针
    double        *pcustom_score;  //指针指向客户得分数组 
    unsigned char *prenege_flag;   //指向指标对应的客户违约标志位，一个客户只有一个违约状态。 
    int           index_cus_num;   //指标对应的客户个数
    double Xi0;                    //Xi0指标i对应的非违约客户指标数值的平均值
	double Xi1;				       //Xi1指标i对应的违约客户数值的平均值,  
	double Xi;				       //Xi指标i对应的所有客户数值的平均值,
    double        single_fishscore;//单个指标的fishscore值
    double        weight;          //单个指标的权值 
}INDEX_ATTRI_ST;//指标属性结构体定义 

extern const double ESP; //
extern FILE *fp1,*fp2;//定义文件指针 
extern INDEX_ATTRI_ST  st_index[INDEXNUM];//
extern int   renege,no_renege;//违约，非违约人数 
extern double max_chosed_fishscore;
extern void Arrary_Change(INDEX_ATTRI_ST st_index[INDEXNUM],double arr[CUSTOMNUM][INDEXNUM]);
extern double ori_arrdata[CUSTOMNUM][INDEXNUM];
extern void  Get_OriData(FILE** pfile_in,FILE **pfile_out);
extern unsigned int Get_Line_Num(FILE *pfile); 
extern unsigned int Get_Row_Num(FILE *pfile); 
extern double Text_To_Arry(FILE *pfile,double arr[CUSTOMNUM][INDEXNUM]);
extern void Print_ST(void); 
extern void Print_x_Index(INDEX_ATTRI_ST *st_index,int index_num,int from_cus_start,int from_cus_end); 
extern void Find_Renege_People(int *renege,int *no_renege); 
extern unsigned char * Renege_Flag(double arr[CUSTOMNUM][INDEXNUM]);

extern long long unsigned int C(unsigned int m,unsigned int n);
extern int A(int m,int n);
extern double Alg_Calculate_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM]);
extern double  Alg_Calculate_F_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM]);
extern double  Alg_Cal_x_F_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM],int index_num,char *psuffix_index);
extern pindex_suffix  Alg_Get_Combination(INDEX_ATTRI_ST st_index[INDEXNUM],unsigned char m, unsigned char n);
extern unsigned char  Alg_Get_Add_index_suffix(pindex_suffix psuffix_remained_index,unsigned char m,unsigned char n);
extern char Get_One_Reminder_Index_Suffix(pindex_suffix index_head,char rand_val); 
extern double  Alg_Cal_List_x_F_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM],int index_num,pindex_suffix pchosedindex_suffix);
extern pindex_suffix  Alg_Generate_remained_index(pindex_suffix psuffix_index,unsigned char m,unsigned char n);

extern pindex_suffix List_Creat(unsigned char m);
extern pindex_suffix List_Delete(pindex_suffix head,pindex_suffix psuffix_index,unsigned char n); 
extern void List_Print(pindex_suffix index_head);
extern char List_Write(pindex_suffix index_head,char value,unsigned char n);
extern char List_Read(pindex_suffix index_head,unsigned char n);
extern pindex_suffix List_Del(pindex_suffix index_head,unsigned char value);
extern unsigned char Alg_Genrate_Rand_value(unsigned char m,unsigned char n); 
//extern 
#endif

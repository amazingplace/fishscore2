#include "algorithm.h"
#include "public.h"
#include "math.h"
#include "malloc.h"
#include "stdlib.h" 
#include "string.h" 
#include "time.h"
const double ESP = 1e-6; //
INDEX_ATTRI_ST  st_index[INDEXNUM] = {0};//����ָ������ ������66��ָ�� 
int   renege = 0,no_renege = 0;//ΥԼ����ΥԼ���� 
double sum_of_sglfishscore = 0;//����ָ���fishscore�ĺ� 
double max_chosed_fishscore = 0;
/******************************************************
�������ܣ�  ��ʼ�����ݽṹ��
�������ƣ�
����˵����   
*******************************************************/  
void Alg_Struct_Init(INDEX_ATTRI_ST st_index[INDEXNUM],double arr[CUSTOMNUM][INDEXNUM])
{
	int i,j;
	unsigned char *prenege_flag_temp = NULL;
	double *pcustom_score_temp = NULL;
 	 Arrary_Change(st_index,ori_arrdata);//���鵽�ṹ�� 
  	 prenege_flag_temp = Renege_Flag(ori_arrdata);
  	 pcustom_score_temp = (double *)malloc(CUSTOMNUM*sizeof(double));//ÿ���ͻ�����һ���÷�
	 memset(pcustom_score_temp,0,CUSTOMNUM*sizeof(double)); 
 	for(i = 0;i < INDEXNUM;i++)
	{
		st_index[i].index_cus_num = CUSTOMNUM;//�ͻ�������ֵ 
		st_index[i].index_flag.index_chosedflag  = 0;//��ֵ 
		st_index[i].index_flag.index_usedflag    = 0;//��ֵ
		st_index[i].weight    = 0;//��ֵ
		st_index[i].single_fishscore    = 0;//��ֵ
		st_index[i].Xi   = 0;//��ֵ
		st_index[i].Xi0 = 0;
		st_index[i].Xi1 = 0;
		st_index[i].prenege_flag = prenege_flag_temp;//ÿһ��ָ������ָ�붼���Է��ʵ�prenege_flagָ��ָ����ڴ� 
		st_index[i].pcustom_score = pcustom_score_temp;//ÿһ��ָ������ָ�붼���Է��ʵ�pcustom_scoreָ��ָ����ڴ�
 	} 
 	Find_Renege_People(&renege,&no_renege);//���ΥԼ�ͷ�ΥԼ������  
}

/******************************************************
�������ܣ�  ����ά���л� b 
�������ƣ�
����˵����   
*******************************************************/  
/***************************
�������ܣ�    ��ԭʼ�ṹ������ݰ�����֯ 

*********************/
void Arrary_Change(INDEX_ATTRI_ST st_index[INDEXNUM],double arr[CUSTOMNUM][INDEXNUM])
{
	int i,j,k;

	for(i = 0;i < INDEXNUM;i++)
	{
		st_index[i].pindex_data =  (double *)malloc(CUSTOMNUM*sizeof(double)); //�����ڴ�ָ��
		for(j = 0;j < CUSTOMNUM;j++)
		{
			st_index[i].pindex_data[j] = arr[j][i]; 
		}		 
	}

} 
/*******************��ȡ��־λ���ǰ��ͻ���˳��***************************/
unsigned char * Renege_Flag(double arr[CUSTOMNUM][INDEXNUM]) 
{
	unsigned char * ptemp;
	int i;
	ptemp =  (unsigned char *)malloc(CUSTOMNUM*sizeof(unsigned char)); //�����ڴ�ָ��
	for(i = 0;i < CUSTOMNUM;i++)
	{
		if(arr[i][INDEXNUM-1] == 1)
		{
			ptemp[i] = 1; 
		}
		else
		{
			ptemp[i] = 0; 
		}
		//Sleep(100);//����鿴����д���Ƿ���ȷ ������̫�쿴���� 
		//printf("%d\t",ptemp[i]);
	}
	return ptemp;
 } 
 

 
 
/**************************
�������ܣ�  ���ΥԼ�ͷ�ΥԼ������ 
***************************/
void Find_Renege_People(int *prenege,int *pno_renege)
{
	int i,j,temprenege = 0,tempno_renege = 0;//һ��Ҫ����ֵ 

	for(i = 0;i < CUSTOMNUM;i++)
	{
		if(st_index[INDEXNUM-1].pindex_data[i] == 1)
			temprenege++;//ΥԼ 
			else
			tempno_renege++;//��ΥԼ  
	} 
	*prenege = temprenege;
	*pno_renege = tempno_renege;
    //printf("%d\t",renege); 
    //printf("%d\t",no_renege);
} 
/*******************���㵥��ָ���fishscoreֵ*******************/
double Alg_Calculate_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM])
{

	double Xij0 = 0;				//Xij0ָ��i��Ӧ�ĵ�j����ΥԼ�ͻ�����ֵ, 
	double Xih1 = 0;				//Xih1-ָ��i��Ӧ�ĵ�h��ΥԼ�ͻ�����ֵ, 
	double n0   = 0;				//n0 -��ΥԼ�ͻ�����,
	double n1   = 0;				//n1 -ΥԼ�ͻ�����	
	int  i,j,k,cnt = 0;
	double sum_Xi0 = 0,sum_Xi1 = 0;
	double Xi0_Xi_square = 0,Xi1_Xi_square = 0;
	double Sum_Xij0_Xi0_square = 0,Sum_Xih1_Xi1_square = 0;
	n0 = no_renege;//��ʼ������ΥԼ 
	n1 = renege;//��ʼ����ΥԼ 
	for(i = 0;i < INDEXNUM-1;i++)
	{
		for(j = 0;j < CUSTOMNUM;j++)
		{
			if(st_index[i].prenege_flag[j] == 0)
				sum_Xi0 += st_index[i].pindex_data[j];
			else
				sum_Xi1 += st_index[i].pindex_data[j];	
		}
		st_index[i].Xi0 = sum_Xi0/n0; //Xi0ָ��i��Ӧ�ķ�ΥԼ�ͻ�ָ����ֵ��ƽ��ֵ
		st_index[i].Xi1 = sum_Xi1/n1; //Xi1ָ��i��Ӧ��ΥԼ�ͻ�ָ����ֵ��ƽ��ֵ
		st_index[i].Xi = (sum_Xi0 + sum_Xi1)/(n0 + n1); //Xiָ��i��Ӧ�����пͻ���ֵ��ƽ��ֵ,
		Xi0_Xi_square = pow((st_index[i].Xi0 - st_index[i].Xi),2);//
		Xi1_Xi_square = pow((st_index[i].Xi1 - st_index[i].Xi),2);//

		for(j = 0;j < CUSTOMNUM;++j)
		{
			if(st_index[i].prenege_flag[j] == 0)
			{
				Sum_Xij0_Xi0_square += pow((st_index[i].pindex_data[j]-st_index[i].Xi0),2);//��ǰ��ΥԼ�ͻ��ĵ÷�-����ΥԼ�ͻ��÷־�ֵ�Ĳ��ƽ��֮�� 
			}
			else
			{
		    	Sum_Xih1_Xi1_square += pow((st_index[i].pindex_data[j]-st_index[i].Xi1),2);//��ǰΥԼ�ͻ��ĵ÷�-���з�ΥԼ�ͻ��÷־�ֵ�Ĳ��ƽ��֮�� 	
			}
		}
		if(Xi0_Xi_square != 0||Xi1_Xi_square != 0)//��32��ָ����������жϡ���������Ϊ0 
		{
		    st_index[i].single_fishscore = \
			( Xi0_Xi_square + Xi1_Xi_square ) / \
			( (Sum_Xij0_Xi0_square/n0) + (Sum_Xih1_Xi1_square/n1) );//���ÿ��ָ���FisherScoreֵ 
		}
		else
		{
			st_index[i].Xi = 0;
			st_index[i].Xi0 = 0;
			st_index[i].Xi1 = 0;
			st_index[i].single_fishscore = 0;
		}
		//printf("%.9lf\t%d\t\t",st_index[i].single_fishscore,cnt++);
		sum_of_sglfishscore += st_index[i].single_fishscore;//�������ָ��FisherScoreֵ�ĺ� 
		Sum_Xij0_Xi0_square = 0;
		Sum_Xih1_Xi1_square = 0;//���������һ��ָ��������ֵ 
		Xi0_Xi_square = 0;
		Xi1_Xi_square = 0;
	    sum_Xi0 = 0;//���������һָ��� 
	    sum_Xi1 = 0;//���������һָ���		
	} 
	return sum_of_sglfishscore;
} 

/**************************
�������� ��  ����÷ֵ�fishscoreֵ 

*************************************************/
double  Alg_Calculate_F_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM])
{
		double F_fishscore = 0;
		double S1;		//S(1)-ΥԼ�ͻ��÷־�ֵ��
		double S0;			//S(0)-��ΥԼ�ͻ��÷־�ֵ��
		double S;			//S-���пͻ��÷־�ֵ��
		double Si1;			//Si(1)-��i��ΥԼ�ͻ��ĵ÷֣�
		double Si0;			//S i(0)-��i����ΥԼ�ͻ��ĵ÷֣�
		double SumOfScore0 = 0,SumOfScore1 = 0;
		double SumOfSquareScore0 = 0,SumOfSquareScore1 = 0;
	    int n1;         	//n1-ΥԼ�ͻ�����
	    int n0;        	//n0-��ΥԼ�ͻ�����
		int i,j,k;
		n0 = no_renege;//��ʼ������ΥԼ 
		n1 = renege;//��ʼ����ΥԼ 
		for(i = 0;i < INDEXNUM-1;++i)
		{		
			st_index[i].weight = st_index[i].single_fishscore/sum_of_sglfishscore;
	    }
		for(j = 0;j < CUSTOMNUM;++j)
		{  
			for(i = 0;i < INDEXNUM-1;++i)//65��ָ�� 
			{
				st_index[i].pcustom_score[j] += st_index[i].weight*st_index[i].pindex_data[j];//Ȩ��*ָ�� ,��ǰ�ͻ��ĵ÷� 
				//printf("%f\t",RealCusData[i].Score);��ӡÿ���ͻ��ĵ÷� 
			}
			i = 0;//iֻҪС�����ָ�� ���� ����Ϊ++i֮��i = 66�ˣ��������������� 
			if(st_index[i].prenege_flag[j] == 0)
			{
				SumOfScore0 += st_index[i].pcustom_score[j];//��ΥԼ�ͻ��ĵ÷�֮�� 
			}
			else
			{
		    	SumOfScore1 += st_index[i].pcustom_score[j];//ΥԼ�ͻ��ĵ÷�֮�� 	
			}	
		
		}
		S0 =  SumOfScore0/n0;//��ΥԼ�ͻ��ĵ÷־�ֵ
		//printf("%f\t",SumOfScore0);
		S1 =  SumOfScore1/n1;//ΥԼ�ͻ��ĵ÷־�ֵ 
		//printf("%f\t",SumOfScore1);

		S = (SumOfScore1+SumOfScore0)/(n0+n1);//���пͻ��÷־�ֵ
		
		for(j = 0;j < CUSTOMNUM;++j)
		{
			if(st_index[i].prenege_flag[j] == 0)
			{
				SumOfSquareScore0 += pow((st_index[i].pcustom_score[j]-S0),2);//��ǰΥԼ�ͻ��ĵ÷�-����ΥԼ�ͻ��÷־�ֵ�Ĳ��ƽ��֮�� 
			}
			else
			{
		    	SumOfSquareScore1 += pow((st_index[i].pcustom_score[j]-S1),2);//��ǰ��ΥԼ�ͻ��ĵ÷�-���з�ΥԼ�ͻ��÷־�ֵ�Ĳ��ƽ��֮�� 	
			}
		}
		 
		F_fishscore = \
		( pow((S1-S),2) + pow((S0-S),2) )/( (SumOfSquareScore0/n0) + (SumOfSquareScore1/n1) );
		//printf("%f\t",F_fishscore);
	    //fprintf(fp2,"%g\n", F_fishscore);
		return F_fishscore;	
}
/************************************
�������ܣ�  ����ָ������ָ��ĵ÷ֵ�fishscore 
����˵������index_numָ����ָ����� 
***********************************/
double  Alg_Cal_x_F_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM],int index_num,char *psuffix_index)
{
		double F_fishscore = 0;
		double S1;		//S(1)-ΥԼ�ͻ��÷־�ֵ��
		double S0;			//S(0)-��ΥԼ�ͻ��÷־�ֵ��
		double S;			//S-���пͻ��÷־�ֵ��
		double Si1;			//Si(1)-��i��ΥԼ�ͻ��ĵ÷֣�
		double Si0;			//S i(0)-��i����ΥԼ�ͻ��ĵ÷֣�
		double SumOfScore0 = 0,SumOfScore1 = 0;
		double SumOfSquareScore0 = 0,SumOfSquareScore1 = 0;
		double tempsum_of_sglfishscore = 0;
	    int n1;         	//n1-ΥԼ�ͻ�����
	    int n0;        	//n0-��ΥԼ�ͻ�����
		int i,j,k;
		n0 = no_renege;//��ʼ������ΥԼ 
		n1 = renege;//��ʼ����ΥԼ 
		if(index_num>INDEXNUM)
			index_num = INDEXNUM-1;
		for(i = 0;i < index_num;++i)
		{	
			tempsum_of_sglfishscore += st_index[psuffix_index[i+1]].single_fishscore;
		}
		for(i = 0;i < index_num;++i)
		{		
			st_index[psuffix_index[i+1]].weight = st_index[psuffix_index[i+1]].single_fishscore/tempsum_of_sglfishscore;
	    }
	    //����
		for(j = 0;j < CUSTOMNUM;++j)
		{  
			for(i = 0;i < index_num;++i)//ָ���� index_num��ָ�� 
			{
				st_index[0].pcustom_score[j] = 0;//Ȩ��*ָ�� ,��ǰ�ͻ��ĵ÷� 
				//printf("%f\t",RealCusData[i].Score);��ӡÿ���ͻ��ĵ÷� 
			}
		}
		for(j = 0;j < CUSTOMNUM;++j)
		{  
			for(i = 0;i < index_num;++i)//ָ���� index_num��ָ�� 
			{
				st_index[0].pcustom_score[j] += st_index[psuffix_index[i+1]].weight*st_index[psuffix_index[i+1]].pindex_data[j];//Ȩ��*ָ�� ,��ǰ�ͻ��ĵ÷� 
				//printf("%f\t",RealCusData[i].Score);��ӡÿ���ͻ��ĵ÷� 
			}
			i = 0;//iֻҪС�����ָ�� ���� ����Ϊ++i֮��i = 66�ˣ��������������� 
			if(st_index[0].prenege_flag[j] == 0)
			{
				SumOfScore0 += st_index[0].pcustom_score[j];//��ΥԼ�ͻ��ĵ÷�֮�� 
			}
			else
			{
		    	SumOfScore1 += st_index[0].pcustom_score[j];//ΥԼ�ͻ��ĵ÷�֮�� 	
			}	
		
		}
		S0 =  SumOfScore0/n0;//��ΥԼ�ͻ��ĵ÷־�ֵ
		//printf("%f\t",SumOfScore0);
		S1 =  SumOfScore1/n1;//ΥԼ�ͻ��ĵ÷־�ֵ 
		//printf("%f\t",SumOfScore1);

		S = (SumOfScore1+SumOfScore0)/(n0+n1);//���пͻ��÷־�ֵ
		
		for(j = 0;j < CUSTOMNUM;++j)
		{
			if(st_index[0].prenege_flag[j] == 0)
			{
				SumOfSquareScore0 += pow((st_index[0].pcustom_score[j]-S0),2);//��ǰΥԼ�ͻ��ĵ÷�-����ΥԼ�ͻ��÷־�ֵ�Ĳ��ƽ��֮�� 
			}
			else
			{
		    	SumOfSquareScore1 += pow((st_index[0].pcustom_score[j]-S1),2);//��ǰ��ΥԼ�ͻ��ĵ÷�-���з�ΥԼ�ͻ��÷־�ֵ�Ĳ��ƽ��֮�� 	
			}
		}
		 
		F_fishscore = \
		( pow((S1-S),2) + pow((S0-S),2) )/( (SumOfSquareScore0/n0) + (SumOfSquareScore1/n1) );
		//printf("%f\t",F_fishscore);
	    //fprintf(fp2,"%g\n", F_fishscore);
		return F_fishscore;	
}

double  Alg_Cal_List_x_F_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM],int index_num,pindex_suffix pchosedindex_suffix)
{
		double F_fishscore = 0;
		double S1 = 0;		//S(1)-ΥԼ�ͻ��÷־�ֵ��
		double S0 = 0;			//S(0)-��ΥԼ�ͻ��÷־�ֵ��
		double S = 0;			//S-���пͻ��÷־�ֵ��
		double Si1 = 0;			//Si(1)-��i��ΥԼ�ͻ��ĵ÷֣�
		double Si0 = 0;			//S i(0)-��i����ΥԼ�ͻ��ĵ÷֣�
		double SumOfScore0 = 0,SumOfScore1 = 0;
		double SumOfSquareScore0 = 0,SumOfSquareScore1 = 0;
		double tempsum_of_sglfishscore = 0;
	    int n1;         	//n1-ΥԼ�ͻ�����
	    int n0;        	//n0-��ΥԼ�ͻ�����
		unsigned int i,j,k;
		char temp_suffix = 0;
		static unsigned int cnt = 0;
		n0 = no_renege;//��ʼ������ΥԼ 
		n1 = renege;//��ʼ����ΥԼ 
		pindex_suffix head = NULL,tail  = NULL;
		head = pchosedindex_suffix;
		tail = head;
		if(index_num>INDEXNUM)
			index_num = INDEXNUM-1;
		for(i = 0;i < index_num;++i)
		{	
			temp_suffix = List_Read(head,i+1);
			tempsum_of_sglfishscore += st_index[temp_suffix].single_fishscore;		
		}
		//printf("tempsum_of_sglfishscore:%.6lf\t%d\n",tempsum_of_sglfishscore,cnt++);
		for(i = 0;i < index_num;++i)
		{		
			temp_suffix = List_Read(head,i+1);
			st_index[temp_suffix].weight = st_index[temp_suffix].single_fishscore/tempsum_of_sglfishscore;
	    //	printf("�� %d\t��ָ���Ȩ�أ�%.9lf\n",i,st_index[temp_suffix].weight); 
		}
		//���� 
		for(j = 0;j < CUSTOMNUM;++j)
		{ 
			for(i = 0;i < index_num;++i)//ָ���� index_num��ָ�� 
			{
				    temp_suffix = List_Read(head,i+1);
					st_index[temp_suffix].pcustom_score[j] = 0;
			}
		}
		for(j = 0;j < CUSTOMNUM;++j)
		{  
			for(i = 0;i < index_num;++i)//ָ���� index_num��ָ�� 
			{
				temp_suffix = List_Read(head,i+1);
				//printf("%d\t",temp_suffix);
				st_index[temp_suffix].pcustom_score[j] += st_index[temp_suffix].weight*st_index[temp_suffix].pindex_data[j];//Ȩ��*ָ�� ,��ǰ�ͻ��ĵ÷� 
								
			}
		//	printf("�� %d���ͻ��ĵ÷֣�%.9lf\n",j,st_index[0].pcustom_score[j]);//��ӡÿ���ͻ��ĵ÷� 
			i = 0;//iֻҪС�����ָ�� ���� ����Ϊ++i֮��i = 66�ˣ��������������� 
			if(st_index[0].prenege_flag[j] == 0)
			{
				SumOfScore0 += st_index[0].pcustom_score[j];//��ΥԼ�ͻ��ĵ÷�֮�� 
			}
			else
			{
		    	SumOfScore1 += st_index[0].pcustom_score[j];//ΥԼ�ͻ��ĵ÷�֮�� 	
			}	
		
		}
		S0 =  SumOfScore0/n0;//��ΥԼ�ͻ��ĵ÷־�ֵ
		//printf("%f\t",SumOfScore0);
		S1 =  SumOfScore1/n1;//ΥԼ�ͻ��ĵ÷־�ֵ 
		//printf("%f\t",SumOfScore1);

		S = (SumOfScore1+SumOfScore0)/(n0+n1);//���пͻ��÷־�ֵ
		
		for(j = 0;j < CUSTOMNUM;++j)
		{
			if(st_index[0].prenege_flag[j] == 0)
			{
				SumOfSquareScore0 += pow((st_index[0].pcustom_score[j]-S0),2);//��ǰΥԼ�ͻ��ĵ÷�-����ΥԼ�ͻ��÷־�ֵ�Ĳ��ƽ��֮�� 
			}
			else
			{
		    	SumOfSquareScore1 += pow((st_index[0].pcustom_score[j]-S1),2);//��ǰ��ΥԼ�ͻ��ĵ÷�-���з�ΥԼ�ͻ��÷־�ֵ�Ĳ��ƽ��֮�� 	
			}
		}
		 
		F_fishscore = \
		( pow((S1-S),2) + pow((S0-S),2) )/( (SumOfSquareScore0/n0) + (SumOfSquareScore1/n1) );
		//printf("%f\t\n",F_fishscore);
	    //fprintf(fp2,"%g\n", F_fishscore);
		return F_fishscore;	
}


/***************************************************** 
�������ܣ�  ����ܸ������㹫ʽ 
�������ƣ�  
����˵���� 
  

******************************************************/
long long unsigned int C(unsigned int m,unsigned int n) 
{
	long long unsigned int temp = 1;
	unsigned int i;
//��֤n>=m-n
    if(n<m-n)
        return C(m,m-n);
    for(i=0;i<m-n;++i)
	{
        temp*=n+i+1;
        temp/=i+1;//�ڷ�ĸ��ʱ��Լ����Ӧ�ķ��� 
    }
    //printf("%lld\t",temp);
    return temp;
}


/***************************************************** 
�������ܣ�  ѡ��ָ����м���÷ֵ�Fishscore 
�������ƣ�  
����˵����  chosed_index_num   ѡ���ָ����� 
  

******************************************************/
double Alg_Calculate_Score(int chosed_index_num,INDEX_ATTRI_ST st_index[INDEXNUM])
{
	int i,j;
	long long unsigned int k;
	int k_max = 0;
	unsigned char * ptempsnglfishscore = NULL;//��ʱ�洢��ɸѡ��chosed_index_num��ָ����±�ֵ��
	double x_F_fishscore = 0,temp_x_F_fishscore = 0;
	double swap_suffix = 0;
	k_max = C(INDEXNUM-1,chosed_index_num);//����65��ָ�꣬ѡ��20����һ���ж�������� 
	ptempsnglfishscore = (unsigned char*)malloc(chosed_index_num*sizeof(unsigned char));//����ָ����ֽڴ洢ָ����±� 
	if(NULL == ptempsnglfishscore)
	{
		return;
	}
	else
	

	return 0;
}



/**************************************************** ****
�������ܣ� ȡ������������ѡ���������fishscore�����Ǹ����
���������� m�ܵ�ָ�������nѡ��ָ����� 
����ֵ��   ���ص�ǰȡ�����ָ��fishscoreֵ���±�����ָ�� 
*********************************************************/
 
pindex_suffix  Alg_Get_Combination(INDEX_ATTRI_ST st_index[INDEXNUM],unsigned char m, unsigned char n)
{
	int i,j,k;
	unsigned char *phead = NULL,*ptail = NULL;
	long long unsigned int count = 0,max_count = 0;
	unsigned char flag = 1;           // ��־�ҵ�һ����Ч���
	double chosed_index_Fishscore = 0,temp_chosed_index_Fishscore = 0;
	pindex_suffix st_order = NULL,head = NULL,tail = NULL;
	char suff_value = 0,temp = 0;
	char *order = (char *)malloc((n+1)*sizeof(char));
	n = n > m ? m : n;//��ֹ����� 
//	if(m-n>n)
//	{
//		n = m-n;
//	}
    max_count = C(m,n);
    printf("%lld\n",max_count);
	fprintf(fp2,"%lld\n",max_count);
    k = n;
	for(i = 0;i<=n;++i)
	   order[i]  = i-1;
	st_order = List_Creat((n+1));
	head  = st_order;
	tail = head;
  	
    //List_Print(head);
	if(NULL == st_order)
	{
		return;
	}            	
	 while(order[0] == -1)
	 {
		  if(flag)                   // �������Ҫ������
		  {     
                      			  
			   count++;
			   temp_chosed_index_Fishscore = Alg_Cal_x_F_Fishscore(st_index,n,order);  
			   if(chosed_index_Fishscore<temp_chosed_index_Fishscore&&fabs(chosed_index_Fishscore-temp_chosed_index_Fishscore)>ESP) 
               {
				    chosed_index_Fishscore = temp_chosed_index_Fishscore;//ѡ���ġ� 
				    for(i = 0;i <= n;++i)
				    {
				    	List_Write(st_order,order[i],i);//���������� 
					}
					List_Print(st_order);				    
			   }
			   else
			   printf("%lld\t",count);
			   //printf("%.9lf\t",chosed_index_Fishscore);
			   //printf("%d\n",count);
			   
			   flag = 0;
		  }
		  if(count == max_count) 
		    break;//��ʱorder��ֵ��û�к���ĳ������
		  order[k]++;
		  if(order[k] == m)          // ��ǰλ���������ֿ�ѡ������
		  {
		  	   order[k--] = 0;
			   continue;
		  }     		  
		  if(k < n)                  // ���µ�ǰλ�õ���һλ�õ�����          
		  {
			order[++k] = order[k-1];
		    continue;
		  }		  
		  if(k == n)
		   flag = 1;
	 }
     max_chosed_fishscore = chosed_index_Fishscore;
	 //printf("MAX:\t%.9lf\n",chosed_index_Fishscore);//��ӡ��ѡ������ָ��ĵ÷ֵ�fishscore�����ֵ 
	 //printf("%lld\n",count);
     free(order);
     //List_Print(order);
     return  st_order;//����ָ����������±������ָ�� 
}  


/********************************
�Ѿ�ѡ���            psuffix_index
*************************************************/
pindex_suffix  Alg_Generate_remained_index(pindex_suffix psuffix_index,unsigned char m,unsigned char n)
{
    pindex_suffix remained_index = NULL,ptempindex = NULL;
    ptempindex = psuffix_index;
    //List_Print(ptempindex);
	remained_index = List_Creat(m);//������m�±�ڵ�
	//List_Print(remained_index);
	remained_index = List_Delete(remained_index,ptempindex,n);//ɾ���Ѿ�ѡ����±��Ӧ��n���ڵ� ������ʣ��Ľڵ� 
	return remained_index;
}
/*********************************
�������ܣ�    ��üӱߵ��±�ֵ 
***********************************/ 
unsigned char Alg_Genrate_Rand_value(unsigned char m,unsigned char n)
{
	unsigned char rand_value = 0;
	srand((unsigned)time(NULL)); 
	rand_value = (rand() % (m-n)); //���������������������ڴ�ʣ���ָ���±���ѡ��һ�����мӱ߲��� 
	return rand_value;
} 
//unsigned char  Alg_Get_Add_index_suffix(pindex_suffix psuffix_remained_index)
//{
//	pindex_suffix ptempindex = NULL;
//	char rand_value = 0,chosed_remain_suffix = 0; 
//	//	for(i = 1;i <= n;++i)//ע������ط���i��1��ʼ�� 
//	//	{
//	//		printf("%d\t",ptempindex[i]);
//	//	}
//	ptempindex = psuffix_remained_index;
//
//    //printf("ԭʼ�����ֵ%d\t\n",rand_value);	
//    chosed_remain_suffix = Get_One_Reminder_Index_Suffix(ptempindex,rand_value);//ѡ��ʣ�µ�ָ����±�ֵ 
//    //printf("ѡȡ��ָ���±�ֵ%d\n",chosed_remain_suffix);
//	//List_Print(ptempindex);
//	return chosed_remain_suffix;
//}



char Get_One_Reminder_Index_Suffix(pindex_suffix index_head,char rand_val)
{
	pindex_suffix head = NULL,tail = NULL;
	unsigned char count = 0;
	head = index_head;
	tail = index_head;
	while(NULL != tail) 
	{
		if(count == rand_val)
			break;
		else
		{
			count++;
			head = tail;
			tail = tail->pnext;
		}
	}
	return tail->index;//���ض�Ӧ������±�ֵ 
}


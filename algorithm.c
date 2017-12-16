#include "algorithm.h"
#include "public.h"
#include "math.h"
#include "malloc.h"
#include "stdlib.h" 
#include "string.h" 
#include "time.h"
const double ESP = 1e-6; //
INDEX_ATTRI_ST  st_index[INDEXNUM] = {0};//定义指标数组 这里有66个指标 
int   renege = 0,no_renege = 0;//违约，非违约人数 
double sum_of_sglfishscore = 0;//所有指标的fishscore的和 
double max_chosed_fishscore = 0;
/******************************************************
函数功能：  初始化数据结构体
函数名称：
参数说明：   
*******************************************************/  
void Alg_Struct_Init(INDEX_ATTRI_ST st_index[INDEXNUM],double arr[CUSTOMNUM][INDEXNUM])
{
	int i,j;
	unsigned char *prenege_flag_temp = NULL;
	double *pcustom_score_temp = NULL;
 	 Arrary_Change(st_index,ori_arrdata);//数组到结构体 
  	 prenege_flag_temp = Renege_Flag(ori_arrdata);
  	 pcustom_score_temp = (double *)malloc(CUSTOMNUM*sizeof(double));//每个客户都有一个得分
	 memset(pcustom_score_temp,0,CUSTOMNUM*sizeof(double)); 
 	for(i = 0;i < INDEXNUM;i++)
	{
		st_index[i].index_cus_num = CUSTOMNUM;//客户数赋初值 
		st_index[i].index_flag.index_chosedflag  = 0;//初值 
		st_index[i].index_flag.index_usedflag    = 0;//初值
		st_index[i].weight    = 0;//初值
		st_index[i].single_fishscore    = 0;//初值
		st_index[i].Xi   = 0;//初值
		st_index[i].Xi0 = 0;
		st_index[i].Xi1 = 0;
		st_index[i].prenege_flag = prenege_flag_temp;//每一个指标的相关指针都可以访问到prenege_flag指针指向的内存 
		st_index[i].pcustom_score = pcustom_score_temp;//每一个指标的相关指针都可以访问到pcustom_score指针指向的内存
 	} 
 	Find_Renege_People(&renege,&no_renege);//求出违约和非违约的人数  
}

/******************************************************
函数功能：  数组维度切换 b 
函数名称：
参数说明：   
*******************************************************/  
/***************************
函数功能：    把原始结构体的数据按列组织 

*********************/
void Arrary_Change(INDEX_ATTRI_ST st_index[INDEXNUM],double arr[CUSTOMNUM][INDEXNUM])
{
	int i,j,k;

	for(i = 0;i < INDEXNUM;i++)
	{
		st_index[i].pindex_data =  (double *)malloc(CUSTOMNUM*sizeof(double)); //分配内存指针
		for(j = 0;j < CUSTOMNUM;j++)
		{
			st_index[i].pindex_data[j] = arr[j][i]; 
		}		 
	}

} 
/*******************提取标志位，是按客户的顺序***************************/
unsigned char * Renege_Flag(double arr[CUSTOMNUM][INDEXNUM]) 
{
	unsigned char * ptemp;
	int i;
	ptemp =  (unsigned char *)malloc(CUSTOMNUM*sizeof(unsigned char)); //分配内存指针
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
		//Sleep(100);//方便查看数据写入是否正确 ，否则太快看不清 
		//printf("%d\t",ptemp[i]);
	}
	return ptemp;
 } 
 

 
 
/**************************
函数功能：  求出违约和非违约的人数 
***************************/
void Find_Renege_People(int *prenege,int *pno_renege)
{
	int i,j,temprenege = 0,tempno_renege = 0;//一定要赋初值 

	for(i = 0;i < CUSTOMNUM;i++)
	{
		if(st_index[INDEXNUM-1].pindex_data[i] == 1)
			temprenege++;//违约 
			else
			tempno_renege++;//非违约  
	} 
	*prenege = temprenege;
	*pno_renege = tempno_renege;
    //printf("%d\t",renege); 
    //printf("%d\t",no_renege);
} 
/*******************计算单个指标的fishscore值*******************/
double Alg_Calculate_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM])
{

	double Xij0 = 0;				//Xij0指标i对应的第j个非违约客户的数值, 
	double Xih1 = 0;				//Xih1-指标i对应的第h个违约客户的数值, 
	double n0   = 0;				//n0 -非违约客户总数,
	double n1   = 0;				//n1 -违约客户总数	
	int  i,j,k,cnt = 0;
	double sum_Xi0 = 0,sum_Xi1 = 0;
	double Xi0_Xi_square = 0,Xi1_Xi_square = 0;
	double Sum_Xij0_Xi0_square = 0,Sum_Xih1_Xi1_square = 0;
	n0 = no_renege;//初始化，非违约 
	n1 = renege;//初始化，违约 
	for(i = 0;i < INDEXNUM-1;i++)
	{
		for(j = 0;j < CUSTOMNUM;j++)
		{
			if(st_index[i].prenege_flag[j] == 0)
				sum_Xi0 += st_index[i].pindex_data[j];
			else
				sum_Xi1 += st_index[i].pindex_data[j];	
		}
		st_index[i].Xi0 = sum_Xi0/n0; //Xi0指标i对应的非违约客户指标数值的平均值
		st_index[i].Xi1 = sum_Xi1/n1; //Xi1指标i对应的违约客户指标数值的平均值
		st_index[i].Xi = (sum_Xi0 + sum_Xi1)/(n0 + n1); //Xi指标i对应的所有客户数值的平均值,
		Xi0_Xi_square = pow((st_index[i].Xi0 - st_index[i].Xi),2);//
		Xi1_Xi_square = pow((st_index[i].Xi1 - st_index[i].Xi),2);//

		for(j = 0;j < CUSTOMNUM;++j)
		{
			if(st_index[i].prenege_flag[j] == 0)
			{
				Sum_Xij0_Xi0_square += pow((st_index[i].pindex_data[j]-st_index[i].Xi0),2);//当前非违约客户的得分-所有违约客户得分均值的差的平方之和 
			}
			else
			{
		    	Sum_Xih1_Xi1_square += pow((st_index[i].pindex_data[j]-st_index[i].Xi1),2);//当前违约客户的得分-所有非违约客户得分均值的差的平方之和 	
			}
		}
		if(Xi0_Xi_square != 0||Xi1_Xi_square != 0)//第32列指标的特殊性判断。除数不能为0 
		{
		    st_index[i].single_fishscore = \
			( Xi0_Xi_square + Xi1_Xi_square ) / \
			( (Sum_Xij0_Xi0_square/n0) + (Sum_Xih1_Xi1_square/n1) );//求出每个指标的FisherScore值 
		}
		else
		{
			st_index[i].Xi = 0;
			st_index[i].Xi0 = 0;
			st_index[i].Xi1 = 0;
			st_index[i].single_fishscore = 0;
		}
		//printf("%.9lf\t%d\t\t",st_index[i].single_fishscore,cnt++);
		sum_of_sglfishscore += st_index[i].single_fishscore;//求出所有指标FisherScore值的和 
		Sum_Xij0_Xi0_square = 0;
		Sum_Xih1_Xi1_square = 0;//清零计算下一个指标的相关数值 
		Xi0_Xi_square = 0;
		Xi1_Xi_square = 0;
	    sum_Xi0 = 0;//清零计算下一指标个 
	    sum_Xi1 = 0;//清零计算下一指标个		
	} 
	return sum_of_sglfishscore;
} 

/**************************
函数功能 ：  计算得分的fishscore值 

*************************************************/
double  Alg_Calculate_F_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM])
{
		double F_fishscore = 0;
		double S1;		//S(1)-违约客户得分均值；
		double S0;			//S(0)-非违约客户得分均值；
		double S;			//S-所有客户得分均值；
		double Si1;			//Si(1)-第i个违约客户的得分；
		double Si0;			//S i(0)-第i个非违约客户的得分；
		double SumOfScore0 = 0,SumOfScore1 = 0;
		double SumOfSquareScore0 = 0,SumOfSquareScore1 = 0;
	    int n1;         	//n1-违约客户数；
	    int n0;        	//n0-非违约客户数。
		int i,j,k;
		n0 = no_renege;//初始化，非违约 
		n1 = renege;//初始化，违约 
		for(i = 0;i < INDEXNUM-1;++i)
		{		
			st_index[i].weight = st_index[i].single_fishscore/sum_of_sglfishscore;
	    }
		for(j = 0;j < CUSTOMNUM;++j)
		{  
			for(i = 0;i < INDEXNUM-1;++i)//65个指标 
			{
				st_index[i].pcustom_score[j] += st_index[i].weight*st_index[i].pindex_data[j];//权重*指标 ,当前客户的得分 
				//printf("%f\t",RealCusData[i].Score);打印每个客户的得分 
			}
			i = 0;//i只要小于最大指标 就行 ，因为++i之后，i = 66了，索引不到，清零 
			if(st_index[i].prenege_flag[j] == 0)
			{
				SumOfScore0 += st_index[i].pcustom_score[j];//非违约客户的得分之和 
			}
			else
			{
		    	SumOfScore1 += st_index[i].pcustom_score[j];//违约客户的得分之和 	
			}	
		
		}
		S0 =  SumOfScore0/n0;//非违约客户的得分均值
		//printf("%f\t",SumOfScore0);
		S1 =  SumOfScore1/n1;//违约客户的得分均值 
		//printf("%f\t",SumOfScore1);

		S = (SumOfScore1+SumOfScore0)/(n0+n1);//所有客户得分均值
		
		for(j = 0;j < CUSTOMNUM;++j)
		{
			if(st_index[i].prenege_flag[j] == 0)
			{
				SumOfSquareScore0 += pow((st_index[i].pcustom_score[j]-S0),2);//当前违约客户的得分-所有违约客户得分均值的差的平方之和 
			}
			else
			{
		    	SumOfSquareScore1 += pow((st_index[i].pcustom_score[j]-S1),2);//当前非违约客户的得分-所有非违约客户得分均值的差的平方之和 	
			}
		}
		 
		F_fishscore = \
		( pow((S1-S),2) + pow((S0-S),2) )/( (SumOfSquareScore0/n0) + (SumOfSquareScore1/n1) );
		//printf("%f\t",F_fishscore);
	    //fprintf(fp2,"%g\n", F_fishscore);
		return F_fishscore;	
}
/************************************
函数功能：  计算指定个数指标的得分的fishscore 
参数说明：　index_num指定的指标个数 
***********************************/
double  Alg_Cal_x_F_Fishscore(INDEX_ATTRI_ST st_index[INDEXNUM],int index_num,char *psuffix_index)
{
		double F_fishscore = 0;
		double S1;		//S(1)-违约客户得分均值；
		double S0;			//S(0)-非违约客户得分均值；
		double S;			//S-所有客户得分均值；
		double Si1;			//Si(1)-第i个违约客户的得分；
		double Si0;			//S i(0)-第i个非违约客户的得分；
		double SumOfScore0 = 0,SumOfScore1 = 0;
		double SumOfSquareScore0 = 0,SumOfSquareScore1 = 0;
		double tempsum_of_sglfishscore = 0;
	    int n1;         	//n1-违约客户数；
	    int n0;        	//n0-非违约客户数。
		int i,j,k;
		n0 = no_renege;//初始化，非违约 
		n1 = renege;//初始化，违约 
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
	    //清零
		for(j = 0;j < CUSTOMNUM;++j)
		{  
			for(i = 0;i < index_num;++i)//指定的 index_num个指标 
			{
				st_index[0].pcustom_score[j] = 0;//权重*指标 ,当前客户的得分 
				//printf("%f\t",RealCusData[i].Score);打印每个客户的得分 
			}
		}
		for(j = 0;j < CUSTOMNUM;++j)
		{  
			for(i = 0;i < index_num;++i)//指定的 index_num个指标 
			{
				st_index[0].pcustom_score[j] += st_index[psuffix_index[i+1]].weight*st_index[psuffix_index[i+1]].pindex_data[j];//权重*指标 ,当前客户的得分 
				//printf("%f\t",RealCusData[i].Score);打印每个客户的得分 
			}
			i = 0;//i只要小于最大指标 就行 ，因为++i之后，i = 66了，索引不到，清零 
			if(st_index[0].prenege_flag[j] == 0)
			{
				SumOfScore0 += st_index[0].pcustom_score[j];//非违约客户的得分之和 
			}
			else
			{
		    	SumOfScore1 += st_index[0].pcustom_score[j];//违约客户的得分之和 	
			}	
		
		}
		S0 =  SumOfScore0/n0;//非违约客户的得分均值
		//printf("%f\t",SumOfScore0);
		S1 =  SumOfScore1/n1;//违约客户的得分均值 
		//printf("%f\t",SumOfScore1);

		S = (SumOfScore1+SumOfScore0)/(n0+n1);//所有客户得分均值
		
		for(j = 0;j < CUSTOMNUM;++j)
		{
			if(st_index[0].prenege_flag[j] == 0)
			{
				SumOfSquareScore0 += pow((st_index[0].pcustom_score[j]-S0),2);//当前违约客户的得分-所有违约客户得分均值的差的平方之和 
			}
			else
			{
		    	SumOfSquareScore1 += pow((st_index[0].pcustom_score[j]-S1),2);//当前非违约客户的得分-所有非违约客户得分均值的差的平方之和 	
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
		double S1 = 0;		//S(1)-违约客户得分均值；
		double S0 = 0;			//S(0)-非违约客户得分均值；
		double S = 0;			//S-所有客户得分均值；
		double Si1 = 0;			//Si(1)-第i个违约客户的得分；
		double Si0 = 0;			//S i(0)-第i个非违约客户的得分；
		double SumOfScore0 = 0,SumOfScore1 = 0;
		double SumOfSquareScore0 = 0,SumOfSquareScore1 = 0;
		double tempsum_of_sglfishscore = 0;
	    int n1;         	//n1-违约客户数；
	    int n0;        	//n0-非违约客户数。
		unsigned int i,j,k;
		char temp_suffix = 0;
		static unsigned int cnt = 0;
		n0 = no_renege;//初始化，非违约 
		n1 = renege;//初始化，违约 
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
	    //	printf("第 %d\t个指标的权重：%.9lf\n",i,st_index[temp_suffix].weight); 
		}
		//清零 
		for(j = 0;j < CUSTOMNUM;++j)
		{ 
			for(i = 0;i < index_num;++i)//指定的 index_num个指标 
			{
				    temp_suffix = List_Read(head,i+1);
					st_index[temp_suffix].pcustom_score[j] = 0;
			}
		}
		for(j = 0;j < CUSTOMNUM;++j)
		{  
			for(i = 0;i < index_num;++i)//指定的 index_num个指标 
			{
				temp_suffix = List_Read(head,i+1);
				//printf("%d\t",temp_suffix);
				st_index[temp_suffix].pcustom_score[j] += st_index[temp_suffix].weight*st_index[temp_suffix].pindex_data[j];//权重*指标 ,当前客户的得分 
								
			}
		//	printf("第 %d个客户的得分：%.9lf\n",j,st_index[0].pcustom_score[j]);//打印每个客户的得分 
			i = 0;//i只要小于最大指标 就行 ，因为++i之后，i = 66了，索引不到，清零 
			if(st_index[0].prenege_flag[j] == 0)
			{
				SumOfScore0 += st_index[0].pcustom_score[j];//非违约客户的得分之和 
			}
			else
			{
		    	SumOfScore1 += st_index[0].pcustom_score[j];//违约客户的得分之和 	
			}	
		
		}
		S0 =  SumOfScore0/n0;//非违约客户的得分均值
		//printf("%f\t",SumOfScore0);
		S1 =  SumOfScore1/n1;//违约客户的得分均值 
		//printf("%f\t",SumOfScore1);

		S = (SumOfScore1+SumOfScore0)/(n0+n1);//所有客户得分均值
		
		for(j = 0;j < CUSTOMNUM;++j)
		{
			if(st_index[0].prenege_flag[j] == 0)
			{
				SumOfSquareScore0 += pow((st_index[0].pcustom_score[j]-S0),2);//当前违约客户的得分-所有违约客户得分均值的差的平方之和 
			}
			else
			{
		    	SumOfSquareScore1 += pow((st_index[0].pcustom_score[j]-S1),2);//当前非违约客户的得分-所有非违约客户得分均值的差的平方之和 	
			}
		}
		 
		F_fishscore = \
		( pow((S1-S),2) + pow((S0-S),2) )/( (SumOfSquareScore0/n0) + (SumOfSquareScore1/n1) );
		//printf("%f\t\n",F_fishscore);
	    //fprintf(fp2,"%g\n", F_fishscore);
		return F_fishscore;	
}


/***************************************************** 
函数功能：  组合总个数计算公式 
函数名称：  
参数说明： 
  

******************************************************/
long long unsigned int C(unsigned int m,unsigned int n) 
{
	long long unsigned int temp = 1;
	unsigned int i;
//保证n>=m-n
    if(n<m-n)
        return C(m,m-n);
    for(i=0;i<m-n;++i)
	{
        temp*=n+i+1;
        temp/=i+1;//在分母乘时，约掉对应的分子 
    }
    //printf("%lld\t",temp);
    return temp;
}


/***************************************************** 
函数功能：  选择指标进行计算得分的Fishscore 
函数名称：  
参数说明：  chosed_index_num   选择的指标个数 
  

******************************************************/
double Alg_Calculate_Score(int chosed_index_num,INDEX_ATTRI_ST st_index[INDEXNUM])
{
	int i,j;
	long long unsigned int k;
	int k_max = 0;
	unsigned char * ptempsnglfishscore = NULL;//临时存储的筛选的chosed_index_num个指标的下标值。
	double x_F_fishscore = 0,temp_x_F_fishscore = 0;
	double swap_suffix = 0;
	k_max = C(INDEXNUM-1,chosed_index_num);//计算65个指标，选择20个，一共有多少种情况 
	ptempsnglfishscore = (unsigned char*)malloc(chosed_index_num*sizeof(unsigned char));//分配指标个字节存储指标的下标 
	if(NULL == ptempsnglfishscore)
	{
		return;
	}
	else
	

	return 0;
}



/**************************************************** ****
函数功能： 取组合数算出的所选个数的组合fishscore最大的那个组合
函数参数： m总的指标个数，n选的指标个数 
返回值：   返回当前取得最大指标fishscore值的下标数组指针 
*********************************************************/
 
pindex_suffix  Alg_Get_Combination(INDEX_ATTRI_ST st_index[INDEXNUM],unsigned char m, unsigned char n)
{
	int i,j,k;
	unsigned char *phead = NULL,*ptail = NULL;
	long long unsigned int count = 0,max_count = 0;
	unsigned char flag = 1;           // 标志找到一个有效组合
	double chosed_index_Fishscore = 0,temp_chosed_index_Fishscore = 0;
	pindex_suffix st_order = NULL,head = NULL,tail = NULL;
	char suff_value = 0,temp = 0;
	char *order = (char *)malloc((n+1)*sizeof(char));
	n = n > m ? m : n;//防止误操作 
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
		  if(flag)                   // 输出符合要求的组合
		  {     
                      			  
			   count++;
			   temp_chosed_index_Fishscore = Alg_Cal_x_F_Fishscore(st_index,n,order);  
			   if(chosed_index_Fishscore<temp_chosed_index_Fishscore&&fabs(chosed_index_Fishscore-temp_chosed_index_Fishscore)>ESP) 
               {
				    chosed_index_Fishscore = temp_chosed_index_Fishscore;//选最大的。 
				    for(i = 0;i <= n;++i)
				    {
				    	List_Write(st_order,order[i],i);//拷贝到链表 
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
		    break;//这时order的值才没有后面的程序被清空
		  order[k]++;
		  if(order[k] == m)          // 当前位置已无数字可选，回溯
		  {
		  	   order[k--] = 0;
			   continue;
		  }     		  
		  if(k < n)                  // 更新当前位置的下一位置的数字          
		  {
			order[++k] = order[k-1];
		    continue;
		  }		  
		  if(k == n)
		   flag = 1;
	 }
     max_chosed_fishscore = chosed_index_Fishscore;
	 //printf("MAX:\t%.9lf\n",chosed_index_Fishscore);//打印所选个数的指标的得分的fishscore的最大值 
	 //printf("%lld\n",count);
     free(order);
     //List_Print(order);
     return  st_order;//返回指标最大的组合下标数组的指针 
}  


/********************************
已经选择的            psuffix_index
*************************************************/
pindex_suffix  Alg_Generate_remained_index(pindex_suffix psuffix_index,unsigned char m,unsigned char n)
{
    pindex_suffix remained_index = NULL,ptempindex = NULL;
    ptempindex = psuffix_index;
    //List_Print(ptempindex);
	remained_index = List_Creat(m);//创建个m下标节点
	//List_Print(remained_index);
	remained_index = List_Delete(remained_index,ptempindex,n);//删除已经选择的下标对应的n个节点 ，返回剩余的节点 
	return remained_index;
}
/*********************************
函数功能：    获得加边的下标值 
***********************************/ 
unsigned char Alg_Genrate_Rand_value(unsigned char m,unsigned char n)
{
	unsigned char rand_value = 0;
	srand((unsigned)time(NULL)); 
	rand_value = (rand() % (m-n)); //产生随机数，该随机数用于从剩余的指标下标中选择一个进行加边操作 
	return rand_value;
} 
//unsigned char  Alg_Get_Add_index_suffix(pindex_suffix psuffix_remained_index)
//{
//	pindex_suffix ptempindex = NULL;
//	char rand_value = 0,chosed_remain_suffix = 0; 
//	//	for(i = 1;i <= n;++i)//注意这个地方，i从1开始的 
//	//	{
//	//		printf("%d\t",ptempindex[i]);
//	//	}
//	ptempindex = psuffix_remained_index;
//
//    //printf("原始的随机值%d\t\n",rand_value);	
//    chosed_remain_suffix = Get_One_Reminder_Index_Suffix(ptempindex,rand_value);//选择剩下的指标的下标值 
//    //printf("选取的指标下标值%d\n",chosed_remain_suffix);
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
	return tail->index;//返回对应的随机下标值 
}


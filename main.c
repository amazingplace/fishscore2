#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "public.h"

FILE *fp1  = NULL,*fp2 = NULL;//定义文件指针 

int main(void) 
{
	short int TEM;
	int i,j,k;
	int m,n;
	/**********************修改这两个值。m最大为65,指标个数，n是选择的指标数***********************************/
	//m = 20,n = 4;
	printf("请输入m:");
	scanf("%d",&m);
	printf("请输入n:");
	scanf("%d",&n);
	pindex_suffix chosed_index = NULL,remained_index = NULL;
	int temp_remain  = 0,temp_chose = 0,cnt = 0,cnt2=0; 
	int re_temp_m = 0,re_temp_n = 0; 
	unsigned char temp_get_index_suffix = 0,get_remain_index_suffix = 0;
	unsigned char temp_chose_index_suffix = 0,get_chose_index_suffix = 0; 
	double add_max_chosed_fishscore = 0.0,add_temp = 0.0,re_max_chosed_fishscore = 0.0,re_temp = 0.0;
	char temp_chose_value = 0,get_chose_value = 0,temp_remain_value = 0,get_remain_value = 0;
	Get_OriData(&fp1,&fp2);
    Text_To_Arry(fp1,ori_arrdata); //文本到数组  
    Alg_Struct_Init(st_index,ori_arrdata);//初始化指标 
    Alg_Calculate_Fishscore(st_index);//计算单个指标的fishscore 
    
	
    chosed_index = Alg_Get_Combination(st_index,m,n);//计算组合数，并计算所选组合数的指标 对应的得分的fishscore值 
    remained_index = Alg_Generate_remained_index(chosed_index,m,n);//求出剩余的指标
	List_Print(chosed_index);
	List_Print(remained_index);
		
	temp_remain = m-n;//剩余指标的个数维护 
	temp_chose = n;//已选指标的个数维护 
	for(i = 0;i < m-n;++i) //一直加，最大的可能性 
	{
		for(j = 0;j < temp_remain;++j)//第一次遍历所有剩余指标，找最大的		
		{
			
			temp_remain_value = List_Read(remained_index,j);//获取剩余指标随机值对应的指标下标
			temp_get_index_suffix = j; 
			//printf("%d\n",temp_get_index_suffix);
			#ifdef _PRINTF_
			printf("加边前的指标下标:"); 
			List_Print(chosed_index);
			#endif
		    List_Add(chosed_index,temp_remain_value);//在选择的指标基础上增加一个节点		    
		    #ifdef _PRINTF_
		    printf("加边后的指标下标:"); 
		    List_Print(chosed_index);
		    #endif	
			add_temp = Alg_Cal_List_x_F_Fishscore(st_index,temp_chose+1,chosed_index);//加边后的fishscore
			if(add_max_chosed_fishscore <  add_temp&& fabs(add_max_chosed_fishscore-add_temp) > ESP)
			{
				add_max_chosed_fishscore  = add_temp;//增加后变大
				get_remain_index_suffix =  temp_get_index_suffix;//保留这个可能是最大的剩余指标的下标 
				get_remain_value = temp_remain_value;
				/**************继续增加************************/
				//remained_index = List_Del(remained_index,rand_val);//剩余指标删除一个 
				#ifdef _PRINTF_
				List_Print(chosed_index);
				printf("加边后剩余的指标下标:"); 
				List_Print(remained_index);
				#endif
			}
			List_Del(chosed_index,temp_chose+1);//删除该节点， 在链表的尾部 
			//List_Print(chosed_index);
		}
		printf("第%d次加边前的最大值:%.6lf\n",cnt++,max_chosed_fishscore); 
		fprintf(fp2,"第%d次加边前的最大值:%.6lf\n",cnt,max_chosed_fishscore);
		if(max_chosed_fishscore<add_max_chosed_fishscore&&fabs(max_chosed_fishscore-add_max_chosed_fishscore) > ESP) 
		{
			max_chosed_fishscore = add_max_chosed_fishscore;
			printf("加边后变大的值%.9lf\n",add_max_chosed_fishscore);
			fprintf(fp2,"加边后变大的值%g\n", add_max_chosed_fishscore);
			List_Add(chosed_index,get_remain_value);//确定要加边的指标
			remained_index = List_Del(remained_index,get_remain_index_suffix); //剩余的指标减掉被减边的那个指标 
			temp_remain--;
			temp_chose++; 
		}
		else
		{
			break;
		}
	}
    List_Print(chosed_index);
    re_temp_n = temp_chose;
	for(i = 0;i < re_temp_n;++i)
	{
		for(j = 0;j < temp_chose;++j)
		{
		    temp_chose_value = List_Read(chosed_index,1);//把删除的值读出来，有可能不删 
		    temp_chose_index_suffix = temp_chose-j;//因为該值遍历后会被加到链表的末尾 
		    #ifdef _PRINTF_
		    printf("减边前的所选指标下标:"); 
		    List_Print(chosed_index);
		    #endif
		    chosed_index = List_Del(chosed_index,1);
		    #ifdef _PRINTF_
		    printf("减边后的所选指标下标:");  
		    List_Print(chosed_index);
		    #endif
		    re_temp = Alg_Cal_List_x_F_Fishscore(st_index,temp_chose-1,chosed_index);//减边后的fishscore
			
	        	
			if(re_max_chosed_fishscore < re_temp && fabs(re_max_chosed_fishscore-re_temp) > ESP)
			{		
				re_max_chosed_fishscore = re_temp;//减边后变大
				get_chose_value = temp_chose_value;//可能减边的指标下标
				get_chose_index_suffix = temp_chose_index_suffix;
			}
			List_Add(chosed_index,temp_chose_value);//把暂时减边的加回来 ，注意，加到末尾了	
		}
		printf("第%d次减边前的最大值:%.6lf\n",cnt2++,max_chosed_fishscore); 
		fprintf(fp2,"第%d次减边前的最大值:%.6lf\n",cnt2,max_chosed_fishscore);

		if(max_chosed_fishscore < re_max_chosed_fishscore && fabs(max_chosed_fishscore-re_max_chosed_fishscore) > ESP) 
		{
		    /***********减边后变大*************************/ 
		    printf("减边后变大的值%.6lf\n",re_max_chosed_fishscore);
		    fprintf(fp2,"减边后变大的值%.6lf\n", re_max_chosed_fishscore);
		    max_chosed_fishscore = re_max_chosed_fishscore;
			chosed_index = List_Del(chosed_index,get_chose_index_suffix);
			temp_chose--;
		}
		else
		{
			break;
		}
	} 	
	
	printf("停止的最大值:%.6lf\n",max_chosed_fishscore); 
	printf("最终选择指标下标:\n"); 
	fprintf(fp2,"停止的最大值:%.6lf\n",max_chosed_fishscore); 
	fprintf(fp2,"最终选择指标下标:\n"); 
	List_Print(chosed_index);
	free(chosed_index);
	free(remained_index);
	system("pause");
	return 0;   
}





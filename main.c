#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "public.h"

FILE *fp1  = NULL,*fp2 = NULL;//�����ļ�ָ�� 

int main(void) 
{
	short int TEM;
	int i,j,k;
	int m,n;
	/**********************�޸�������ֵ��m���Ϊ65,ָ�������n��ѡ���ָ����***********************************/
	//m = 20,n = 4;
	printf("������m:");
	scanf("%d",&m);
	printf("������n:");
	scanf("%d",&n);
	pindex_suffix chosed_index = NULL,remained_index = NULL;
	int temp_remain  = 0,temp_chose = 0,cnt = 0,cnt2=0; 
	int re_temp_m = 0,re_temp_n = 0; 
	unsigned char temp_get_index_suffix = 0,get_remain_index_suffix = 0;
	unsigned char temp_chose_index_suffix = 0,get_chose_index_suffix = 0; 
	double add_max_chosed_fishscore = 0.0,add_temp = 0.0,re_max_chosed_fishscore = 0.0,re_temp = 0.0;
	char temp_chose_value = 0,get_chose_value = 0,temp_remain_value = 0,get_remain_value = 0;
	Get_OriData(&fp1,&fp2);
    Text_To_Arry(fp1,ori_arrdata); //�ı�������  
    Alg_Struct_Init(st_index,ori_arrdata);//��ʼ��ָ�� 
    Alg_Calculate_Fishscore(st_index);//���㵥��ָ���fishscore 
    
	
    chosed_index = Alg_Get_Combination(st_index,m,n);//�������������������ѡ�������ָ�� ��Ӧ�ĵ÷ֵ�fishscoreֵ 
    remained_index = Alg_Generate_remained_index(chosed_index,m,n);//���ʣ���ָ��
	List_Print(chosed_index);
	List_Print(remained_index);
		
	temp_remain = m-n;//ʣ��ָ��ĸ���ά�� 
	temp_chose = n;//��ѡָ��ĸ���ά�� 
	for(i = 0;i < m-n;++i) //һֱ�ӣ����Ŀ����� 
	{
		for(j = 0;j < temp_remain;++j)//��һ�α�������ʣ��ָ�꣬������		
		{
			
			temp_remain_value = List_Read(remained_index,j);//��ȡʣ��ָ�����ֵ��Ӧ��ָ���±�
			temp_get_index_suffix = j; 
			//printf("%d\n",temp_get_index_suffix);
			#ifdef _PRINTF_
			printf("�ӱ�ǰ��ָ���±�:"); 
			List_Print(chosed_index);
			#endif
		    List_Add(chosed_index,temp_remain_value);//��ѡ���ָ�����������һ���ڵ�		    
		    #ifdef _PRINTF_
		    printf("�ӱߺ��ָ���±�:"); 
		    List_Print(chosed_index);
		    #endif	
			add_temp = Alg_Cal_List_x_F_Fishscore(st_index,temp_chose+1,chosed_index);//�ӱߺ��fishscore
			if(add_max_chosed_fishscore <  add_temp&& fabs(add_max_chosed_fishscore-add_temp) > ESP)
			{
				add_max_chosed_fishscore  = add_temp;//���Ӻ���
				get_remain_index_suffix =  temp_get_index_suffix;//�����������������ʣ��ָ����±� 
				get_remain_value = temp_remain_value;
				/**************��������************************/
				//remained_index = List_Del(remained_index,rand_val);//ʣ��ָ��ɾ��һ�� 
				#ifdef _PRINTF_
				List_Print(chosed_index);
				printf("�ӱߺ�ʣ���ָ���±�:"); 
				List_Print(remained_index);
				#endif
			}
			List_Del(chosed_index,temp_chose+1);//ɾ���ýڵ㣬 �������β�� 
			//List_Print(chosed_index);
		}
		printf("��%d�μӱ�ǰ�����ֵ:%.6lf\n",cnt++,max_chosed_fishscore); 
		fprintf(fp2,"��%d�μӱ�ǰ�����ֵ:%.6lf\n",cnt,max_chosed_fishscore);
		if(max_chosed_fishscore<add_max_chosed_fishscore&&fabs(max_chosed_fishscore-add_max_chosed_fishscore) > ESP) 
		{
			max_chosed_fishscore = add_max_chosed_fishscore;
			printf("�ӱߺ����ֵ%.9lf\n",add_max_chosed_fishscore);
			fprintf(fp2,"�ӱߺ����ֵ%g\n", add_max_chosed_fishscore);
			List_Add(chosed_index,get_remain_value);//ȷ��Ҫ�ӱߵ�ָ��
			remained_index = List_Del(remained_index,get_remain_index_suffix); //ʣ���ָ����������ߵ��Ǹ�ָ�� 
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
		    temp_chose_value = List_Read(chosed_index,1);//��ɾ����ֵ���������п��ܲ�ɾ 
		    temp_chose_index_suffix = temp_chose-j;//��Ϊԓֵ������ᱻ�ӵ������ĩβ 
		    #ifdef _PRINTF_
		    printf("����ǰ����ѡָ���±�:"); 
		    List_Print(chosed_index);
		    #endif
		    chosed_index = List_Del(chosed_index,1);
		    #ifdef _PRINTF_
		    printf("���ߺ����ѡָ���±�:");  
		    List_Print(chosed_index);
		    #endif
		    re_temp = Alg_Cal_List_x_F_Fishscore(st_index,temp_chose-1,chosed_index);//���ߺ��fishscore
			
	        	
			if(re_max_chosed_fishscore < re_temp && fabs(re_max_chosed_fishscore-re_temp) > ESP)
			{		
				re_max_chosed_fishscore = re_temp;//���ߺ���
				get_chose_value = temp_chose_value;//���ܼ��ߵ�ָ���±�
				get_chose_index_suffix = temp_chose_index_suffix;
			}
			List_Add(chosed_index,temp_chose_value);//����ʱ���ߵļӻ��� ��ע�⣬�ӵ�ĩβ��	
		}
		printf("��%d�μ���ǰ�����ֵ:%.6lf\n",cnt2++,max_chosed_fishscore); 
		fprintf(fp2,"��%d�μ���ǰ�����ֵ:%.6lf\n",cnt2,max_chosed_fishscore);

		if(max_chosed_fishscore < re_max_chosed_fishscore && fabs(max_chosed_fishscore-re_max_chosed_fishscore) > ESP) 
		{
		    /***********���ߺ���*************************/ 
		    printf("���ߺ����ֵ%.6lf\n",re_max_chosed_fishscore);
		    fprintf(fp2,"���ߺ����ֵ%.6lf\n", re_max_chosed_fishscore);
		    max_chosed_fishscore = re_max_chosed_fishscore;
			chosed_index = List_Del(chosed_index,get_chose_index_suffix);
			temp_chose--;
		}
		else
		{
			break;
		}
	} 	
	
	printf("ֹͣ�����ֵ:%.6lf\n",max_chosed_fishscore); 
	printf("����ѡ��ָ���±�:\n"); 
	fprintf(fp2,"ֹͣ�����ֵ:%.6lf\n",max_chosed_fishscore); 
	fprintf(fp2,"����ѡ��ָ���±�:\n"); 
	List_Print(chosed_index);
	free(chosed_index);
	free(remained_index);
	system("pause");
	return 0;   
}





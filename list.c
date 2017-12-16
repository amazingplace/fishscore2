#include "list.h"
#include "public.h"
#include "stdlib.h"

/***********************************************************
函数功能：   链表创建m个节点 
*************************************************************/
pindex_suffix List_Creat(unsigned char m)
{
	pindex_suffix pindexsuf = NULL,head = NULL,temp = NULL,test= NULL;//指向结构体的指针 
	int i;
	for(i = 0;i < m;++i)
	{
		
		if(i == 0)
		{
			pindexsuf = (pindex_suffix)malloc(sizeof(index_suffix));
			head = pindexsuf;
			temp = head;
			temp->index = i;
			temp->pnext = NULL;
		}
		else
		{
			pindexsuf = (pindex_suffix)malloc(sizeof(index_suffix));
			temp->pnext = pindexsuf;
			temp = pindexsuf;
			temp->index = i;
			temp->pnext = NULL;
		}		
	}

//	test = head;
//	while(NULL != test)
//	{
//		printf("%d\t",test->index);
//		test = test->pnext;
//	}
	return head; 
} 
/********************
函数说明：  增加一个节点内容
参数说明：  value,增加的节点 的值。 
***********************************/
pindex_suffix List_Add(pindex_suffix index_head,unsigned char value)
{
	pindex_suffix head = NULL,tail = NULL;
	head = index_head;
	tail = head;
	while(NULL != tail)
	{
		head = tail;
		tail = tail->pnext;
	}
	head->pnext = (pindex_suffix)malloc(sizeof(index_suffix));
    tail = head->pnext;
    tail->pnext = NULL;
	tail->index = value;
	return index_head;
}

pindex_suffix List_Del(pindex_suffix index_head,unsigned char value)
{
	pindex_suffix head = NULL,tail = NULL,temp = NULL;
	unsigned char cnt = 0;
	head = index_head;
	tail = head;
	while(NULL != tail)
	{
		if(cnt != value)
		{
			cnt++;
			head = tail;
			tail = tail->pnext;
		}
		else
		{
			if(cnt == 0)
			{
				temp = tail;
				if(NULL != tail->pnext)
				{
					tail = tail->pnext;
                    index_head = tail;
					break;				
				}
				else
				{
					index_head = NULL;
			    	break;
				}
				   
			}
			else
			{
				temp = tail;
				if(NULL != tail->pnext)
				{
					tail = tail->pnext;
					head->pnext = tail;
				}
				else
				{
					head->pnext = NULL;
				}				
				break;
			}

		}
	}
	free(temp);
	return index_head;
}


void List_Print(pindex_suffix index_head)
{
	pindex_suffix head = NULL,tail = NULL;
	if(NULL == index_head)
	{
		printf("空链表\n");
		return;
	}
	head = index_head;
	tail = head;
	printf("\n");
	fprintf(fp2,"\n");
	while(NULL != tail)
	{
		printf("%d\t",tail->index);
		fprintf(fp2,"%d\t",tail->index);
		tail = tail->pnext;
	}
	printf("\n");
	printf("\n");
	printf("\n");
	fprintf(fp2,"\n");
	fprintf(fp2,"\n");	
	fprintf(fp2,"\n");
}
/****************************
函数功能：   去除被选择的节点 
参数说明：    head   下标结构体头指针 
**************************************/

pindex_suffix List_Delete(pindex_suffix index_head,pindex_suffix psuffix,unsigned char n) 
{
	int i,j,k;
	pindex_suffix head = NULL,tail = NULL,swap = NULL,temp = NULL;
	head = index_head;
	tail = head->pnext;//tail指向head后一个节点 
	if(NULL == head)
	{
		return;
	}
	for(i = 0;i < n;++i)
	{
		while(NULL != tail)
		{
			if(head->index == List_Read(psuffix,i+1)) 
			{
				
				temp = head;
				head = tail;
				tail = tail->pnext;
				index_head = head;	
				free(temp);	
				break;			 
			}
			else if(tail->index == List_Read(psuffix,i+1))//
			{
				temp = tail;//记录要删除的节点指针
				if(NULL != tail->pnext) 
				{
					tail = tail->pnext;//
					head->pnext = tail;
					head = tail;
				}
				else
				{
					head->pnext = NULL;
				}

				free(temp);//删除节点 		 
				break;			
			}
			else
			{
				if(NULL != tail) 
				{
					head = tail;
					tail = tail->pnext;
				}
			}	
		}	

		head = index_head;//复位 
		tail = head->pnext;	
	}
/***************验证****************/
//	head = index_head;
//	while(NULL != head)
//	{
//		printf("%d\t",head->index);
//		head = head->pnext;
//	}
	return index_head;//返回删除后剩余的链表头指针 
	
}

/********************************** 
函数说明：　访问具体某个节点的数据 
**************************************************/
char List_Read(pindex_suffix index_head,unsigned char n)
{
	pindex_suffix head = NULL,tail = NULL;
	unsigned char cnt = 0;
	head = index_head;
	tail = index_head;
	while(NULL != tail) 
	{
		if(cnt != n)
		{
			cnt++;
			head = tail;
			tail = tail->pnext;
		}
		
		else
		{
			break;
		}
	}
	return tail->index;//返回对应的随机下标值 
}

/*****************

value:  写入的值，
n:       写入的位置 
**************/
char List_Write(pindex_suffix index_head,char value,unsigned char n)
{
	pindex_suffix head = NULL,tail = NULL;
	unsigned char cnt = 0;
	head = index_head;
	tail = index_head;
	while(NULL != tail) 
	{
		if(cnt != n)
		{
			cnt++;
			head = tail;
			tail = tail->pnext;
		}
		else
		{
			break;			
		}
	}
	if(value == -126)
	{
		tail->index +=1;
	}
	else
	tail->index = value;
	return tail->index;//返回对应的随机下标值 
}


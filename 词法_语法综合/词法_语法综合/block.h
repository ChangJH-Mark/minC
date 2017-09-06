#pragma once
#ifndef BLOCK_H
#define BLOCK_H
#include"CodeBlock.h"

struct Block {
	int block_type;
	int begin;  //´íÎóµÄbeginÊÇ-1£»
	int end;
	struct Block *left;
	struct Block *panduan;
	struct CodeBlock *right;
};
Block *inti_Bk(int, int, int, Block*, CodeBlock*,Block*);
Block *do_if(int,int);
Block *do_return(int, int);
Block *do_else(int, int);
Block *do_while(int, int);
Block *do_common(int, int);
Block * blockAnalyis(int begin, int end)
{
	Block *ans=NULL;
	if (begin > end)
	{
		printf("º¯Êý²»Âú\n");
		return NULL;
	}
	else if (begin == end)
		return NULL;
	else
	{
		switch (token[begin].type)
		{
		case IF: ans = do_if(begin, end); break;
		case ELSE: ans = do_else(begin, end); break;
		case WHILE: ans = do_while(begin, end); break;
		case RETURN: ans = do_return(begin, end); break;
		default: ans = do_common(begin, end); break;
		}
		if (ans != NULL)
			ans->left = blockAnalyis(ans->end + 1, end);
		return ans;
	}
}
Block *do_if(int a,int b)
{
	Block *an;
	int i,zuokuohao,youkuohao,flag=0;
	for (i = a+1; i <= b; i++)
	{
		if (token[i].type == L_BOUNDER)//{
		{
			if (flag == 0)
				zuokuohao = i;
			flag++;
		}
		else if (token[i].type == R_BOUNDER)//}
		{
			flag--;
			if (flag == 0)
			{
				youkuohao = i;
				break;
			}
			else if (flag < 0)
			{
				printf("IF Óï¾ä³ö´í\n");
				return NULL;
			}
		}
	}
	an = inti_Bk(IF, a, youkuohao, NULL, StartBuildCodeBlockTree(a,youkuohao), NULL);
	if (an != NULL)
	{
		an->panduan = blockAnalyis(a + 1, zuokuohao - 1);
		an->left = blockAnalyis(youkuohao + 1, b);
		if (an->panduan != NULL)
		{
			an->panduan->left = blockAnalyis(youkuohao + 1, b);
			an->panduan->right = NULL;
		}
		an->right = NULL;
		return an;
	}
	return an;
}
Block *do_common(int a, int b)
{
	Block *an;
	int i,finish;
	for (i = a + 1; i <= b; i++)
	{
		if (token[i].type==L_BOUNDER || token[i].type==SEMI)//{,;
		{
			finish = i;
			break;
		}
	}
	if (i > b)
	{
		printf("ÆÕÍ¨Óï¾ä³ö´í\n");
		return NULL;
	}
	an = inti_Bk(COMMON,a, finish,NULL,StartBuildCodeBlockTree(a,finish),NULL);
	an->left = blockAnalyis(finish + 1, b);
	return an;
}
//Block *do_return(int a, int b)
//{
//	Block *an;
//	int i, finish;
//	for (i = a + 1; i <= b; i++)
//	{
//		if (token[i].type == L_BOUNDER || token[i].type == SEMI)//{,;
//		{
//			finish = i;
//			break;
//		}
//	}
//	if (i > b)
//	{
//		printf("return Óï¾ä³ö´í\n");
//		return NULL;
//	}
//	an = inti_Bk(RETURN, a, finish,NULL,StartBuildCodeBlockTree(a,finish),NULL);
//	an->left = blockAnalyis(finish + 1, b);
//	return an;
//}
Block *do_while(int a, int b)
{
	Block *an;
	int i, zuokuohao, youkuohao, flag = 0;
	for (i = a + 1; i <= b; i++)
	{
		if (token[i].type == L_BOUNDER)//{
		{
			if (flag == 0)
				zuokuohao = i;
			flag++;
		}
		else if (token[i].type == R_BOUNDER)//}
		{
			flag--;
			if (flag == 0)
			{
				youkuohao = i;
				break;
			}
			else if (flag < 0)
			{
				printf("IF Óï¾ä³ö´í\n");
				return NULL;
			}
		}
	}
	an = inti_Bk(WHILE, a, youkuohao, NULL, StartBuildCodeBlockTree(a,youkuohao), NULL);
	an->panduan = blockAnalyis(a + 1, zuokuohao - 1);
	an->left = blockAnalyis(youkuohao + 1, b);
	if (an->panduan != NULL)
	{
		an->panduan->left = blockAnalyis(youkuohao + 1, b);
		an->panduan->right = NULL;
	}
	an->right = NULL;
	return an;
}
Block *do_else(int a, int b)
{
	int i, flag = 0;
	Block *an;
	int zuokuohao, youkuohao;
	for (i = a + 1; i <= b; i++)
	{
		if (token[i].type == L_BOUNDER)//{
		{
			if (flag == 0)
				zuokuohao = i;
			flag++;
		}
		else if (token[i].type == R_BOUNDER)//}
		{
			flag--;
			if (flag == 0)
			{
				youkuohao = i;
				break;
			}
			else
			{
				printf("else Óï¾ä³ö´í\n");
				return NULL;
			}
		}
	}
	an = inti_Bk(ELSE, a, youkuohao, NULL, StartBuildCodeBlockTree(a,youkuohao), NULL);
	an->left = blockAnalyis(youkuohao + 1, b);
	an->panduan = blockAnalyis(zuokuohao + 1, youkuohao - 1);
	an->right = NULL;
	return an;
}
Block *do_return(int a, int b)
{
	Block *an;
	int i, finish, flag = 0;
	for (i = a + 1; i <= b; i++)
	{
		if (token[i].type == SEMI)//;
		{
			finish = i;
			break;
		}
	}
	if (i > b)
	{
		printf("return Óï¾ä³ö´í\n");
		return NULL;
	}
	an = inti_Bk(RETURN, a, finish, NULL, StartBuildCodeBlockTree(a,finish), NULL);
	an->panduan = blockAnalyis(a + 1, finish);
	an->left = blockAnalyis(finish + 1, b);
	if (an->panduan != NULL)
	{
		an->panduan->left = blockAnalyis(finish + 1, b);
		an->panduan->right = NULL;
	}
	an->right = NULL;
	return an;
}
Block *inti_Bk(int type, int begin, int end, Block* left, CodeBlock* right, Block *panduan)
{
	Block *a;
	a = (Block*)malloc(sizeof(Block));
	a->block_type = type;
	a->begin = begin;
	a->end = end;
	a->left = left;
	a->right = right;
	a->panduan = panduan;
	return a;
}
#endif
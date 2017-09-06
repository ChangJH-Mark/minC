#pragma once
#ifndef  METHOD_H
#define METHOD_H
#include"block.h"
#include"lex.h"
#include<string>
struct FuncNode
{
	int func_type;
	string func_name;
	Node func_param[5];
	struct FuncNode *next_func;
	struct Block *block;
};
void inti_f(FuncNode**, int, string, vector<Node>, FuncNode*, int, int);
void printfunc(FuncNode*);
FuncNode* funcAnalyis(int head, int tail)
{
	FuncNode* a = NULL;
	int type;
	string name;
	vector<Node> param;
	Node b;
	int begin, end;//funcnode 内容 
	int i, flag = 0, index = 0;
	int state = 0;
	param.clear();
	for (i = head; i <= tail; i++)
	{
		if (token[i].type == L_BOUNDER)//"{"
		{
			flag++;
			if (flag == 1)
			{
				index = i;
				begin = i;
			}
		}
		if (token[i].type == R_BOUNDER)//"}"
		{
			flag--;
			if (flag == 0)
			{
				end = i;
				break;
			}
			else if (flag<0)
			{
				cout << "\"{\"之前出现\"}\"error" << endl;
				return NULL;
			}
		}
	}
	if (head >= tail || flag != 0 || index == head ||token[index-1].type!=R_BRA)//|| token[index - 1].type == R_BRA) //")"
	{
		cout << "函数不满" << endl;
		return NULL;
	}

	for (i = index - 2; i >= head; i--)
	{
		if (state == 4) //4是错误情况
			break;
		switch (state)
		{
		case 0: if (token[i].type==ID)//标识符
			state = 1;
				else if (token[i].type==COMMA)//","
					continue;
				else if (token[i].type==L_BRA)//"("
					state = 4;
				else
					state = 2;
			break;
		case 1: 
			if (token[i].type >= INT && token[i].type <= STRING)//"关键字"
			{
				b.str = token[i + 1].str;
				b.type = token[i].type;
				/*strcpy_s(b.token_name, token[i + 1].token_name);
				strcpy_s(b.token_type, token[i].token_name);*/
				b.line = token[i].line;
				param.push_back(b);
				state = 0;
			}
			else
				state = 2;
			break;
		case 2: printf("函数不满\n"); return NULL; break;
		}
	}
	if (i - 1 < head || token[i].type != ID || token[i - 1].type != INT && token[i - 1].type != REAL && token[i - 1].type != STRING &&token[i - 1].type != VOID )//标识符以及关键字
	{
		cout << "函数不满" << endl;
		return NULL;
	}
	//strcpy_s(type, token[i - 1].token_name);
	//strcpy_s(name, token[i].token_name);
	name = token[i].str;
	type = token[i - 1].type;
	inti_f(&a, type, name, param, NULL, begin, end);//begin是函数开始时的  {下标    }是函数结束的下标
	a->next_func = funcAnalyis(end + 1, tail);
	return a;
}
void inti_f(FuncNode** f, int type, string name, vector<Node> param, FuncNode* next, int begin, int end)
{
	int i=0;
	//(*f) = (FuncNode*)malloc(sizeof(FuncNode));
	(*f) = new FuncNode;
	(*f)->func_type = type;
	(*f)->func_name = name;
	for (i = 0; i < param.size(); i++)
		(*f)->func_param[i] = param[i];
	(*f)->func_param[i].line = 0;
	(*f)->next_func = next;
	if(name!="agoodmethod")
		(*f)->block = blockAnalyis(begin +1, end - 1);
}
void printfunc(FuncNode* a)
{
	int i = 0, num = 0;
	while (a != NULL)
	{
		printf("函数%d在第%d行开始:\n", ++num, (a->block)->begin);
		printf("函数%d类型：%s\t", num, a->func_type);
		printf("函数%d名称：%s\n", num, a->func_name);
		for (i = 0;i<a->func_param[i].line!=0; i++)
		{
				printf("形参 %d:\n", i + 1);
				printf("形参%d类型：%s\t", i + 1, a->func_param[i].type);
				printf("形参%d名称：%s\n", i + 1, a->func_param[i].str);
		}
		printf("函数%d在第%d行结束\n", num, (a->block)->end);
		a = a->next_func;
	}
}
#endif
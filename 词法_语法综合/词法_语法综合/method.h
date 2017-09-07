#pragma once
#ifndef  METHOD_H
#define METHOD_H
#include"block.h"
#include"lex.h"
#include<string>
struct FuncNode
{
	int func_type;          //函数返回值类型
	string func_name;      //函数名字
	Node func_param[5];     //函数参数，func_param[i].line=0表明  参数到这里终结，不包括i
	struct FuncNode *next_func;      //指向funcAnalyis分析出的 下一个函数
	struct Block *block;           //函数所包含的代码块
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
	int begin, end;//     存分析出的 函数内容
	int i, flag = 0, index = 0;     //flag用于记录{}出现的次数，“{”++1，“}”--1，  index记录第一次出现{ 的位置
	int state = 0;         // 描述扫描参数的状态
	param.clear();
	for (i = head; i <= tail; i++)    //在head,tail中找构成函数边界的  {   }
	{
		if (token[i].type == L_BOUNDER)//"{"
		{
			flag++;
			if (flag == 1)
			{
				index = i;
				begin = i;             //begin用于BLOCK分析的开始token 下标
			}
		}
		if (token[i].type == R_BOUNDER)//"}"
		{
			flag--;
			if (flag == 0)
			{
				end = i;             //end用于Block分析的结束下标
				break;
			}
			else if (flag<0)              //{ }没匹配
			{
				cout << "\"{\"之前出现\"}\"error" << endl;
				return NULL;
			}
		}
	}
	if (head >= tail || flag != 0 || index == head ||token[index-1].type!=R_BRA)//|| token[index - 1].type == R_BRA) //")"
	{  //{ } 不匹配，{ 的位置等于head , { 前边不是）都是函数不满的情况
		cout << "函数不满" << endl;
		return NULL;
	}

	for (i = index - 2; i >= head; i--)
	{
		if (state == 4) //4要退出循环
			break;
		switch (state)
		{
		case 0: if (token[i].type==ID)//标识符
			state = 1;           //已有标识符，还需一个变量类型才能组成一个参数
				else if (token[i].type==COMMA)//","
					continue;    // “，”表明还有参数
				else if (token[i].type==L_BRA)//"("
					state = 4;    //（ 出现表明不会再有参数
				else
					state = 2;
			break;
		case 1: 
			if (token[i].type >= INT && token[i].type <= STRING)//"关键字"
			{
				b.str = token[i + 1].str;       //参数b 名字和i+1相同，type 是 i 的type
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
	{   //由于循环，i是（ 前面一位，如果 i-1<head,i 不是标识符， i-1不是函数返回类型，都将造成函数结构不满
		cout << "函数不满" << endl;
		return NULL;
	}
	//strcpy_s(type, token[i - 1].token_name);
	//strcpy_s(name, token[i].token_name);
	name = token[i].str;
	type = token[i - 1].type;
	inti_f(&a, type, name, param, NULL, begin, end);//begin是函数开始时的  { 下标    } 是函数结束的下标     a中存入刚分析出的函数
	a->next_func = funcAnalyis(end + 1, tail);   //接着分析 a 之后的函数
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
	if(name!="agoodmethod")         //抽象树的根节点叫 “agoodmethod”  根节点不需要分析代码块
		(*f)->block = blockAnalyis(begin +1, end - 1);
}
void printfunc(FuncNode* a)     //打印生成的函数树
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
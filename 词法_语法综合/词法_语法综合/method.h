#pragma once
#ifndef  METHOD_H
#define METHOD_H
#include"block.h"
#include"lex.h"
#include<string>
struct FuncNode
{
	int func_type;          //��������ֵ����
	string func_name;      //��������
	Node func_param[5];     //����������func_param[i].line=0����  �����������սᣬ������i
	struct FuncNode *next_func;      //ָ��funcAnalyis�������� ��һ������
	struct Block *block;           //�����������Ĵ����
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
	int begin, end;//     ��������� ��������
	int i, flag = 0, index = 0;     //flag���ڼ�¼{}���ֵĴ�������{��++1����}��--1��  index��¼��һ�γ���{ ��λ��
	int state = 0;         // ����ɨ�������״̬
	param.clear();
	for (i = head; i <= tail; i++)    //��head,tail���ҹ��ɺ����߽��  {   }
	{
		if (token[i].type == L_BOUNDER)//"{"
		{
			flag++;
			if (flag == 1)
			{
				index = i;
				begin = i;             //begin����BLOCK�����Ŀ�ʼtoken �±�
			}
		}
		if (token[i].type == R_BOUNDER)//"}"
		{
			flag--;
			if (flag == 0)
			{
				end = i;             //end����Block�����Ľ����±�
				break;
			}
			else if (flag<0)              //{ }ûƥ��
			{
				cout << "\"{\"֮ǰ����\"}\"error" << endl;
				return NULL;
			}
		}
	}
	if (head >= tail || flag != 0 || index == head ||token[index-1].type!=R_BRA)//|| token[index - 1].type == R_BRA) //")"
	{  //{ } ��ƥ�䣬{ ��λ�õ���head , { ǰ�߲��ǣ����Ǻ������������
		cout << "��������" << endl;
		return NULL;
	}

	for (i = index - 2; i >= head; i--)
	{
		if (state == 4) //4Ҫ�˳�ѭ��
			break;
		switch (state)
		{
		case 0: if (token[i].type==ID)//��ʶ��
			state = 1;           //���б�ʶ��������һ���������Ͳ������һ������
				else if (token[i].type==COMMA)//","
					continue;    // �������������в���
				else if (token[i].type==L_BRA)//"("
					state = 4;    //�� ���ֱ����������в���
				else
					state = 2;
			break;
		case 1: 
			if (token[i].type >= INT && token[i].type <= STRING)//"�ؼ���"
			{
				b.str = token[i + 1].str;       //����b ���ֺ�i+1��ͬ��type �� i ��type
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
		case 2: printf("��������\n"); return NULL; break;
		}
	}
	if (i - 1 < head || token[i].type != ID || token[i - 1].type != INT && token[i - 1].type != REAL && token[i - 1].type != STRING &&token[i - 1].type != VOID )//��ʶ���Լ��ؼ���
	{   //����ѭ����i�ǣ� ǰ��һλ����� i-1<head,i ���Ǳ�ʶ���� i-1���Ǻ����������ͣ�������ɺ����ṹ����
		cout << "��������" << endl;
		return NULL;
	}
	//strcpy_s(type, token[i - 1].token_name);
	//strcpy_s(name, token[i].token_name);
	name = token[i].str;
	type = token[i - 1].type;
	inti_f(&a, type, name, param, NULL, begin, end);//begin�Ǻ�����ʼʱ��  { �±�    } �Ǻ����������±�     a�д���շ������ĺ���
	a->next_func = funcAnalyis(end + 1, tail);   //���ŷ��� a ֮��ĺ���
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
	if(name!="agoodmethod")         //�������ĸ��ڵ�� ��agoodmethod��  ���ڵ㲻��Ҫ���������
		(*f)->block = blockAnalyis(begin +1, end - 1);
}
void printfunc(FuncNode* a)     //��ӡ���ɵĺ�����
{
	int i = 0, num = 0;
	while (a != NULL)
	{
		printf("����%d�ڵ�%d�п�ʼ:\n", ++num, (a->block)->begin);
		printf("����%d���ͣ�%s\t", num, a->func_type);
		printf("����%d���ƣ�%s\n", num, a->func_name);
		for (i = 0;i<a->func_param[i].line!=0; i++)
		{
				printf("�β� %d:\n", i + 1);
				printf("�β�%d���ͣ�%s\t", i + 1, a->func_param[i].type);
				printf("�β�%d���ƣ�%s\n", i + 1, a->func_param[i].str);
		}
		printf("����%d�ڵ�%d�н���\n", num, (a->block)->end);
		a = a->next_func;
	}
}
#endif
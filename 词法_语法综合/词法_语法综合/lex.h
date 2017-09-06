#ifndef _LEX_H_
#define _LEX_H_
#include"define.h"
#include<iostream>
#include<stdio.h>
#include<string.h>
#include<string>
#include<vector>
using namespace std;

struct Node
{
	int type;//����
	string str;//��ԭ��
	int line;//�к�
};

typedef struct Node Node;
extern vector<Node>token;

static char keyword[10][7] = { "int","real","string","while","if","else","out","in","void","return" };

class lex
{
public:
	lex();
	~lex();

	void scanline();//����ɨ
	void clear(const char str[]);//���ע�ͺ��Ʊ��
	void tokenlist(int type);//����token��

	friend int wordkind(const char c);//�ж��ַ�����
	friend int stringkind(const char str[]);//�ж��Ƿ��ǹؼ���
	friend int letter(const char c);//�ж��Ƿ�����ĸ
	friend int number(const char c);//�ж��Ƿ�������
	friend int symbol(const char c);//�ж��Ƿ��Ƿ���Ҫ��ķ���

private:
	FILE *file;
	int countline;//��¼�к�
	int bufnum;
	int state;
	char bufin[256];
	char bufout[100];
};

#endif
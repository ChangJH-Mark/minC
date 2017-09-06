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
	int type;//代号
	string str;//串原型
	int line;//行号
};

typedef struct Node Node;
extern vector<Node>token;

static char keyword[10][7] = { "int","real","string","while","if","else","out","in","void","return" };

class lex
{
public:
	lex();
	~lex();

	void scanline();//按行扫
	void clear(const char str[]);//清楚注释和制表符
	void tokenlist(int type);//建立token流

	friend int wordkind(const char c);//判断字符类型
	friend int stringkind(const char str[]);//判断是否是关键字
	friend int letter(const char c);//判断是否是字母
	friend int number(const char c);//判断是否是数字
	friend int symbol(const char c);//判断是否是符合要求的符号

private:
	FILE *file;
	int countline;//记录行号
	int bufnum;
	int state;
	char bufin[256];
	char bufout[100];
};

#endif
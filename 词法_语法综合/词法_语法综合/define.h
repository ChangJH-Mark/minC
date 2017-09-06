#pragma once
#ifndef _DEFINE_H_
#define _DEFINE_H_
enum Myenum
{
	INT,//int
	REAL,//real
	STRING,//string
	WHILE,//while，或while语句
	IF,//if，或if语句
	ELSE,//else，或else语句
	OUT,//out
	IN,//in
	VOID,//void
	RETURN,//return，或return语句
	ADD,//'+'
	SUB,//'-'
	MUL,//'*'
	DIV,//'/'
	MOD,//'%'
	ASG,//'='
	DOLLAR,//'$'
	JING,//'#'
	GRT_THAN,//'>'
	LES_THAN,//'<'
	NOT,//'!'
	GRT_EQUAL,//'>='
	LES_EQUAL,//'<='
	NOT_EQUAL,//'<>'
	EQUAL,//'=='
	AND,//'&&'
	OR,//'||'
	COMMA,//','
	POINTER,//'.'
	L_BRA,//'('
	R_BRA,//')'
	L_INDEX,//'['
	R_INDEX,//']'
	L_BOUNDER,//'{'
	R_BOUNDER,//'}'
	SEMI,//';'
	ID,//标识符
	INT_VAL,//int常量
	REAL_VAL,//real常量
	STRING_VAL,//字符串
	COMMON,//普通语句
	JUDGEMENT//判断语句
};
#endif // !_DEFINE_H_

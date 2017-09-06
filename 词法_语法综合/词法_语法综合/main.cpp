#include"lex.h"
#include"block.h"
#include"method.h"
#include"CodeBlock.h"
int main()
{
	lex lex;
	lex.scanline();
	for (int i = 0; i < token.size(); i++)
		cout << "[ " << token[i].str << " ]" << " --- [ " << token[i].type << " ]" << "ÐÐºÅ" << token[i].line << endl;
	

	system("pause");
}
//C:\Users\93446\Desktop\shenmin.txt
#include"lex.h"
#include"block.h"
#include"method.h"
#include"CodeBlock.h"
int main()
{
	FuncNode *head;
	lex lex;
	lex.scanline();
	for (int i = 0; i < token.size(); i++)
		cout << "[ " << token[i].str << " ]" << " --- [ " << token[i].type << " ]" << "�к�" << token[i].line << endl;
	vector<Node>param;
	param.clear();
	printf("�����Ǻ����ķ���\n");
	//system("pause");
	string a = "agoodmethod";
	inti_f(&head,INT,a, param, NULL, 0, token.size()-1);
	head->next_func = funcAnalyis(0, token.size() - 1);
	printfunc(head->next_func);
	system("pause");
		/*char path[50];
		scanf_s("%s", path, 50);
		Lex *lex = new Lex(path);
		boolExpr *a;
		printf("�����ǶԲ���ʽ����˳��ķ�����\n");
		a = boolAnalyis(0, token_num - 1);
		printBoolTree(a);
	/*FuncNode *head;
	char path[50];
	vector<node>param;
	param.clear();
	while (scanf_s("%s", path, 50) != EOF)
	{
		Lex *lex = new Lex(path);
		printf("�����Ǻ����ķ���\n");
		inti_f(&head, "head", "shit", param, NULL, 1, token[token_num - 1].line);
		head->next_func = funcAnalyis(0, token_num - 1);
		printfunc(head->next_func);
	}
	char path[50];
	scanf_s("%s", path, 50);
	Lex *lex = new Lex(path);
	boolExpr *a;
	printf("�����ǶԲ���ʽ����˳��ķ�����\n");
	a = boolAnalyis(0, token_num - 1);
	printBoolTree(a);*/
}
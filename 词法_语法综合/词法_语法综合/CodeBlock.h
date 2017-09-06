#pragma once
#ifndef CodeBlock_H
#define CodeBlock_H
#include<stdlib.h>

typedef struct CodeBlock {
	CodeBlock *rightChild;
	CodeBlock *leftChild;
	int i;

}CODEBLOCK,CodeBlock;

bool isNeededDeleteBracket(int start, int end)
{
	int flag = 1;
	for (int i = start + 1; i <= end; i++)
	{
		if (token[i].type == L_BRA)
		{
			flag++;
		}
		else if (token[i].type == R_BRA)
		{
			flag--;
			if (flag == 0)
			{
				if (i == end)//��ʼ����������������ƥ��
					return true;
				else
				{
					return false;
				}
			}
		}
	}
	return false;
}

int GetTokenPriority(int type)
{
	switch (type)
	{
	case COMMA:
		return -1;
		break;

	case AND:
		return 0;
		break;
	case OR:
		return 0;
		break;

	case ASG:
		return 1;
		break;
	case EQUAL:
		return 1;
		break;
	case GRT_EQUAL:
		return 1;
		break;
	case LES_EQUAL:
		return 1;
		break;
	case NOT_EQUAL:
		return 1;
		break;
	case GRT_THAN:
		return 1;
		break;
	case LES_THAN:
		return 1;
		break;

	case ADD:
		return 2;
		break;
	case SUB:
		return 2;
		break;

	case MUL:
		return 3;
		break;
	case DIV:
		return 3;
		break;
	case MOD:
		return 3;
		break;
	case DOLLAR:
		return 3;
		break;

	case JING:
		return 4;
		break;

	case ID:
		return 5;
		break;
	case INT_VAL:
		return 5;
		break;
	case REAL_VAL:
		return 5;
		break;
	case STRING_VAL:
		return 5;
		break;

	case INT:
		return 6;
		break;
	case REAL:
		return 6;
		break;
	case STRING:
		return 6;
	case IN:
		return 6;
		break;
	case OUT:
		return 6;
		break;
	case NOT:
		return 6;
		break;
	default:
		cout << "Unidentified Token! " + type << endl;
		return -1;
	}
}

void BuildCodeBlockTree(CodeBlock *headNode,int start,int end)
{
	if (token[end].type == SEMI)
		end--;
	//�ȴ������ҵ����ȼ���͵���Ϊͷ��㣬Ȼ��ݹ�
	if (token[start].type == L_BRA)
	{
		//����������ǣ�a+b����������Ҫ������ȥ��
		if (isNeededDeleteBracket(start,end))
		{
			start++;
			end--;
		}
	}

	int min = 99;
	int position = -1;
	for (int i = start; i <= end; i++) // ( 24,)25
	{
		//������Ҫ����������Ŵ��ڣ���������Ķ������ȼ���ߣ�Ȼ������ȥ��
		if (token[i].type == L_BRA)
		{
			//�ҵ�(��
			int flag = 1;
			for (int j = i + 1; j <= end; j++)
			{
				if (token[j].type == L_BRA)
					flag++;

				//������Ҫ�ҵ�)Ȼ��ֱ��������һ�ε�����
				if (token[j].type == R_BRA)
				{
					flag--;
					if (flag == 0)
					{
						//�ҵ�)��
						i = j + 1;
						break;
					}
				}
			}
			//���ǵ� a = (a+b) * (c+d)���������������֮���
			if (i > end)
				break;
		}

		if (GetTokenPriority(token[i].type) < min)
		{
			min = GetTokenPriority(token[i].type);
			position = i;
		}
	}

	headNode->i = position;

	int priority = GetTokenPriority(token[position].type);

	if (priority >= -1 && priority <= 4)
	{
		if (start >= position || end <= position)
		{
			cout << "Synax Error : " + token[position].str;
			cout << " Line:";
			cout << token[position].line << endl;
			return;
		}
	}


	if (start < position)
	{
		//ִ����һ���ݹ����
		CodeBlock *newLChildNode;
		newLChildNode = (CodeBlock *)malloc(sizeof(CodeBlock));
		newLChildNode->leftChild = NULL;
		newLChildNode->rightChild = NULL;
		headNode->leftChild = newLChildNode;
		BuildCodeBlockTree(newLChildNode, start, position - 1);
	}


	if (end > position)
	{
		CodeBlock *newRChildNode;
		newRChildNode = (CodeBlock *)malloc(sizeof(CodeBlock));
		newRChildNode->leftChild = NULL;
		newRChildNode->rightChild = NULL;
		headNode->rightChild = newRChildNode;
		BuildCodeBlockTree(newRChildNode, position + 1, end);
		//ִ����һ���ݹ����
	}
}

CodeBlock* StartBuildCodeBlockTree(int start, int end)
{
	CodeBlock *root;
	root = (CodeBlock *)malloc(sizeof(CodeBlock));
	root->leftChild = NULL;
	root->rightChild = NULL;

	BuildCodeBlockTree(root, start,end);
	return root;
}

int FindNextSentence()
{
	for (int i = 0; i < token.size(); i++)
	{
		if (token[i].type == SEMI)
		{
			return i;
			break;
		}
	}

	return -1;
}

//void postrav(CodeBlock *bt)
//{
//	if (bt != NULL) {
//		postrav(bt->leftChild);
//		postrav(bt->rightChild);
//		cout << token[bt->i].str << endl;
//	}
//}
//
//void qian(CodeBlock *bt)
//{
//	if (bt != NULL)
//	{
//		cout << token[bt->i].str << endl;
//		postrav(bt->leftChild);
//		postrav(bt->rightChild);
//	}
//}
//
//void zhong(CodeBlock *bt)
//{
//	if (bt != NULL)
//	{
//		postrav(bt->leftChild);
//		cout << token[bt->i].str << endl;
//		postrav(bt->rightChild);
//	}
//}
//
//
//int main()
//{
//	//token[0].type = INT; token[0].str = "int"; token[0].line = 1;
//	//token[1].type = ID; token[1].str = "a"; token[1].line = 1;
//	//token[2].type = ASG; token[2].str = "="; token[2].line = 1;
//	//token[3].type = ID; token[3].str = "b"; token[3].line = 1;
//	//token[4].type = ADD; token[4].str = "+"; token[4].line = 1;
//	//token[5].type = INT_VAL; token[5].str = "3"; token[5].line = 1;
//	//token[6].type = SEMI; token[6].str = ";"; token[6].line = 1;
//	//D:\5.txt
//
//	lex lex;
//	lex.scanline();
//	for (int i = 0; i < token.size(); i++)
//		cout << "[ " << token[i].str << " ]" << " --- [ " << token[i].type << " ]" << "�к�" << token[i].line << endl;
//	
//	system("pause");
//	
//
//	CodeBlock* root = StartBuildCodeBlockTree(0, FindNextSentence());
//	qian(root);
//	cout << "" << endl;
//	zhong(root);
//	cout << "" << endl;
//	postrav(root);
//	system("pause");
//}
#endif
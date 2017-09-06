#include"lex.h"

bool InOutCheck(int start,int end)
{
	if (token[end].type == SEMI)
		end--;
	if (token[start].type == IN)
	{
		int flag = start + 1;
		if (token[flag].type == ID)
		{
			if (flag == end)
				return true;
			else
			{
				cout << "Synax Error: There should be ; after  " + token[flag].str;
				cout << ". Line:";
				cout << token[flag].line << endl;
				return false;
			}
		}

		else if (token[flag].type == STRING_VAL)
		{
			flag++;
			if (token[flag].type == COMMA)
			{
				flag++;
				if (token[flag].type == ID)
				{
					if (flag == end)
					{
						return true;
					}

					else
					{
						cout << "Synax Error: There should be ; after  " + token[flag].str;
						cout << ". Line:";
						cout << token[flag].line << endl;
						return false;
					}
				}

				else
				{
					flag--;
					cout << "Synax Error: There should be id after  " + token[flag].str;
					cout << ". Line:";
					cout << token[flag].line << endl;
					return false;
				}
			}

			else
			{
				flag--;
				cout << "Synax Error: There should be , after  " + token[flag].str;
				cout << ". Line:";
				cout << token[flag].line << endl;
				return false;
			}
		}

		else
		{
			flag--;
			cout << "Synax Error: There should be string or id after in ";
			cout << ". Line:";
			cout << token[flag].line << endl;
			return false;
		}
	}

	else if(token[start].type == OUT)
	{
		int flag = start + 1;
		if (token[flag].type == STRING_VAL)
		{
			if (flag == end)
				return true;
			
			flag++;
			if(token[flag].type == COMMA)
			{
				flag++;
				if (token[flag].type == ID)
				{
					if (flag == end)
						return true;
					else
					{
						cout << "Synax Error: There should be ; after " + token[flag].str;
						cout << ". Line:";
						cout << token[flag].line << endl;
						return false;
					}
				}

				else
				{
					flag--;
					cout << "Synax Error: There should be id after " + token[flag].str;
					cout << ". Line:";
					cout << token[flag].line << endl;
					return false;
				}
			}

			else
			{
				flag--;
				cout << "Synax Error: There should be , or ; after " + token[flag].str;
				cout << ". Line:";
				cout << token[flag].line << endl;
				return false;
			}
		}

		else if(token[flag].type == INT_VAL || token[flag].type == ID)
		{
			if (flag == end)
				return true;

			flag++;
			if(token[flag].type == COMMA)
			{
				flag++;
				if (token[flag].type == STRING_VAL)
				{
					if (flag == end)
						return true;
					else
					{
						cout << "Synax Error: There should be ; after " + token[flag].str;
						cout << ". Line:";
						cout << token[flag].line << endl;
						return false;
					}
				 }
				else
				{
					flag--;
					cout << "Synax Error: There should be string_val after " + token[flag].str;
					cout << ". Line:";
					cout << token[flag].line << endl;
					return false;
				}
			}

			else
			{
				flag--;
				cout << "Synax Error: There should be , or ; after " + token[flag].str;
				cout << ". Line:";
				cout << token[flag].line << endl;
				return false;
			}
		}

		else
		{
			flag--;
			cout << "Synax Error: There should be id or string or int_val after out ";
			cout << ". Line:";
			cout << token[flag].line << endl;
			return false;
		}
		
	}

	else
	{
		return true;
	}
}

//int FindNextSentence()
//{
//	for (int i = 0; i < token.size(); i++)
//	{
//		if (token[i].type == SEMI)
//		{
//			return i;
//			break;
//		}
//	}
//
//	return -1;
//}

//int main()
//{
//	//D:\5.txt
//	lex lex;
//	lex.scanline();
//	for (int i = 0; i < token.size(); i++)
//		cout << "[ " << token[i].str << " ]" << " --- [ " << token[i].type << " ]" << "ÐÐºÅ" << token[i].line << endl;
//
//	system("pause");
//	
//	if (InOutCheck(0, FindNextSentence()))
//	{
//		cout << "Right"<<endl;
//	}
//
//	system("pause");
//}
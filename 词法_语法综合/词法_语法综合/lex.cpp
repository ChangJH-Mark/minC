#include "lex.h"

vector<Node>token;

lex::lex()
{
	countline = 1;
	bufnum = 0;
	state = 0;
	memset(bufout, 0, sizeof(bufout));
	memset(bufin, 0, sizeof(bufin));
	char temp[100];
	cin >> temp;
	if ((temp[strlen(temp) - 4] == '.') && (temp[strlen(temp) - 3] == 't')
		&& (temp[strlen(temp) - 2] == 'x') && (temp[strlen(temp) - 1] == 't'))
	{
		const char * file_name;
		file_name = temp;
		fopen_s(&file, file_name, "r");
	}
	else
	{
	}
}

lex::~lex()
{
	fclose(file);
}

void lex::scanline()
{
	int i, j, k;
	while (fgets(bufin, 256, file) != NULL)
	{
		if (strlen(bufin) != 1)
		{
			clear(bufin);
			for (i = 0; bufin[i] != '\n' || bufnum; i++)
			{
				switch (state)
				{
				case 0://��ʼ״̬
					switch (wordkind(bufin[i]))
					{
					case 1://�ӵ���ĸ
						bufout[bufnum++] = bufin[i];
						state = 1;
						break;
					case 2://�ӵ�����
						bufout[bufnum++] = bufin[i];
						state = 3;
						break;
					case 3://'='
						bufout[bufnum++] = bufin[i];
						if (bufin[i + 1] == '=')
						{
							bufout[bufnum++] = bufin[i + 1];
							bufout[bufnum] = '\0';
							tokenlist(EQUAL);//==
							i++;
						}
						else
						{
							bufout[bufnum] = '\0';
							tokenlist(ASG);//=
						}
						state = 0;
						break;
					case 4://'>'
						bufout[bufnum++] = bufin[i];
						if (bufin[i + 1] == '=')
						{
							bufout[bufnum++] = bufin[i + 1];
							bufout[bufnum] = '\0';
							tokenlist(GRT_EQUAL);//>=
							i++;
						}
						else
						{
							bufout[bufnum] = '\0';
							tokenlist(GRT_THAN);//>
						}
						state = 0;
						break;
					case 5://'<'
						bufout[bufnum++] = bufin[i];
						if (bufin[i + 1] == '=')
						{
							bufout[bufnum++] = bufin[i + 1];
							bufout[bufnum] = '\0';
							tokenlist(LES_EQUAL);//<=
							i++;
						}
						else if (bufin[i + 1] == '>')
						{
							bufout[bufnum++] = bufin[i + 1];
							bufout[bufnum] = '\0';
							tokenlist(NOT_EQUAL);//<>
							i++;
						}
						else
						{
							bufout[bufnum] = '\0';
							tokenlist(LES_THAN);//<
						}
						state = 0;
						break;
					case 6://'&'
						bufout[bufnum++] = bufin[i];
						if (bufin[i + 1] == '&')
						{
							bufout[bufnum++] = bufin[i + 1];
							bufout[bufnum] = '\0';
							tokenlist(AND);//&&
							i++;
						}
						else
						{
							cout << "�޷�ʶ��ķ���" << "[ " << bufin[i] << " ]" << "�к�" << countline << endl;
							state = 0;
							bufnum = 0;
							memset(bufout, 0, sizeof(bufout));
						}
						state = 0;
						break;
					case 7://'|'
						bufout[bufnum++] = bufin[i];
						if (bufin[i + 1] == '|')
						{
							bufout[bufnum++] = bufin[i + 1];
							bufout[bufnum] = '\0';
							tokenlist(OR);//||
							i++;
						}
						else
						{
							cout << "�޷�ʶ��ķ���" << "[ " << bufin[i] << " ]" << "�к�" << countline << endl;
							state = 0;
							bufnum = 0;
							memset(bufout, 0, sizeof(bufout));
						}
						state = 0;
						break;
					case 8://' '
						state = 0;
						bufnum = 0;
						break;
					case 9://'"'
						for (j = i + 1; bufin[j] != '"' && (j < strlen(bufin)); j++)
						{
							if (bufin[j] == '\\')//ת��
							{
								switch (bufin[j + 1])
								{
								case 'n':bufout[bufnum++] = '\n'; j++; break;
								case 't':bufout[bufnum++] = '\t'; j++; break;
								case '0':bufout[bufnum++] = '\0'; j++; break;
								case '\\':bufout[bufnum++] = '\\'; j++; break;
								case '"':bufout[bufnum++] = '\"'; j++; break;
								default:
									//������
									break;
								}
							}
							else
								bufout[bufnum++] = bufin[j];
						}

						if (bufin[j] == '"')
						{
							i = j;
							bufout[bufnum] = '\0';
							tokenlist(STRING_VAL);//�ַ���
						}
						else
						{
							cout << "�޷�ʶ����ַ���" << "[ \"" << bufout << " ]" << "�к�" << countline << endl;
							state = 0;
							bufnum = 0;
							memset(bufout, 0, sizeof(bufout));
						}
						state = 0;
						break;
					case 11://'+,-,*,/,....'
						bufout[bufnum++] = bufin[i];
						bufout[bufnum] = '\0';
						switch (bufout[0])
						{
						case '+':tokenlist(ADD); break;
						case '-':tokenlist(SUB); break;
						case '*':tokenlist(MUL); break;
						case '/':tokenlist(DIV); break;
						case '%':tokenlist(MOD); break;
						case '$':tokenlist(DOLLAR); break;
						case '#':tokenlist(JING); break;
						case '!':tokenlist(NOT); break;
						case ',':tokenlist(COMMA); break;
						case '(':tokenlist(L_BRA); break;
						case ')':tokenlist(R_BRA); break;
						case '[':tokenlist(L_INDEX); break;
						case ']':tokenlist(R_INDEX); break;
						case '{':tokenlist(L_BOUNDER); break;
						case '}':tokenlist(R_BOUNDER); break;
						case ';':tokenlist(SEMI); break;
						}
						state = 0;
						break;
					default:
						cout << "�޷�ʶ��ķ���" << "[ " << bufin[i] << " ]" << "�к�" << countline << endl;
						state = 0;
						break;
					}
					break;
				case 1:
					switch (wordkind(bufin[i]))
					{
					case 1://�ӵ���ĸ
						bufout[bufnum++] = bufin[i];
						state = 1;
						break;
					case 2://�ӵ�����
						bufout[bufnum++] = bufin[i];
						state = 1;
						break;
					default:
						i--;
						bufout[bufnum] = '\0';
						switch (stringkind(bufout))
						{
						case -1:
							tokenlist(ID);	//��ʶ��
							state = 0;
							break;
						default://������
							tokenlist(stringkind(bufout));
							state = 0;
							break;
						}
						break;
					}
					break;
				case 3:
					switch (wordkind(bufin[i]))
					{
					case 2://�ӵ�����
						bufout[bufnum++] = bufin[i];
						state = 3;
						break;
					case 12://�ӵ�С����
						bufout[bufnum++] = bufin[i];
						state = 4;
						break;
					default:
						bufout[bufnum] = '\0';
						i--;
						tokenlist(INT_VAL);//���ͳ���
						state = 0;
						break;
					}
					break;
				case 4:
					switch (wordkind(bufin[i]))
					{
					case 2://�ӵ�����
						bufout[bufnum++] = bufin[i];
						state = 4;
						break;
					default:
						bufout[bufnum] = '\0';
						tokenlist(REAL_VAL);//ʵ�ͳ���
						state = 0;
						break;
					}
					break;
				}
			}
			countline++;
		}
		else
			countline++;
	}

	//����������������ֵ�ϲ���һ��token��
	for (i = 0; i < token.size(); i++)
	{
		if (token[i].type == ADD || token[i].type == SUB)
		{
			int flag = 0;
			if (token[i].type == ADD)
				flag = 1;
			if ((token[i + 1].type == INT_VAL || token[i + 1].type == REAL_VAL) && (token[i - 1].type == ASG || token[i - 1].type == L_BRA ||
				token[i - 1].type == GRT_THAN || token[i - 1].type == GRT_EQUAL || token[i - 1].type == LES_THAN || token[i - 1].type == LES_EQUAL || NOT_EQUAL || token[i - 1].type == EQUAL ||
				token[i - 1].type == AND || token[i - 1].type == OR || token[i - 1].type == IF || token[i - 1].type == WHILE))
			{
				vector<Node>::iterator it = token.begin() + i;
				token.erase(it);
				string s;
				s = token[i].str;
				if (flag)
					s = "+" + s;
				else
					s = "-" + s;
				token[i].str = s;
			}
		}
		else
		{
			continue;
		}
	}
}

void lex::clear(const char str[])
{
	int i, j;
	int noteCount = 0;
	int flag = 0;

	for (i = 0; bufin[i] != '\0'; i++)
	{
		//�Ʊ��
		if (bufin[i] == '\t')
		{
			for (j = i; bufin[j] != '\0'; j++)
			{
				bufin[j] = bufin[j + 1];
			}
			i = -1;
		}

		//ע��
		if (bufin[i] == '"')
		{
			flag = 1 - flag;
			continue;
		}
		if (bufin[i] == '/' && flag == 0)
		{
			if (bufin[i + 1] == '/')
			{
				bufin[i] = '\n';
				break;
			}
		}
	}

}

void lex::tokenlist(int type)
{
	Node buf;//�ݴ�token
	buf.line = countline;//�к�
	buf.str = bufout;//��
	buf.type = type;//����
	token.push_back(buf);
	//cout << "[ " << bufout << " ]" << " --- [ " << buf.type << " ]" << "�к�" << buf.line << endl;
	state = 0;
	bufnum = 0;
	memset(bufout, 0, sizeof(bufout));
}

int wordkind(const char c)
{
	if (letter(c))
		return 1;
	if (number(c))
		return 2;
	if (c == '=')
		return 3;
	if (c == '>')
		return 4;
	if (c == '<')
		return 5;
	if (c == '&')
		return 6;
	if (c == '|')
		return 7;
	if (c == ' ')
		return 8;
	if (c == '"')
		return 9;
	if (symbol(c))
		return 11;
	if (c == '.')
		return 12;
	return 0;
}

int stringkind(const char str[])
{
	int i;
	for (i = 0; i < 10; i++)
	{
		if (strcmp(str, keyword[i]) == 0)
			return i;
	}
	return -1;
}

int letter(const char c)
{
	if ((c >= 'a'&&c <= 'z') || (c >= 'A'&&c <= 'Z'))
		return 1;
	return 0;
}

int number(const char c)
{
	if (c >= '0'&&c <= '9')
		return 1;
	return 0;
}

int symbol(const char c)
{
	if (c == '+' || c == '-' || c == '*' || c == '%' || c == '$' || c == '#' || c == '!' || c == '/' ||
		c == ',' || c == '(' || c == ')' || c == '[' || c == ']' || c == '{' || c == '}' || c == ';')
		return 1;
	return 0;
}

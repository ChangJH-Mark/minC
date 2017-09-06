#include"lex.h"

struct MemberTable
{
	int type;//����������������������ͣ����Ϊ-1��������������ţ�-2�����һ�����
	int i; //��������������token������±�,���Ҫ����������ֱ�ӵ�token[i]������str�ͺ���
	int intValue;//����ʵ�ʵ�ֵ��,�����
	string stringValue;
};

typedef struct MemberTable MemberTable;

struct MethodTable
{
	int type;
	int i;//���غ�����ô������
	vector<int> memberType;
};

typedef struct MethodTable MethodTable;

vector<MemberTable> memberTable;
vector<MethodTable> methodTable;

void AddNewMemberToTable(int type,int i)
{
	MemberTable newTable;
	newTable.type = type;
	newTable.i = i;
	newTable.intValue = 0;
	memberTable.push_back(newTable);
}

void AddNewMethodToTable(int type, int i)
{
	MethodTable newTable;
	newTable.type = type;
	newTable.i = i;
	methodTable.push_back(newTable);
}

int FindMember(string name)
{
	for (int i = 0; i < memberTable.size(); i++)
	{
		if (token[memberTable[i].i].str.compare(name) == 0)
		{
			//ƥ��ɹ�,�����±�ţ���Ȼ����-1
			return  i;
		}
	}
	return -1;
}

int FindMethod(string name)
{
	for (int i = 0; i < methodTable.size(); i++)
	{
		if (token[methodTable[i].i].str.compare(name) == 0)
		{
			//ƥ��ɹ�,�����±�ţ���Ȼ����-1
			return  i;
		}
	}
	return -1;
}

bool ChangeMemberIntValue(string name,int value)
{
	//Ҳ��֮���һ��ù�ϣ��
	for (int i = 0; i < memberTable.size(); i++)
	{
		if (token[memberTable[i].i].str.compare(name) == 0)
		{
			//ƥ��ɹ�
			memberTable[i].intValue = value;
			return  true;
		}
	}
	return false;
}

bool ChangeMemeberStringValue(string name, string value)
{
	for (int i = 0; i < memberTable.size(); i++)
	{
		if (token[memberTable[i].i].str.compare(name) == 0)
		{
			//ƥ��ɹ�
			memberTable[i].stringValue = value;
			return  true;
		}
	}
	return false;
}

//bool ChangeMethodIntValue(string name, int value)
//{
//	for (int i = 0; i < methodTable.size(); i++)
//	{
//		if (token[methodTable[i].i].str.compare(name) == 0)
//		{
//			//ƥ��ɹ�
//			methodTable[i].intValue = value;
//			return  true;
//		}
//	}
//	return false;
//}

//bool ChangeMethodStringValue(string name, string value)
//{
//	for (int i = 0; i < methodTable.size(); i++)
//	{
//		if (token[methodTable[i].i].str.compare(name) == 0)
//		{
//			//ƥ��ɹ�
//			methodTable[i].stringValue = value;
//			return  true;
//		}
//	}
//	return false;
//}

void StartScopeForMember(int i)//����һ���µ������򣬼�ѹ��һ��������
{
	MemberTable newTable;
	newTable.type = -1;
	newTable.i = i;
	memberTable.push_back(newTable);
}

void StartScopeForMethod(int i)
{
	MethodTable newTable;
	newTable.type = -1;
	newTable.i = i;
	methodTable.push_back(newTable);
}

void EndScopeForMember()
{
	vector<MemberTable>::iterator it;
	int i = memberTable.size();
	for (i = memberTable.size() - 1; i >= 0; i--)
	{
		if (memberTable[i].type != -1)
		{
			it = memberTable.begin() + i;
			memberTable.erase(it);
		}

		else
		{
			it = memberTable.begin() + i;
			memberTable.erase(it);
			break;
		}
	}
}

void EndScopeForMethod()
{
	vector<MethodTable>::iterator it;
	int i = methodTable.size();
	for (i = methodTable.size(); i >= 0; i--)
	{
		if (methodTable[i].type != -1)
		{
			it = methodTable.begin() + i;
			methodTable.erase(it);
		}

		else
		{
			it = methodTable.begin() + i;
			methodTable.erase(it);
			break;
		}
	}
}

void PrintMember()
{
	for each (MemberTable member in memberTable)
	{
		cout << token[member.i].str << endl;
	}
}

void PrintMethod()
{
	for each (MethodTable method in methodTable)
	{
		cout << token[method.i].str << endl;
	}
}

//
//int main()
//{
//	lex lex;
//	lex.scanline();
//	for (int i = 0; i < token.size(); i++)
//		cout << "[ " << token[i].str << " ]" << " --- [ " << token[i].type << " ]" << "�к�" << token[i].line << endl;
//
//	system("pause");
//
//	AddNewMemberToTable(1, 0);
//	StartScopeForMember(1);
//	AddNewMemberToTable(1, 2);
//	AddNewMemberToTable(1, 3);
//	system("pause");
//
//}
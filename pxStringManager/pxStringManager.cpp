// pxStringManager.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <string.h>
#include <iostream>
using namespace std;

/*
Function     : ���ַ����в������ַ���

Return Value : �ҵ�֮�󷵻� ����λ��; δ�ҵ�����-1

Date         : 20170622
*
*/
int Find(char *in_szString, char *in_szSubString);

int Find(char *in_szString, char *in_szSubString)
{
	if (NULL == in_szString)
	{
		return -1;
	}

	if (NULL == in_szSubString)
	{
		return -1;
	}

	int nLen1 = strlen(in_szString);
	int nLen2 = strlen(in_szSubString);

	if (nLen1 < nLen2)
	{
		return -1;
	}

	int nCount = 0; // ������ȵĸ���
	bool bFound = false;

	for (int i = 0; i < nLen1 - nLen2; i++)
	{
		for (int j = 0; j < nLen2; j++)
		{
			if (in_szString[i + j] != in_szSubString[j])
			{
				break;
			}
			else
			{
				nCount++;

				if (nLen2 = nCount)
				{
					bFound = true;

					return i;
				}
			}
		}
	}

	if (!bFound)
	{
		return -1;
	}

	return -1;
}


int _tmain(int argc, _TCHAR* argv[])
{
	char *szString = "abcdefghijk";
	char *szSubString = "def";

	int nPos = Find(szString, szSubString);

	cout<<"String: "<<szString<<endl;
	cout<<"SubString: "<<szSubString<<endl;

	if (nPos < 0)
	{
		cout<<szSubString << " not in "<<szString<<endl;
	}
	else
	{
		cout<<szSubString <<  " is in " << szString << "; Position: "<<nPos<<endl;
	}

	return 0;
}


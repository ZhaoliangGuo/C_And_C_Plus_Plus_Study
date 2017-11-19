#include "stdafx.h"
#include "pxList.h"
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

void Print(list <string> listStudents);

/*
list ��֧�������ȡ.
���ǲ�����listStudents.begin() + 2��ָ��list�еĵ���������
��ΪSTL��list����˫����list��ʵ�ֵģ� ����֧�������ȡ��
*/

void TestList()
{
	// ����list
	list <string> listStudents;

	// ��Ա����push_back()��Ԫ�ؼ��뵽list�ĺ���
	listStudents.push_back("1 James");
	listStudents.push_back("2 Kate");

	// ��Ա����push_front()��Ԫ�ؼ��뵽list��ǰ��
	listStudents.push_front("3 New James");
	listStudents.push_front("4 New Kate");

	Print(listStudents);

	// �ж�list�Ƿ�Ϊ��
	if (!listStudents.empty())
	{
		printf("list is not empty!!\n");

		list <string> ::iterator iter;
		for (iter = listStudents.begin(); iter != listStudents.end(); ++iter)
		{
			cout<<*iter<<endl;
		}
	}
	else
	{
		printf("list is empty!!\n");
	}

	cout<<endl;

	int nCount = 0;
	nCount = count(listStudents.begin(), listStudents.end(), "1 James"); // ����ָ��Ԫ�ش��ڵĸ���
	printf("1 James nCount:%d\n", nCount);

	cout<<endl;

	// ����ָ��Ԫ��
	list <string> ::iterator iter;
	iter = find(listStudents.begin(), listStudents.end(), "1 James");
	if (iter != listStudents.end())
	{
		printf("1 James exist\n");
	}
	else
	{
		printf("1 James not exist\n");
	}

	cout<<endl;

	// ����
	listStudents.sort(); 
	printf("list sorting ...\n");
	Print(listStudents); // ��ӡ��ǰlist

	listStudents.push_back("5 LiLei");
	printf("after push_back 5 LiLei ...\n");
	Print(listStudents);

	// ɾ��ͷԪ��
	listStudents.erase(listStudents.begin()); 
	printf("after erase the begin element...\n");
	Print(listStudents);

	// ɾ��ͷԪ��
	listStudents.pop_front();
	printf("after pop_front...\n");
	Print(listStudents);

	// ɾ��βԪ��
	listStudents.pop_back();
	printf("after pop_back...\n");
	Print(listStudents);

	listStudents.remove("4 New Kate");
	printf("after remove 4 New Kate...\n");
	Print(listStudents);

	// ɾ������Ԫ��
	listStudents.erase(listStudents.begin(), listStudents.end());
	printf("after erase all elements...\n");
	if (listStudents.empty())
	{
		printf("list is empty\n");
	}
	else
	{
		printf("list is not empty\n");
	}
}

void Print(list <string> listStudents)
{
	list <string>::iterator iter = listStudents.begin();
	for (; iter != listStudents.end(); ++iter)
	{
		cout<<*iter<<endl;
	}

	cout<<endl;
}
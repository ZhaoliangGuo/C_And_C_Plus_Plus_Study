#include "stdafx.h"
#include "pxList.h"
#include <list>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;

void Print(list <string> listStudents);

/*
list 不支持随机存取.
我们不能用listStudents.begin() + 2来指向list中的第三个对象，
因为STL的list是以双链的list来实现的， 它不支持随机存取。
*/

void TestList()
{
	// 建立list
	list <string> listStudents;

	// 成员函数push_back()把元素加入到list的后面
	listStudents.push_back("1 James");
	listStudents.push_back("2 Kate");

	// 成员函数push_front()把元素加入到list的前面
	listStudents.push_front("3 New James");
	listStudents.push_front("4 New Kate");

	Print(listStudents);

	// 判断list是否为空
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
	nCount = count(listStudents.begin(), listStudents.end(), "1 James"); // 查找指定元素存在的个数
	printf("1 James nCount:%d\n", nCount);

	cout<<endl;

	// 查找指定元素
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

	// 排序
	listStudents.sort(); 
	printf("list sorting ...\n");
	Print(listStudents); // 打印当前list

	listStudents.push_back("5 LiLei");
	printf("after push_back 5 LiLei ...\n");
	Print(listStudents);

	// 删除头元素
	listStudents.erase(listStudents.begin()); 
	printf("after erase the begin element...\n");
	Print(listStudents);

	// 删除头元素
	listStudents.pop_front();
	printf("after pop_front...\n");
	Print(listStudents);

	// 删除尾元素
	listStudents.pop_back();
	printf("after pop_back...\n");
	Print(listStudents);

	listStudents.remove("4 New Kate");
	printf("after remove 4 New Kate...\n");
	Print(listStudents);

	// 删除所有元素
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
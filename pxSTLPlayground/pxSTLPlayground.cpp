// pxSTLPlayground.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <queue>
using namespace std;

void TestVector();
void TestMap();
void TestList();
void TestQueue();

int _tmain(int argc, _TCHAR* argv[])
{
	//TestQueue();

	TestVector();

	getchar();


	return 0;
}

void TestQueue()
{
	queue <int> qiNum;
	qiNum.push(1);
	qiNum.push(2);
	qiNum.push(3);

	int i = qiNum.front();

	cout<<i<<endl;

	int nCount = qiNum.size();
	cout<<"size: "<<nCount<<endl;

	while (!qiNum.empty())
	{
		cout<<qiNum.front()<<endl;
		qiNum.pop();
	}
}

void TestMap()
{

}

void TestVector()
{
	vector <int> vecNum;
	vecNum.push_back(1);
	vecNum.push_back(2);
	vecNum.push_back(3);
	vecNum.push_back(4);

	printf("******************orginal vector*****************\n");
	int nSize = vecNum.size();
	for (int i = 0; i < nSize; i++ )
	{
		cout<<"vecNum["<<i<<"] : "<<vecNum[i]<<endl;
	}

	int nTemp = 0;
	nTemp = vecNum.back();
	cout<<"vecNum.back() : "<<nTemp<<endl; // 4 

	printf("******************after pop_back*****************\n");
	vecNum.pop_back(); // 出栈， 即弹出栈顶的元素
	nSize = vecNum.size();
	for (int i = 0; i < nSize; i++ )
	{
		cout<<"vecNum["<<i<<"] : "<<vecNum[i]<<endl;
	}

	/*
	vecNum[0] : 1
	vecNum[1] : 2
	vecNum[2] : 3
	*/

	printf("******************after erase*****************\n");
	vecNum.erase(vecNum.begin(), vecNum.begin() + 1); // 删除首元素，即处于栈底的元素
	nSize = vecNum.size();
	for (int i = 0; i < nSize; i++ )
	{
		cout<<"vecNum["<<i<<"] : "<<vecNum[i]<<endl;
	}

	/*
	******************erase*****************
	vecNum[0] : 2
	vecNum[1] : 3
	*/
}


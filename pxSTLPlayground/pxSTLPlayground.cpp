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
	TestQueue();


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

	int nSize = vecNum.size();

	int nTemp = 0;
	nTemp = vecNum.back();
	vecNum.pop_back();
	vecNum.pop_back();

	nSize = vecNum.size();

	for (int i = 0; i < nSize; i++ )
	{
		cout<<"vecNum["<<i<<"] : "<<vecNum[i]<<endl;
	}
}


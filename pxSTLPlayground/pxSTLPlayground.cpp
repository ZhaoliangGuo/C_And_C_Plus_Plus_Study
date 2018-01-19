// pxSTLPlayground.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <vector>
#include <iostream>
#include <queue>
#include <list>
#include <map>
using namespace std;

#include "pxList.h"

struct SPxUserInfo
{
#define MAX_NAME_LEN (512)

	unsigned int nUserId;
	char szName[MAX_NAME_LEN];
	int  nAge;

	SPxUserInfo()
	{
		Flush();
	}

	~SPxUserInfo()
	{
		Flush();
	}

	void Flush()
	{
		nUserId = 0;
		memset(szName, 0,  MAX_NAME_LEN);
		nAge = 0;
	}
};

void TestVector();
void TestMap();
void TestList();
void TestQueue();

int _tmain(int argc, _TCHAR* argv[])
{
	//TestQueue();

	//TestMap();

	TestVector();

	//TestList();

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
	std::map <unsigned int, SPxUserInfo> mapUser;

	// 添加数据
	SPxUserInfo sPxUserInfo;
	sPxUserInfo.nUserId = 110;
	strcpy(sPxUserInfo.szName, "Kate"); 
	sPxUserInfo.nAge = 18;

	printf("数组方式插入关键字为%d的数据, Name:%s...\n", sPxUserInfo.nUserId, sPxUserInfo.szName);
	std::map <unsigned int, SPxUserInfo> :: iterator iter = mapUser.find(sPxUserInfo.nUserId);
	if (mapUser.end() == iter)
	{
		// 这种方式如果某关键字的数据已存在，会直接覆盖旧的.
		mapUser[sPxUserInfo.nUserId] = sPxUserInfo; // 用数组方式插入数据
	}

	// 遍历map
	printf("遍历map....\n");
	iter = mapUser.begin();
	while (mapUser.end() != iter)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);

		iter++;
	}
	printf("遍历结束. 元素个数:%d\n\n", mapUser.size());

	strcpy(sPxUserInfo.szName,"New Kate");
	printf("用数组方式插入 关键字为%d 变化后的数据, Name:%s ...\n", sPxUserInfo.nUserId, sPxUserInfo.szName);
	mapUser[sPxUserInfo.nUserId] = sPxUserInfo; // 直接覆盖
	printf("遍历map....\n");
	iter = mapUser.begin();
	while (mapUser.end() != iter)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);

		iter++;
	}
	printf("遍历结束. 元素个数:%d\n\n", mapUser.size());

	sPxUserInfo.nUserId = 120;
	strcpy(sPxUserInfo.szName, "James");
	sPxUserInfo.nAge = 20;

	printf("insert方式插入关键字为%d的数据, Name:%s ...\n", sPxUserInfo.nUserId, sPxUserInfo.szName);

	iter = mapUser.find(sPxUserInfo.nUserId);
	if (mapUser.end() == iter)
	{
		// 用insert方式插入数据
		// 这种方式指定关键字存在 则无法插入
		mapUser.insert(pair <unsigned int, SPxUserInfo> (sPxUserInfo.nUserId, sPxUserInfo));
	}

	printf("遍历map....\n");
	iter = mapUser.begin();
	while (mapUser.end() != iter)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);

		iter++;
	}
	printf("遍历结束. 元素个数:%d\n\n", mapUser.size());

	strcpy(sPxUserInfo.szName, "New James");
	printf("insert方式插入关键字为%d 修改后的数据, Name:%s ...\n", sPxUserInfo.nUserId, sPxUserInfo.szName);
	mapUser.insert(pair<unsigned int, SPxUserInfo> (sPxUserInfo.nUserId, sPxUserInfo));

	printf("遍历map....\n");
	iter = mapUser.begin();
	while (mapUser.end() != iter)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);

		iter++;
	}
	printf("遍历结束. 元素个数:%d\n\n", mapUser.size());

	// 删除指定元素
	int nUserId = 110;
	printf("删除nUserId = %d的元素...\n", nUserId);

	// 方式1
	//iter = mapUser.find(nUserId);
	//if (mapUser.end() != iter) // 如果找到
	//{
	//	mapUser.erase(iter);
	//}

	// 方式2 
	mapUser.erase(nUserId);

	for (iter = mapUser.begin(); iter != mapUser.end(); iter++)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);
	}
	printf("删除元素结束.元素个数:%d\n", mapUser.size());

	// 判断map是否为空
	if (mapUser.empty()) // empty函数: return true only if sequence is empty
	{
		printf("map is empty\n");
	}
	else
	{
		printf("map is not empty\n");
	}

	printf("\n");

	// 清空所有元素
	// 方式1:
	mapUser.clear();

	// 方式2:
	// 清空方式2
	//mapUser.erase(mapUser.begin(), mapUser.end());

	printf("开始清空所有元素...\n");
	if (mapUser.empty()) // empty函数: return true only if sequence is empty
	{
		printf("map is empty\n");
	}
	else
	{
		printf("map is not empty\n");
	}
}

struct SPxSampleItem
{
	int nIndex; 
	int nValue;  // 最大值

	SPxSampleItem()
	{
		Flush();
	}

	~SPxSampleItem()
	{
		Flush();
	}

	void Flush()
	{
		nIndex = -1;
		nValue = -1;
	}
};

// 升序排序规则
inline bool index_ascending(const SPxSampleItem & m1, const SPxSampleItem & m2) 
{
	return m1.nIndex < m2.nIndex;
}

// 降序排序规则
inline bool value_descending(const SPxSampleItem & m1, const SPxSampleItem & m2) 
{
	return m1.nValue > m2.nValue;
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


	// 演示排序
	//////////////////////////////////////////////////////////////////////////
	vector <SPxSampleItem> vsItem;
	SPxSampleItem sSampleItem;
	sSampleItem.nIndex = 3;
	sSampleItem.nValue = 500;
	vsItem.push_back(sSampleItem);

	sSampleItem.nIndex = 2;
	sSampleItem.nValue = 5;
	vsItem.push_back(sSampleItem);

	sSampleItem.nIndex = 1;
	sSampleItem.nValue = 5000;
	vsItem.push_back(sSampleItem);

	sSampleItem.nIndex = 4;
	sSampleItem.nValue = 50;
	vsItem.push_back(sSampleItem);

	printf("\n The original data ...\n");
	vector <SPxSampleItem> ::iterator iter = vsItem.begin();
	for(; iter != vsItem.end(); ++iter)
	{
		printf("Index: %4d, Value: %4d\n", iter->nIndex, iter->nValue);
	}

	// 根据value按降序排列
	::sort(vsItem.begin(), vsItem.end(), value_descending);

	printf("\nAfter descending by value ...\n");
	iter = vsItem.begin();
	for(; iter != vsItem.end(); ++iter)
	{
		printf("Index: %4d, Value: %4d\n", iter->nIndex, iter->nValue);
	}

	// 根据index进行升序排列
	::sort(vsItem.begin(), vsItem.end(), index_ascending);
	printf("\nAfter ascending by index ...\n");
	iter = vsItem.begin();
	for(; iter != vsItem.end(); ++iter)
	{
		printf("Index: %4d, Value: %4d\n", iter->nIndex, iter->nValue);
	}
}


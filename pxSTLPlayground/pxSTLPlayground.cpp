// pxSTLPlayground.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// �������
	SPxUserInfo sPxUserInfo;
	sPxUserInfo.nUserId = 110;
	strcpy(sPxUserInfo.szName, "Kate"); 
	sPxUserInfo.nAge = 18;

	printf("���鷽ʽ����ؼ���Ϊ%d������, Name:%s...\n", sPxUserInfo.nUserId, sPxUserInfo.szName);
	std::map <unsigned int, SPxUserInfo> :: iterator iter = mapUser.find(sPxUserInfo.nUserId);
	if (mapUser.end() == iter)
	{
		// ���ַ�ʽ���ĳ�ؼ��ֵ������Ѵ��ڣ���ֱ�Ӹ��Ǿɵ�.
		mapUser[sPxUserInfo.nUserId] = sPxUserInfo; // �����鷽ʽ��������
	}

	// ����map
	printf("����map....\n");
	iter = mapUser.begin();
	while (mapUser.end() != iter)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);

		iter++;
	}
	printf("��������. Ԫ�ظ���:%d\n\n", mapUser.size());

	strcpy(sPxUserInfo.szName,"New Kate");
	printf("�����鷽ʽ���� �ؼ���Ϊ%d �仯�������, Name:%s ...\n", sPxUserInfo.nUserId, sPxUserInfo.szName);
	mapUser[sPxUserInfo.nUserId] = sPxUserInfo; // ֱ�Ӹ���
	printf("����map....\n");
	iter = mapUser.begin();
	while (mapUser.end() != iter)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);

		iter++;
	}
	printf("��������. Ԫ�ظ���:%d\n\n", mapUser.size());

	sPxUserInfo.nUserId = 120;
	strcpy(sPxUserInfo.szName, "James");
	sPxUserInfo.nAge = 20;

	printf("insert��ʽ����ؼ���Ϊ%d������, Name:%s ...\n", sPxUserInfo.nUserId, sPxUserInfo.szName);

	iter = mapUser.find(sPxUserInfo.nUserId);
	if (mapUser.end() == iter)
	{
		// ��insert��ʽ��������
		// ���ַ�ʽָ���ؼ��ִ��� ���޷�����
		mapUser.insert(pair <unsigned int, SPxUserInfo> (sPxUserInfo.nUserId, sPxUserInfo));
	}

	printf("����map....\n");
	iter = mapUser.begin();
	while (mapUser.end() != iter)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);

		iter++;
	}
	printf("��������. Ԫ�ظ���:%d\n\n", mapUser.size());

	strcpy(sPxUserInfo.szName, "New James");
	printf("insert��ʽ����ؼ���Ϊ%d �޸ĺ������, Name:%s ...\n", sPxUserInfo.nUserId, sPxUserInfo.szName);
	mapUser.insert(pair<unsigned int, SPxUserInfo> (sPxUserInfo.nUserId, sPxUserInfo));

	printf("����map....\n");
	iter = mapUser.begin();
	while (mapUser.end() != iter)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);

		iter++;
	}
	printf("��������. Ԫ�ظ���:%d\n\n", mapUser.size());

	// ɾ��ָ��Ԫ��
	int nUserId = 110;
	printf("ɾ��nUserId = %d��Ԫ��...\n", nUserId);

	// ��ʽ1
	//iter = mapUser.find(nUserId);
	//if (mapUser.end() != iter) // ����ҵ�
	//{
	//	mapUser.erase(iter);
	//}

	// ��ʽ2 
	mapUser.erase(nUserId);

	for (iter = mapUser.begin(); iter != mapUser.end(); iter++)
	{
		sPxUserInfo = iter->second;
		printf("Id: %d, Name: %s, Age: %d\n", 
			sPxUserInfo.nUserId, sPxUserInfo.szName, sPxUserInfo.nAge);
	}
	printf("ɾ��Ԫ�ؽ���.Ԫ�ظ���:%d\n", mapUser.size());

	// �ж�map�Ƿ�Ϊ��
	if (mapUser.empty()) // empty����: return true only if sequence is empty
	{
		printf("map is empty\n");
	}
	else
	{
		printf("map is not empty\n");
	}

	printf("\n");

	// �������Ԫ��
	// ��ʽ1:
	mapUser.clear();

	// ��ʽ2:
	// ��շ�ʽ2
	//mapUser.erase(mapUser.begin(), mapUser.end());

	printf("��ʼ�������Ԫ��...\n");
	if (mapUser.empty()) // empty����: return true only if sequence is empty
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
	int nValue;  // ���ֵ

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

// �����������
inline bool index_ascending(const SPxSampleItem & m1, const SPxSampleItem & m2) 
{
	return m1.nIndex < m2.nIndex;
}

// �����������
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
	vecNum.pop_back(); // ��ջ�� ������ջ����Ԫ��
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
	vecNum.erase(vecNum.begin(), vecNum.begin() + 1); // ɾ����Ԫ�أ�������ջ�׵�Ԫ��
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


	// ��ʾ����
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

	// ����value����������
	::sort(vsItem.begin(), vsItem.end(), value_descending);

	printf("\nAfter descending by value ...\n");
	iter = vsItem.begin();
	for(; iter != vsItem.end(); ++iter)
	{
		printf("Index: %4d, Value: %4d\n", iter->nIndex, iter->nValue);
	}

	// ����index������������
	::sort(vsItem.begin(), vsItem.end(), index_ascending);
	printf("\nAfter ascending by index ...\n");
	iter = vsItem.begin();
	for(; iter != vsItem.end(); ++iter)
	{
		printf("Index: %4d, Value: %4d\n", iter->nIndex, iter->nValue);
	}
}


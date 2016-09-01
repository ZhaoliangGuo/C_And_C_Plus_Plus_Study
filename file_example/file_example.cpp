// file_example.cpp : �������̨Ӧ�ó������ڵ㡣
// Created by ZhaoliangGuo 2016-09-01
// ��ʾ�򵥵��ļ���д��ע������

#include "stdafx.h"
#include <stdlib.h>
//#include <shellapi.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char szFileName[_MAX_PATH] = {0};
	sprintf(szFileName, "%s", ".\\test.txt");

	// ���ļ�
	// w+ �򿪿ɶ�д�ļ������ļ��������ļ�������Ϊ�㣬�����ļ����ݻ���ʧ�����ļ��������������ļ�
	// at ��д��һ���ı��ļ�������������ı�ĩ׷�����ݡ�
	//FILE *fp = fopen(szFileName, "at");
	FILE *fp = fopen(szFileName, "w+");
	if (NULL == fp) // !!!ִ��fopen֮������fp������֤.
	{
		printf("open file: %s fail, errno: %d", szFileName, errno);

		return -1;
	}

	/*
	int fseek(FILE *fp,long offset,int origin); // ��fp���ļ���дλ��ָ���Ƶ�ָ����λ��

	offset: ���origin��ƫ���ֽ���

	origin: 
			SEEK_SET 0 �ļ���ͷ
			SEEK_CUR 1 ��ǰ��д��λ��
			SEEK_END 2 �ļ�β��
	*/
	fseek(fp, 0, SEEK_SET); // �ƶ����ļ�ͷ��
	fprintf(fp, "%s", "The first line.\n");

	// �ӵ�ǰλ������ƶ������ֽ�
	fseek(fp, 0L, SEEK_END);
	fprintf(fp, "%s", "Welcome to Beijing\n");

	fseek(fp, 0, SEEK_END); // �ƶ����ļ�β��
	fprintf(fp, "%s", "The last line\n");

	// ftell���ڵõ��ļ�λ��ָ�뵱ǰλ��������ļ��׵�ƫ���ֽ���
	fseek(fp, 0, SEEK_END);
	int nFileLength = ftell(fp); // �����ļ��ĳ���

	fflush(fp);

	printf("Filename:%s,nFileLength:%d\n", szFileName, nFileLength);

	fclose(fp);

	// ��ȡ�ļ��е����ݲ���ӡ
    fp = fopen(szFileName, "r");
	if (NULL == fp) // !!!ִ��fopen֮������fp������֤.
	{
		printf("open file: %s fail, errno: %d", szFileName, errno);

		return -1;
	}

	char szLine[1024] = {0};

	while(!feof(fp))// �ж��ļ��Ƿ��β
	{
		if(fgets(szLine, 1024,fp) != NULL)
		{
			printf("%s", szLine);
		}		
	}

	fclose(fp);

	// ���ļ�����֤���
	//ShellExecute(NULL, "open", szFileName, NULL, NULL, SW_SHOWNORMAL);

	getchar();

	return 0;
}


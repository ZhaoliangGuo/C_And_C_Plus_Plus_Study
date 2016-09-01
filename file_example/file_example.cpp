// file_example.cpp : 定义控制台应用程序的入口点。
// Created by ZhaoliangGuo 2016-09-01
// 演示简单的文件读写和注意事项

#include "stdafx.h"
#include <stdlib.h>
//#include <shellapi.h>

int _tmain(int argc, _TCHAR* argv[])
{
	char szFileName[_MAX_PATH] = {0};
	sprintf(szFileName, "%s", ".\\test.txt");

	// 打开文件
	// w+ 打开可读写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件
	// at 读写打开一个文本文件，允许读或在文本末追加数据。
	//FILE *fp = fopen(szFileName, "at");
	FILE *fp = fopen(szFileName, "w+");
	if (NULL == fp) // !!!执行fopen之后必须对fp进行验证.
	{
		printf("open file: %s fail, errno: %d", szFileName, errno);

		return -1;
	}

	/*
	int fseek(FILE *fp,long offset,int origin); // 把fp的文件读写位置指针移到指定的位置

	offset: 相对origin的偏移字节数

	origin: 
			SEEK_SET 0 文件开头
			SEEK_CUR 1 当前读写的位置
			SEEK_END 2 文件尾部
	*/
	fseek(fp, 0, SEEK_SET); // 移动到文件头部
	fprintf(fp, "%s", "The first line.\n");

	// 从当前位置向后移动两个字节
	fseek(fp, 0L, SEEK_END);
	fprintf(fp, "%s", "Welcome to Beijing\n");

	fseek(fp, 0, SEEK_END); // 移动到文件尾部
	fprintf(fp, "%s", "The last line\n");

	// ftell用于得到文件位置指针当前位置相对于文件首的偏移字节数
	fseek(fp, 0, SEEK_END);
	int nFileLength = ftell(fp); // 计算文件的长度

	fflush(fp);

	printf("Filename:%s,nFileLength:%d\n", szFileName, nFileLength);

	fclose(fp);

	// 读取文件中的内容并打印
    fp = fopen(szFileName, "r");
	if (NULL == fp) // !!!执行fopen之后必须对fp进行验证.
	{
		printf("open file: %s fail, errno: %d", szFileName, errno);

		return -1;
	}

	char szLine[1024] = {0};

	while(!feof(fp))// 判定文件是否结尾
	{
		if(fgets(szLine, 1024,fp) != NULL)
		{
			printf("%s", szLine);
		}		
	}

	fclose(fp);

	// 打开文件以验证结果
	//ShellExecute(NULL, "open", szFileName, NULL, NULL, SW_SHOWNORMAL);

	getchar();

	return 0;
}


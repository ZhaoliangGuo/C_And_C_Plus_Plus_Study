// pxSelect.cpp : 定义控制台应用程序的入口点。
// Zhaoliang Guo
// 20170617
// A demo for select

#include "stdafx.h"

#include <WinSock2.h>
#pragma comment(lib, "ws2_32.lib")

FD_SET fdReadSet;

#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	WSADATA wsaData;
	WORD    wVersionRequested;

	wVersionRequested = MAKEWORD(2, 2);  
	int ret = WSAStartup(wVersionRequested, &wsaData);  //加载套接字库  
	if(ret!=0)  
	{  
		printf("WSAStartup() failed!\n");  

		return -1;  
	}  

	// 确认WinSock DLL支持版本2.2  
	if(LOBYTE(wsaData.wVersion)!=2 || HIBYTE(wsaData.wVersion)!=2)  
	{  
		WSACleanup();  
		printf("Invalid WinSock version!\n");

		return -1;  
	}  

	SOCKET sockServer = socket(AF_INET, SOCK_STREAM, 0);

	struct sockaddr_in addrServ;
	memset(&addrServ, 0, sizeof(sockaddr_in));

	int nSockAddrLen = sizeof(SOCKADDR);

	addrServ.sin_family           = AF_INET;
	addrServ.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addrServ.sin_port             = htons(6666);

	bind(sockServer, (sockaddr *)&addrServ, nSockAddrLen);

	listen(sockServer, 5);

	// 超时时间
	timeval tvTimeout;
	tvTimeout.tv_sec  = 2;
	tvTimeout.tv_usec = 0;

	SOCKET sockConnected;

	int nAddrLen = sizeof(sockaddr_in);

	char szSendBuffer[1024] = {0};
	char szRecvBuffer[1024] = {0};

	cout<<"waiting connection..."<<endl;

	while (true)
	{
		FD_ZERO(&fdReadSet);
		FD_SET(sockServer, &fdReadSet);

		int nRet = select(0, &fdReadSet, NULL, NULL, &tvTimeout);
		if (-1 == nRet)
		{
			cout<<"error. break..."<<endl;

			break;
		}
		else if (0 == nRet) // timeout
		{
			cout<<"timeout. select again..."<<endl;

			continue;
		}
		else
		{
			cout<<"connection coming..."<<endl;

			/*		
				如果套接字句柄还在fd_set里
				说明客户端已经有connect的请求发过来了
				马上可以accept成功
			*/
			if (FD_ISSET(sockServer, &fdReadSet)) /*有新的客户端连接到来*/
			{
				sockaddr_in addrClient; // 用于保存客户端的网络节点的信息   

				sockConnected = accept(sockServer, (sockaddr *)&addrClient, &nSockAddrLen);

				if(sockConnected != INVALID_SOCKET) //创建成功
				{
					ZeroMemory(szSendBuffer, 1024);

					//inet_ntoa将结构转换为十进制的IP地址字符串
					sprintf_s(szSendBuffer, 1024, "Welcome %s!", inet_ntoa(addrClient.sin_addr));

					//成功建立连接后向客户端发送数据，结果将显示在客户端上
					send(sockConnected, szSendBuffer, strlen(szSendBuffer) + 1, 0);

					ZeroMemory(szRecvBuffer, 1024);
					recv(sockConnected, szRecvBuffer, 1024, 0);

					cout<<szRecvBuffer<<endl;

					closesocket(sockConnected);  
				}
				else
				{
					int nErrorCode = WSAGetLastError();
					printf("the err code is:%d/n", nErrorCode);
				}
			}
		}	
	}

	closesocket(sockServer);
	WSACleanup();  

	return 0;
}


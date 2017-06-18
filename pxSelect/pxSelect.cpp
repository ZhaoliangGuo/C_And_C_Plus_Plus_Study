// pxSelect.cpp : �������̨Ӧ�ó������ڵ㡣
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
	int ret = WSAStartup(wVersionRequested, &wsaData);  //�����׽��ֿ�  
	if(ret!=0)  
	{  
		printf("WSAStartup() failed!\n");  

		return -1;  
	}  

	// ȷ��WinSock DLL֧�ְ汾2.2  
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

	// ��ʱʱ��
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
				����׽��־������fd_set��
				˵���ͻ����Ѿ���connect�����󷢹�����
				���Ͽ���accept�ɹ�
			*/
			if (FD_ISSET(sockServer, &fdReadSet)) /*���µĿͻ������ӵ���*/
			{
				sockaddr_in addrClient; // ���ڱ���ͻ��˵�����ڵ����Ϣ   

				sockConnected = accept(sockServer, (sockaddr *)&addrClient, &nSockAddrLen);

				if(sockConnected != INVALID_SOCKET) //�����ɹ�
				{
					ZeroMemory(szSendBuffer, 1024);

					//inet_ntoa���ṹת��Ϊʮ���Ƶ�IP��ַ�ַ���
					sprintf_s(szSendBuffer, 1024, "Welcome %s!", inet_ntoa(addrClient.sin_addr));

					//�ɹ��������Ӻ���ͻ��˷������ݣ��������ʾ�ڿͻ�����
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


/* ������ ��� ���� */
#include "server_head.h"

void wsaInit(WORD &wVersionRequested, WSADATA &wsaData) 
{
	/* ���� ���� �Է� */
	wVersionRequested = MAKEWORD(2, 2);
	/* ���α׷����� ���ϴ� ������ ������ �˷���, ���� ����� ���� ���̺귯�� �ʱ�ȭ */
	int errNum = WSAStartup(wVersionRequested, &wsaData);

	/* ���� ���� �ʱ�ȭ�� �������� ��� */
	if (errNum != 0) 
	{
		/* ���� ������ ��� */
		cout << "[WSAStartup Error : " << WSAGetLastError() << "]\n";
		/* ���� ������ �ʱ�ȭ */
		WSACleanup();
		/* ���α׷� ���� */
		exit(1);
	}
}

SOCKET socketInit(SOCKADDR_IN& servAddr)
{
	/*
* sin_family	: IPv4 �ּ�ü�踦 ��Ÿ��
	* �⺻������ AF_INET(IPv4 ���ͳ� ��������) ���� ����
*/
	servAddr.sin_family = AF_INET;
	/*
		* sin_port		: 16 bit ��Ʈ ����
			* ������ ��Ʈ ��ȣ�� �Է�
			* ��Ʈ��ũ�� Big-Endian�� �����
			* htons(Host byte TO Network byte) �Լ��� ���� ��Ʈ ��ȣ�� Network byte�� ����
	*/
	servAddr.sin_port = htons(SERVER_PORT);
	/*
		* sin_addr		: 32 bit IP ����
			* ���� IP �ּҸ� �Է�
	*/
	servAddr.sin_addr.s_addr = inet_addr(SERV_IP);
	/*
		SOCK_STREAM		: ��Ʈ��, TCP ���������� ���� ���
		SOCK_DGRAM		: �����ͱ׷�,  UDP ���������� ���� ���
		IPPROTO_TCP		: TCP ��������
		iPPROTO_UDP		: UDP ��������
		IPPROTO_RAW		: RAW ����
	*/
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	/* ���� ������ �߻��� ��� */
	if (sock == INVALID_SOCKET)
	{
		/* ���� ������ ����ϰ� ���� */
		cout << "[Socket Error : " << WSAGetLastError() << "]\n";
		WSACleanup();
		exit(1);
	}
	return sock;
}

void bindSocket(SOCKET &sock, SOCKADDR_IN &servAddr)
{
	/* ������ ���Ͽ� ������ �ּҿ� ��Ʈ ��ȣ�� �Ҵ��� */
	int errNum = bind(sock, reinterpret_cast<SOCKADDR*>(&servAddr), sizeof(servAddr));
	/* ���� ������ �߻��� ��� */
	if (errNum == SOCKET_ERROR)
	{
		cout << "[Binding Error : " << WSAGetLastError() << "]\n";
		WSACleanup();
		exit(1);
	}
}

bool listenClient(SOCKET& servSock, SOCKADDR_IN &cliAddr)
{
	/* ������ Ŭ���̾�Ʈ�� ���� ���� ��û�� ��� ���� */
	listen(servSock, 5);
	cout << "Waiting for Client ... ... ... ..." << '\n';
	int cliLen = sizeof(cliAddr);
	SOCKET cliSock = accept(servSock, reinterpret_cast<SOCKADDR*>(&cliAddr), &cliLen);
	if (cliSock == INVALID_SOCKET)
	{
		cout << "[Client Socket Error : " << WSAGetLastError() << "]\n";
		return false;
	}

	cout << "[Connection establishted.New Client Socket number is " << cliSock << "]\n";
	return true;
}

bool commWithClient(SOCKET &servSock, SOCKET &cliSock) 
{
	int byteCnts;
}

int main(void)
{
	/* WORD : 16��Ʈ unsigned int */
	/* 
		* wVersionRequested(������)
		* ����(Window Socket)�� �ֻ��� ������ �˷��ֱ� ���� ����� �������� ����
		* ���� 8��Ʈ�� �� ������ ǥ��
		* ���� 8��Ʈ�� �� ������ ǥ��
	*/
	WORD wVersionRequested;
	/* WSADATA : ������ �Ӽ� ������ �����ϴ� ���� */
	WSADATA wsaData;
	/*
		* servAddr	: ���� ���� ���� ����
		* cliAddr	: Ŭ���̾�Ʈ ���� ���� ����
			* cliAddr ������ ���, ������ Ŭ���̾�Ʈ�� ������ �� �� ���� ����ϹǷ� �ϳ��� ��
	*/
	SOCKADDR_IN servAddr, cliAddr;
	/*
		* errNum	: ���� �Լ��� ��ȯ�Ǵ� ���� ��ȣ
			* �� �Լ����� ����, ���п� ���� ��ȯ ���� ���ݾ� �ٸ�
		* bytesCnt	: send �Լ��� ��ȯ ��
			* send �Լ��� ���� ������ ��Ŷ�� byte ���� ��ȯ��
	*/
	int bytesCnt;
	/* buf	: ��Ŷ�� ���� ������ ������ */
	string buf;

	/* ���� �ʱ�ȭ */
	wsaInit(wVersionRequested, wsaData);
	/* ���� �ʱ�ȭ */
	SOCKET servSock = socketInit(servAddr);
	/* ���� �Ҵ� */
	bindSocket(servSock, servAddr);
	/* Ŭ���̾�Ʈ�� ���� ���� ��� */
	listenClient(servSock, cliAddr);
}
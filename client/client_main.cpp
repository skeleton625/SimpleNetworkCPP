#include "client_head.h"

WSADATA wsaInit()
{
	WSADATA wsaData;
	WORD wVersionRequested = MAKEWORD(2, 2);

	if (WSAStartup(wVersionRequested, &wsaData)) {
		cout << "[WSAStrtup errer : " << WSAGetLastError() << "]\n";
		WSACleanup();
		exit(1);
	}
	return wsaData;
}

SOCKET socketInit(SOCKADDR_IN &servAddr)
{
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(SERVER_PORT);
	inet_pton(AF_INET, SERV_IP, &servAddr.sin_addr.s_addr);

	SOCKET cliSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (cliSock == INVALID_SOCKET)
	{
		cout << "[Socekt Error : " << WSAGetLastError() << "]\n";
		WSACleanup();
		exit(1);
	}
	return cliSock;
}

void connectWithServer(SOCKADDR_IN &target, SOCKET &cliSock)
{
	if (connect(cliSock, reinterpret_cast<SOCKADDR*>(&target), sizeof(target)) == SOCKET_ERROR)
	{
		cout << "[Connection Error : " << WSAGetLastError() << "]\n";
		cout << "[Please start Server Program First!!]\n";
		WSACleanup();
		exit(0);
	}
	cout << "[Connection is Complete !!]\n";
}

void commWithServer(SOCKET &cliSock)
{
	int byteCnts;
	string data;
	/* �������� ���� Ŀ�´����̼� ���� */
	while (true) {
		/* ������ �޼����� �Է� */
		cout << "[Send MSG]>>>";
		cin >> data;
		/* �Է��� �޼����� ����� ������ ���� */
		byteCnts = send(cliSock, data.c_str(), data.length(), 0);
		cout << "[Sending Message was Complete!!]\n";
		/* �Է��� �޼����� "END"�� ��� ���α׷� ���� */
		if (data == "END")
		{
			cout << "[Socket Communication is closing]\n";
			return;
		}
	}
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
	*/
	SOCKADDR_IN servAddr;
	/* Ŭ���̾�Ʈ ���� */
	SOCKET cliSock;
	
	/* ���� �Ӽ� �ʱ�ȭ */
	wsaData = wsaInit();
	/* Ŭ���̾�Ʈ ���� ���� */
	cliSock = socketInit(servAddr);
	/* �������� ���� �õ� */
	connectWithServer(servAddr, cliSock);
	/* Ŭ���̾�Ʈ�� ������ �޼��� ������ �ݺ��� */
	commWithServer(cliSock);
	/* ���� Ŭ���� ��ü ���� */
	closesocket(cliSock);
	WSACleanup();

	cout << "[Socket Program is ended]\n";
	return 0;
}
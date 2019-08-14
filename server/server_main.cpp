/* ������ ��� ���� */
#include "server_head.h"

void wsaInit(WORD &wVersionRequested, WSADATA &wsaData) 
{
	/* ���� ���� �Է� */
	wVersionRequested = MAKEWORD(2, 2);
	/* ���α׷����� ���ϴ� ������ ������ �˷���, ���� ����� ���� ���̺귯�� �ʱ�ȭ */
	/*
		* errNum	: ���� �Լ��� ��ȯ�Ǵ� ���� ��ȣ
			* �� �Լ����� ����, ���п� ���� ��ȯ ���� ���ݾ� �ٸ�
	*/
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

SOCKET socketInit(SOCKADDR_IN &servAddr)
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
		* inet_addr �Լ��� ����� �� ���� ������ inet_pton �Լ��� ���
		* int inet_pton(int af, const char *src, void *dst);
	*/
	inet_pton(AF_INET, SERV_IP, &servAddr.sin_addr.s_addr);
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

void listenClient(SOCKET& servSock)
{
	while (!isServerEnd) {
		/* ������ Ŭ���̾�Ʈ�� ���� ���� ��û�� ��� ���� */
		listen(servSock, 5);
		cout << "Waiting for Client ... ... ... ..." << '\n';
		/* ���� ������ Ŭ���̾�Ʈ ������ �ּ� ���� ���� */
		SOCKADDR_IN cliAddr;
		int cliLen = sizeof(cliAddr);
		/* Ŭ���̾�Ʈ�� ������ �޼����� ������ ��� �ش� Ŭ���̾�Ʈ�� ���� ���� */
		SOCKET cliSock = accept(servSock, reinterpret_cast<SOCKADDR*>(&cliAddr), &cliLen);
		/* ���� ������ ������ ���� ���, ������ ����ϰ� �������� ���� */
		if (cliSock == INVALID_SOCKET)
		{
			cout << "[Client Socket Error : " << WSAGetLastError() << "]\n";
		}
		/* ���� ������ ������ Ŭ���̾�Ʈ ���� ���� ��뷮 ���� ���� ���, ������ ��� */
		if (sockCnt > 5)
		{
			cout << "[There is NO place to connect with Client in Server]\n";
		}
		/* �׷��� ���� ��� �ش� Ŭ���̾�Ʈ ������ ������ ���� */
		else
		{
			for (int i = 0; i < CLIENT_MAX_COUNT; i++) {
				if (clientSock[i] == NULL) {
					clientSock[i] = cliSock;
					++sockCnt;
					cout << "[Connection establishted.New Client Socket number is " << cliSock << "]\n";
					break;
				}
			}
		}
	}
}

void commWithClient(SOCKET &servSock) 
{
	int byteCnts;
	/* buf	: ��Ŷ�� ���� ������ ������ */
	char buf[BUF_SIZE];
	/*
		* bytesCnt	: send �Լ��� ��ȯ ��
			* send �Լ��� ���� ������ ��Ŷ�� byte ���� ��ȯ��
	*/
	while (true)
	{
		for(int i = 0; i < 5; i++){
			memset(buf, 0, sizeof(buf));
			/*
				* Ŭ���̾�Ʈ ������ ���� �޼����� ���� ����
				* 1 : �ش� Ŭ���̾�Ʈ ����
				* 2 : �޼��� ����
				* 3 : �ִ� �޼��� ũ��
				* 4 : �÷��� ( �ɼ� ���� ���� )
			*/
			byteCnts = recv(clientSock[i], buf, BUF_SIZE, 0);
			/* ���� Ŭ���̾�Ʈ�κ��� ���۵� �޼����� ���� ��� �ǳ� �� */
			if (byteCnts == 0) continue;
			/* Ŭ���̾�Ʈ�κ��� ���۹��� �޼����� ��� */
			cout << "[Seeded " << clientSock[i] << " ]>>> " << buf << '\n';
			/* END �޼����� ���۹��� ��� ���α׷� ���� */
			if (strcmp(buf, "END")) {
				--sockCnt;
				/*
					* ���ϰ��� ������ ����
					* �������� �ش� Ŭ���̾�Ʈ�� ������ ����
				*/
				shutdown(clientSock[i], SD_BOTH);
				clientSock[i] = NULL;
			}
		}
	}

	cout << "[Communication is Done]\n";
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
	SOCKADDR_IN servAddr;
	/* ���� ���ϰ� Ŭ���̾�Ʈ ���� */
	SOCKET servSock;

	/* ���� �ʱ�ȭ */
	wsaInit(wVersionRequested, wsaData);
	/* ���� �ʱ�ȭ */
	servSock = socketInit(servAddr);
	/* ���� �Ҵ� */
	bindSocket(servSock, servAddr);
	/* Ŭ���̾�Ʈ�� ���� ���� ��� */
	thread lis(listenClient, servSock);
	/* Ŭ���̾�Ʈ�� �������� ���� ����� ���� */
	thread comm(commWithClient, servSock);

	/* �� ������ ��ȯ�� - ��ǻ� ���� */
	lis.join();
	comm.join();
	/* ���� ���� ���� */
	closesocket(servSock);
	/* ���� �ʱ�ȭ */
	WSACleanup();
	/* ���, ��ȭ ������ ���� */
	lis.detach();
	comm.detach();

	cout << "[Program Termination]";
	return 0;
}
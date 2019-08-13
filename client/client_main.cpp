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
	/* 서버와의 소켓 커뮤니케이션 시작 */
	while (true) {
		/* 전송할 메세지를 입력 */
		cout << "[Send MSG]>>>";
		cin >> data;
		/* 입력한 메세지를 연결된 서버로 전송 */
		byteCnts = send(cliSock, data.c_str(), data.length(), 0);
		cout << "[Sending Message was Complete!!]\n";
		/* 입력한 메세지가 "END"일 경우 프로그램 종료 */
		if (data == "END")
		{
			cout << "[Socket Communication is closing]\n";
			return;
		}
	}
}

int main(void)
{
	/* WORD : 16비트 unsigned int */
	/*
		* wVersionRequested(변수명)
		* 윈속(Window Socket)의 최상위 버전을 알려주기 위해 사용할 목적으로 정의
		* 상위 8비트는 부 버전을 표시
		* 하위 8비트는 주 버전을 표시
	*/
	WORD wVersionRequested;
	/* WSADATA : 윈속의 속성 정보를 설정하는 변수 */
	WSADATA wsaData;
	/*
		* servAddr	: 서버 소켓 정보 변수
	*/
	SOCKADDR_IN servAddr;
	/* 클라이언트 소켓 */
	SOCKET cliSock;
	
	/* 윈속 속성 초기화 */
	wsaData = wsaInit();
	/* 클라이언트 소켓 생성 */
	cliSock = socketInit(servAddr);
	/* 서버와의 연결 시도 */
	connectWithServer(servAddr, cliSock);
	/* 클라이언트가 서버로 메세지 전송을 반복함 */
	commWithServer(cliSock);
	/* 소켓 클래스 객체 제거 */
	closesocket(cliSock);
	WSACleanup();

	cout << "[Socket Program is ended]\n";
	return 0;
}
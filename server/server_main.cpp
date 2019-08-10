/* 정의한 헤더 파일 */
#include "server_head.h"

void wsaInit(WORD &wVersionRequested, WSADATA &wsaData) 
{
	/* 윈속 버전 입력 */
	wVersionRequested = MAKEWORD(2, 2);
	/* 프로그램에서 원하는 윈속의 버전을 알려줘, 윈속 사용을 위한 라이브러리 초기화 */
	/*
		* errNum	: 윈속 함수에 반환되는 에러 번호
			* 각 함수마다 성공, 실패에 따른 반환 값이 조금씩 다름
	*/
	int errNum = WSAStartup(wVersionRequested, &wsaData);

	/* 만일 윈속 초기화가 실패했을 경우 */
	if (errNum != 0) 
	{
		/* 윈속 에러를 출력 */
		cout << "[WSAStartup Error : " << WSAGetLastError() << "]\n";
		/* 윈속 설정을 초기화 */
		WSACleanup();
		/* 프로그램 종료 */
		exit(1);
	}
}

SOCKET socketInit(SOCKADDR_IN& servAddr)
{
	/*
* sin_family	: IPv4 주소체계를 나타냄
	* 기본적으로 AF_INET(IPv4 인터넷 프로토콜) 으로 정의
*/
	servAddr.sin_family = AF_INET;
	/*
		* sin_port		: 16 bit 포트 정보
			* 서버의 포트 번호를 입력
			* 네트워크는 Big-Endian을 사용함
			* htons(Host byte TO Network byte) 함수를 통해 포트 번호를 Network byte로 변경
	*/
	servAddr.sin_port = htons(SERVER_PORT);
	/*
		* sin_addr		: 32 bit IP 정보
			* 서버 IP 주소를 입력
	*/
	servAddr.sin_addr.s_addr = inet_addr(SERV_IP);
	/*
		SOCK_STREAM		: 스트림, TCP 프로토콜의 전송 방식
		SOCK_DGRAM		: 데이터그램,  UDP 프로토콜의 전송 방식
		IPPROTO_TCP		: TCP 프로토콜
		iPPROTO_UDP		: UDP 프로토콜
		IPPROTO_RAW		: RAW 소켓
	*/
	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	/* 만일 오류가 발생할 경우 */
	if (sock == INVALID_SOCKET)
	{
		/* 소켓 오류를 출력하고 종료 */
		cout << "[Socket Error : " << WSAGetLastError() << "]\n";
		WSACleanup();
		exit(1);
	}
	return sock;
}

void bindSocket(SOCKET &sock, SOCKADDR_IN &servAddr)
{
	/* 정의한 소켓에 서버의 주소와 포트 번호를 할당함 */
	int errNum = bind(sock, reinterpret_cast<SOCKADDR*>(&servAddr), sizeof(servAddr));
	/* 만일 오류가 발생할 경우 */
	if (errNum == SOCKET_ERROR)
	{
		cout << "[Binding Error : " << WSAGetLastError() << "]\n";
		WSACleanup();
		exit(1);
	}
}

SOCKET listenClient(SOCKET& servSock, SOCKADDR_IN &cliAddr)
{
	/* 서버가 클라이언트의 소켓 연결 요청을 듣기 시작 */
	listen(servSock, 5);
	cout << "Waiting for Client ... ... ... ..." << '\n';
	int cliLen = sizeof(cliAddr);
	SOCKET cliSock = accept(servSock, reinterpret_cast<SOCKADDR*>(&cliAddr), &cliLen);
	if (cliSock == INVALID_SOCKET)
	{
		cout << "[Client Socket Error : " << WSAGetLastError() << "]\n";
		exit(1);
	}

	cout << "[Connection establishted.New Client Socket number is " << cliSock << "]\n";
	return cliSock;
}

bool commWithClient(SOCKET &servSock, SOCKET &cliSock) 
{
	/* buf	: 패킷을 통해 전송할 데이터 */
	char buf[BUF_SIZE];
	/* 클라이언트 소켓을 통해 전송된 모든 데이터 */
	string msg;
	/*
		* bytesCnt	: send 함수의 반환 값
			* send 함수를 통해 전송한 패킷의 byte 수를 반환함
	*/
	int byteCnts;
	while (true)
	{
		msg = "";
		/*
			* 클라이언트 소켓을 통해 메세지를 전송 받음
			* 1 : 해당 클라이언트 소켓
			* 2 : 메세지 버퍼
			* 3 : 최대 메세지 크기
			* 4 : 플래그 ( 옵션 적용 가능 )
		*/
		while (recv(cliSock, buf, BUF_SIZE, 0))
		{ 
			/* 전송된 데이터를 합쳐 줌 */
			msg += buf;
		}
		if (msg == "END") break;
		else
		{
			cout << "[Receive Client " << cliSock << "Message]\n";
			cout << msg << '\n';
		}
	}

	cout << "[Communication is Done]\n";
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
		* cliAddr	: 클라이언트 소켓 정보 변수
			* cliAddr 변수의 경우, 서버와 클라이언트를 연결할 때 한 번만 사용하므로 하나면 됨
	*/
	SOCKADDR_IN servAddr, cliAddr;
	/* 서버 소켓과 클라이언트 소켓 */
	SOCKET servSock, cliSock;

	/* 윈속 초기화 */
	wsaInit(wVersionRequested, wsaData);
	/* 소켓 초기화 */
	servSock = socketInit(servAddr);
	/* 소켓 할당 */
	bindSocket(servSock, servAddr);
	/* 클라이언트의 소켓 연결 대기 */
	cliSock = listenClient(servSock, cliAddr);
	/* 클라이언트와 서버간의 소켓 통신을 시작 */
	commWithClient(servSock, cliSock);
	/* 서버 소켓 종료 */
	closesocket(servSock);
	/* 윈속 초기화 */
	WSACleanup();

	cout << "[Program Termination]";
	return 0;
}
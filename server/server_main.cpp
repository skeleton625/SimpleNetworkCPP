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

SOCKET socketInit(SOCKADDR_IN &servAddr)
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
		* inet_addr 함수를 사용할 수 없기 때문에 inet_pton 함수를 사용
		* int inet_pton(int af, const char *src, void *dst);
	*/
	inet_pton(AF_INET, SERV_IP, &servAddr.sin_addr.s_addr);
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

void commWithClient(SOCKET& servSock, SOCKET cliSock)
{
	/*
		* bytesCnt	: send 함수의 반환 값
			* send 함수를 통해 전송한 패킷의 byte 수를 반환함
	*/
	int byteCnts;
	/* buf	: 패킷을 통해 전송할 데이터 */
	char buf[BUF_SIZE];
	while (true)
	{
		memset(buf, 0, sizeof(buf));
		/* 비어있는 공간일 경우 넘어감 */
		/*
			* 클라이언트 소켓을 통해 메세지를 전송 받음
			* 1 : 해당 클라이언트 소켓
			* 2 : 메세지 버퍼
			* 3 : 최대 메세지 크기
			* 4 : 플래그 ( 옵션 적용 가능 )
		*/
		byteCnts = recv(cliSock, buf, BUF_SIZE, 0);
		if (byteCnts <= 0) continue;
		/* 클라이언트로부터 전송받은 메세지를 출력 */
		cout << "[Sended " << cliSock << " ]>>> " << buf << '\n';
		/* END 메세지를 전송받을 경우 프로그램 종료 */
		if (!strcmp(buf, "END")) {
			--sockCnt;
			/*
				* 소켓간의 전송을 종료
				* 서버에서 해당 클라이언트의 소켓을 제거
			*/
			cout << "[Client " << cliSock << " was disconnected !!]\n";
			shutdown(cliSock, SD_BOTH);
			break;
		}
	}
}


SOCKET listenClient(SOCKET& servSock)
{
	while (!isServerEnd) {
		/* 서버가 클라이언트의 소켓 연결 요청을 듣기 시작 */
		listen(servSock, 5);
		cout << "Waiting for Client ... ... ... ..." << '\n';
		/* 새로 생성할 클라이언트 소켓의 주소 변수 정의 */
		SOCKADDR_IN cliAddr;
		int cliLen = sizeof(cliAddr);
		/* 클라이언트가 서버로 메세지를 전송할 경우 해당 클라이언트의 소켓 생성 */
		SOCKET cliSock = accept(servSock, reinterpret_cast<SOCKADDR*>(&cliAddr), &cliLen);
		/* 소켓 생성시 오류가 있을 경우, 에러를 출력하고 반응하지 않음 */
		if (cliSock == INVALID_SOCKET)
		{
			cout << "[Client Socket Error : " << WSAGetLastError() << "]\n";
		}
		/* 또한 서버가 접속한 클라이언트 수가 서버 허용량 보다 많을 경우, 에러를 출력 */
		if (sockCnt > 5)
		{
			cout << "[There is NO place to connect with Client in Server]\n";
		}
		/* 그렇지 않을 경우 해당 클라이언트 소켓을 서버에 저장 */
		else
		{
			/* 비어 있는 변수에 해당 클라이언트 소켓 객체를 입력 */
			++sockCnt;
			cout << "[Connection establishted.New Client Socket number is " << cliSock << "]\n";
			/* 클라이언트의 메세지 전송 시작 */
			/* 연결된 클라이언트의 대화를 Thread로 동시에 처리 */
			workers.push_back(thread(commWithClient, ref(servSock), ref(cliSock)));
			//return cliSock;
		}
	}
	return NULL;
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
	SOCKADDR_IN servAddr;
	/* 서버 소켓과 클라이언트 소켓 */
	SOCKET servSock;

	/* 윈속 초기화 */
	wsaInit(wVersionRequested, wsaData);
	/* 소켓 초기화 */
	servSock = socketInit(servAddr);
	/* 소켓 할당 */
	bindSocket(servSock, servAddr);
	/* 클라이언트의 소켓 연결 대기 */
	//thread lis(listenClient, ref(servSock));
	/* 두 쓰레드 반환값 - 사실상 없음 */
	SOCKET cliSock = listenClient(servSock);
	//commWithClient(servSock, cliSock);
	//lis.join();
	/* 서버 소켓 종료 */
	closesocket(servSock);
	/* 윈속 초기화 */
	WSACleanup();
	/* 듣기, 대화 쓰레드 종료 */
	//lis.detach();

	cout << "[Program Termination]";
	return 0;
}
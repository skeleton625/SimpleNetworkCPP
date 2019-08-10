#include "client_head.h"

int main(void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
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
	
	return 0;
}
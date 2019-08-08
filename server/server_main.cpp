/* 정의한 헤더 파일 */
#include "server_head.h"

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
	/*
		* errNum	: 윈속 함수에 반환되는 에러 번호
			* 각 함수마다 성공, 실패에 따른 반환 값이 조금씩 다름
		* bytesCnt	: send 함수의 반환 값
			* send 함수를 통해 전송한 패킷의 byte 수를 반환함
	*/
	int errNum, bytesCnt;
	/*
		* buf	: 패킷을 통해 전송할 데이터
	*/
	string buf;
}
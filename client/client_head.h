#include <iostream>
#include <string>
/* Window 용 Socket 라이브러리 */
#include <WinSock2.h>
using namespace std;
/* ws2_32.lib 파일 링크 */
#pragma comment(lib, "ws2_32.lib")

/* 한 패킷의 크기(Byte) */
#define BUF_SIZE 1024
/* 서버의 패킷 큐 크기 */
#define QUEUE_SIZE 10
/* 현 프로그램의 포트 번호 */
#define SERVER_PORT 8084
/* 서버의 IP 주소 (지역 주소로 정의) */
#define SERV_IP "127.0.0.1"

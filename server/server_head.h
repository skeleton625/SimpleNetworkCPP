#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
/* Window 용 Socket 라이브러리 */
#include <WinSock2.h>
/* inet_addr 함수 대신 inet_pton 함수 사용하기 위한 헤더 파일 */
#include <WS2tcpip.h>
/* 여러 클라이언트의 접속과 메세지 출력을 하기 위한 쓰레드 클래스 */
#include <thread>
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
/* 서버에 연결할 수 있는 총 클라이언트 수 */
#define CLIENT_MAX_COUNT 5

int sockCnt = 0;
bool isServerEnd = false;
SOCKET clientSock[5];
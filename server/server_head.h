#include <iostream>
#include <cstdlib>
#include <map>
#include <string>
/* Window �� Socket ���̺귯�� */
#include <WinSock2.h>
/* inet_addr �Լ� ��� inet_pton �Լ� ����ϱ� ���� ��� ���� */
#include <WS2tcpip.h>
/* ���� Ŭ���̾�Ʈ�� ���Ӱ� �޼��� ����� �ϱ� ���� ������ Ŭ���� */
#include <thread>
using namespace std;
/* ws2_32.lib ���� ��ũ */
#pragma comment(lib, "ws2_32.lib")

/* �� ��Ŷ�� ũ��(Byte) */
#define BUF_SIZE 1024
/* ������ ��Ŷ ť ũ�� */
#define QUEUE_SIZE 10
/* �� ���α׷��� ��Ʈ ��ȣ */
#define SERVER_PORT 8084
/* ������ IP �ּ� (���� �ּҷ� ����) */
#define SERV_IP "127.0.0.1"
/* ������ ������ �� �ִ� �� Ŭ���̾�Ʈ �� */
#define CLIENT_MAX_COUNT 5

int sockCnt = 0;
bool isServerEnd = false;
SOCKET clientSock[5];
#include <iostream>
#include <string>
/* Window �� Socket ���̺귯�� */
#include <WinSock2.h>
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

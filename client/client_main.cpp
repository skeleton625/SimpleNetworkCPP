#include "client_head.h"

int main(void)
{
	WORD wVersionRequested;
	WSADATA wsaData;
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
	*/
	SOCKADDR_IN servAddr;
	/* Ŭ���̾�Ʈ ���� */
	SOCKET cliSock;
	
	return 0;
}
/* ������ ��� ���� */
#include "server_head.h"

int main(void)
{
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
		* cliAddr	: Ŭ���̾�Ʈ ���� ���� ����
			* cliAddr ������ ���, ������ Ŭ���̾�Ʈ�� ������ �� �� ���� ����ϹǷ� �ϳ��� ��
	*/
	SOCKADDR_IN servAddr, cliAddr;
	/*
		* errNum	: ���� �Լ��� ��ȯ�Ǵ� ���� ��ȣ
			* �� �Լ����� ����, ���п� ���� ��ȯ ���� ���ݾ� �ٸ�
		* bytesCnt	: send �Լ��� ��ȯ ��
			* send �Լ��� ���� ������ ��Ŷ�� byte ���� ��ȯ��
	*/
	int errNum, bytesCnt;
	/*
		* buf	: ��Ŷ�� ���� ������ ������
	*/
	string buf;
}
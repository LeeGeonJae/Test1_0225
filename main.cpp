#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>
#include <iostream>
#include <string>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	WSAData wsaData;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		cout << "Winsoc Error : " << GetLastError() << endl;
		exit(-1);
	}


	SOCKET ServerSocket;
	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (ServerSocket == INVALID_SOCKET)
	{
		cout << "Socket Error : " << GetLastError() << endl;
		exit(-1);
	}


	SOCKADDR_IN ServerAddr;
	memset(&ServerAddr, 0, sizeof(ServerAddr));
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons(5001);
	ServerAddr.sin_addr.s_addr = inet_addr("127.0.0.1");


	if (connect(ServerSocket, (SOCKADDR*)&ServerAddr, sizeof(ServerAddr)) == SOCKET_ERROR)
	{
		cout << "Connect Error : " << GetLastError() << endl;
		exit(-1);
	}

	char Message[1024] = "give me message.";
//	cin.getline(Buffer, 1023);

	send(ServerSocket, Message, strlen(Message) + 1, 0);

	int RecvLength = recv(ServerSocket, Message, 1024, 0);
	if (RecvLength == 0)
	{
		cout << "RecvLength : " << GetLastError() << endl;
		exit(-1);
	}
	else if (RecvLength < 0)
	{
		cout << "Error : " << GetLastError() << endl;
		exit(-1);
	}

	cout << "Serversended : " << Message << endl;

	closesocket(ServerSocket);

	WSACleanup();

	return 0;
}
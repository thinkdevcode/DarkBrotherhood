#ifndef _GTSOCKET_
	#define _GTSOCKET_

	#ifndef _WINDOWS_
		#define WIN32_LEAN_AND_MEAN
		#include <windows.h>
	#endif

	#ifndef _STDIO_
		#include <stdio.h>
	#endif

	#ifndef _IOSTREAM_
		#include <iostream>
	#endif

	#ifndef _STDLIB_
		#include <stdlib.h>
	#endif

	#ifndef _VECTOR_
		#include <vector>
	#endif

	#ifndef _TIME_
		#include <time.h>
	#endif

	#ifndef _STRING_
		#include <string>
	#endif

	#ifndef _WINSOCK2_
		#include <winsock2.h>
		#include <ws2tcpip.h>
	#endif

	#ifndef _STRSAFE_
		#include <strsafe.h>
	#endif

	using namespace std;
	using std::string;
	using std::vector;

class GTSocket
{
public:
	GTSocket();
	static GTSocket *Instance();
	int InitializeServer(const char * Port);
	SOCKET InitializeClient(const char * Port, char *IP);
	int Listen();
	SOCKET Accept();
	int ShutdownClient(SOCKET sClient);
	int GetSocketStatus(SOCKET sStatus);
	int Close(SOCKET sCSocket);
	int CloseAll(SOCKET *sCSocket, int NumOfSockets);
	int SendPacket(SOCKET sCSocket, const char *buffer, int iBufferLength);
	int SendToAll(SOCKET *sCSocket, int NumOfSockets, const char *buffer, int iBufferLength);
	char *RecievePacket(SOCKET sCSocket);
	int getUsersOnline();
	~GTSocket();
private:
	WSADATA wsaData;
    SOCKET sLSocket;
	SOCKET ConnectSocket;
	struct addrinfo *result;
	bool IsServer;
	bool IsClient;
	int iResult;
	int iSend;
	int iUsersOnline;
};

#endif
#ifndef _GTSOCKET_
	#include "GTSocket.h"
#endif

GTSocket::GTSocket()
{

}

GTSocket *GTSocket::Instance()
{
	static GTSocket GTS;

	return &GTS;
}

int GTSocket::InitializeServer(const char * Port)
{
	IsServer = 1;
	IsClient = 0;
	sLSocket = INVALID_SOCKET;
    addrinfo *result = NULL, hints;
	iUsersOnline = 0;

    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
	{
		return 0;
    }

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;
    hints.ai_flags = AI_PASSIVE;

    iResult = getaddrinfo(NULL, Port, &hints, &result);
    if ( iResult != 0 )
	{
        WSACleanup();
		return 0;
    }

    sLSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
    if (sLSocket == INVALID_SOCKET)
	{
        freeaddrinfo(result);
        WSACleanup();
		return 0;
    }

	iResult = bind( sLSocket, result->ai_addr, (int)result->ai_addrlen);

    if (iResult == SOCKET_ERROR)
	{
        freeaddrinfo(result);
        closesocket(sLSocket);
        WSACleanup();
		cout << "Here " << endl;
		return 0;
    }

	freeaddrinfo(result);

	iResult = listen(sLSocket, SOMAXCONN);

    if (iResult == SOCKET_ERROR)
	{
        closesocket(sLSocket);
        WSACleanup();
		return 0;
    }

	return 1;
}

SOCKET GTSocket::InitializeClient(const char * Port, char * IP)
{
    ConnectSocket = INVALID_SOCKET;
    addrinfo *result = NULL,
             *ptr = NULL,
             hints;
    
    iResult = WSAStartup(MAKEWORD(2,2), &wsaData);
    if (iResult != 0)
	{
        return 0;
    }

    ZeroMemory( &hints, sizeof(hints) );
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    iResult = getaddrinfo(IP, Port, &hints, &result);
    if ( iResult != 0 )
	{
        WSACleanup();
        return 0;
    }

    for(ptr=result; ptr != NULL ;ptr=ptr->ai_next)
	{
        ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
        if (ConnectSocket == INVALID_SOCKET) {
            freeaddrinfo(result);
            WSACleanup();
            return 0;
        }

        iResult = connect( ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
        if (iResult == SOCKET_ERROR) {
            closesocket(ConnectSocket);
            ConnectSocket = INVALID_SOCKET;
            continue;
        }
        break;
    }

    freeaddrinfo(result);

    if (ConnectSocket == INVALID_SOCKET) {
        WSACleanup();
        return 0;
    }

	return ConnectSocket;
}

SOCKET GTSocket::Accept()
{
	SOCKET tSocket = accept(sLSocket, NULL, NULL);
    if (tSocket == INVALID_SOCKET)
	{
		return 0;
    }
	iUsersOnline += 1;

	return tSocket;
}

int GTSocket::ShutdownClient(SOCKET sClient)
{
    iResult = shutdown(sClient, SD_SEND);
    if (iResult == SOCKET_ERROR) {
        closesocket(sClient);
        WSACleanup();
        return 0;
    }
	closesocket(sClient);
	return 1;
}

int GetSocketStatus(SOCKET sStatus)
{
	if (sStatus == INVALID_SOCKET)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int GTSocket::Close(SOCKET sCSocket)
{
	int iClose = closesocket(sCSocket);
	if (iClose == SOCKET_ERROR)
	{
		return 0;
	}
	iUsersOnline -= 1;
	return 1;
}

int CloseAll(SOCKET *sCSocket, int NumOfSockets)
{
	if (NumOfSockets != NULL)
	{
		while (NumOfSockets >= 0)
		{
			int iCloseAll = closesocket(sCSocket[NumOfSockets]);
			if (iCloseAll == SOCKET_ERROR)
			{
				return 0;
			}
			--NumOfSockets;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

int GTSocket::SendPacket(SOCKET sCSocket, const char *buffer, int iBufferLength)
{

	if (sCSocket == INVALID_SOCKET)
	{
		return 0;
	}
	
	iSend = send(sCSocket, buffer, iBufferLength, 0);
	if (iSend == SOCKET_ERROR)
	{
		cout << "send() error :: " << WSAGetLastError() << endl;
		return 0;
	}

	return 1;
}

int GTSocket::SendToAll(SOCKET *sCSocket, int NumOfSockets, const char *buffer, int iBufferLength)
{
	if (NumOfSockets != NULL)
	{
		//SOCKET *nSocket = new SOCKET[NumOfSockets];
		//nSocket = sCSocket;
		while (NumOfSockets >= 0)
		{
			int iSendAll = send(sCSocket[NumOfSockets], buffer, iBufferLength, 0);
			if (iSendAll == SOCKET_ERROR)
			{
				cout << "SendToAll() error :: " << WSAGetLastError() << endl;
				return 0;
			}
			--NumOfSockets;
		}
		return 1;
	}
	else
	{
		return 0;
	}
}

char *GTSocket::RecievePacket(SOCKET sCSocket)
{
	char buffer[65538];
	int iRecieve = recv(sCSocket, buffer, sizeof(buffer), 0);
	if (iRecieve > 0)
	{
		return buffer;
	}
	else
	{
		cout << "rcv() error :: " << WSAGetLastError() << endl;
		return 0;
	}
}

int GTSocket::getUsersOnline()
{
	return iUsersOnline;
}

GTSocket::~GTSocket()
{
    WSACleanup();
}
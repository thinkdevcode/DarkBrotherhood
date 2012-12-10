#ifndef _CSOCKET_
	#define _CSOCKET_

	#ifndef _WINSOCK2API_
		#include "winsock2.h"
	#endif

namespace CSocket
{
	extern "C"
	{
		void Send(BYTE *pSocket, const char *format, ...);
		void SendV(BYTE *pSocket, const char *format, va_list va);

		void Close(BYTE *pSocket);

		in_addr GetAddress(BYTE *pSocket);
		BYTE *GetUser(BYTE *pSocket);
	}
}

#endif

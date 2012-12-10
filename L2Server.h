#ifndef _L2SERVER_
	#define _L2SERVER_

struct FVector
{
	double x;
	double y;
	double z;
};

namespace L2Server
{
	extern "C"
	{
		int Assemble(char *buf, int bufLen, const char *format, ...);
		int VAssemble(char *buf, int bufLen, const char *format, va_list ap);

		const unsigned char *Disassemble(const unsigned char *packet, const char *format, ...);
		int VDisassemble(const unsigned char *packet, const char *format, va_list ap);

		void BroadcastToNeighbor(void *pAddress, int ObjID, int nDistance, FVector vPos, const char *format, ...);
		
		void BroadcastToAllUser(const char *format, ...);
		void BroadcastToAllUser_Announce(const wchar_t *szAnnounce);

		void RequestSavePledgePower(void *pAddress, CCreature *pUser);

		void NpcServer_Send(void *pAddress, const char *szFormat, ...);
	}
};

#endif
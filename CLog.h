#ifndef _CLOG_
	#define _CLOG_

	#ifndef _GLOBAL_
		#include "Global.h"
	#endif

	#ifndef _TIME_
		#include "time.h"
	#endif

	#ifndef _STDIO_
		#include "stdio.h"
	#endif

using std::string;

class CLog
{
public:

	CLog();

	void AddLog(const char *format, ...);

	~CLog();

private:

	FILE *pFile;
	string LogPath;

};

#endif
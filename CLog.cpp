#ifndef _CLOG_
	#include "CLog.h"
#endif

CLog::CLog()
{

}

void CLog::AddLog(const char *format, ...)
{
	fopen_s(&pFile, "L2EP[PvP].txt", "a+");

	string LogText;
	char Buf[1024];
	time_t rawtime;
	struct tm *timeinfo;
	va_list vl;

	va_start(vl, format);
		vsprintf_s(Buf, 1024, format, vl);
	va_end(vl);

	time (&rawtime);
	timeinfo = localtime(&rawtime);

	LogText.append(asctime(timeinfo));
	LogText.append(Buf);
	LogText.append("\n\n");

	fputs(LogText.c_str(), pFile);

	fclose(pFile);
}

CLog::~CLog()
{

}
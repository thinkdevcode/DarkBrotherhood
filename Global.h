#ifndef _GLOBAL_
	#define _GLOBAL_

	#ifndef _WINDOWS_
		#define WIN32_LEAN_AND_MEAN
		#include "windows.h"
	#endif

	#ifndef _STDIO_
		#include "stdio.h"
	#endif

	#ifndef _STRING_
		#include "string"
	#endif

	#ifndef _LIST_
		#include "list"
	#endif

	#ifndef _VECTOR_
		#include <vector>
	#endif

	typedef double QWORD;

	#pragma warning(disable: 4311)

#endif
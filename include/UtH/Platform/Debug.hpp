#pragma once
#ifndef DEBUG_H_UTH
#define DEBUG_H_UTH

#include <cstdarg>

namespace uth
{
	void WriteError(const char* text, ...);
	void WriteWarning(const char* text, ...);
	void WriteLog(const char* text, ...);
	void PrintGLString(const char* name, unsigned int s);
	void CheckGLError(const char* op);
	void CheckALError(const char* op);
}

#if defined(WIN32) || defined(_WIN32)
	#define __func__ __FUNCTION__
#endif

#define Deprecated(moreInfo) uth::WriteLog("Function %s is deprecated \nFile %s \nLine %d \n%s\n", __func__, __FILE__, __LINE__, moreInfo);

#endif
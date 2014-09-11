#pragma once
#ifndef DEBUG_H
#define DEBUG_H

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

#endif
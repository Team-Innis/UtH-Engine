#pragma once
#ifndef OGLCHECK_H_UTH
#define OGLCHECK_H_UTH


namespace uth
{
	/// If NDEBUG hasn't been defined, then define a macro that calls the given
	/// and checks for GL errors. Otherwise the function simply gets called
	/// without any error checking.
	#if !defined(NDEBUG)
		#if defined(WIN32) || defined(_WIN32)
			#define __func__ __FUNCTION__
		#endif

		#define oglCheck(function) ((function), uth::checkGlError(__FILE__, __LINE__, __func__))

	#else

		#define oglCheck(function) (function)

	#endif


	/// A function to check the last GL error.
	///
	/// \param file Inside which file the error was checked.
	/// \param line The number of the line where the error was checked.
	///
	/**/ void checkGlError(const char* file, const unsigned int line, const char* func);

} // namespace uth

#endif

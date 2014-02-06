/***********************************************************************************************/
/**/ #pragma once
/***********************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////////////


namespace uth
{
    /// If NDEBUG hasn't been defined, then define a macro that calls the given
    /// and checks for GL errors. Otherwise the function simply gets called
    /// without any error checking.
    #if !defined(NDEBUG)

        #define oglCheck(function) ((function), uth::checkGlError(__FILE__, __LINE__))

    #else

        #define oglCheck(function) (function)

    #endif


    /// A function to check the last GL error.
    ///
    /// \param file Inside which file the error was checked.
    /// \param line The number of the line where the error was checked.
    ///
    /**/ void checkGlError(const char* file, const unsigned int line);

} // namespace uth
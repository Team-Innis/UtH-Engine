// OS macros

// Windows
#if defined(_WIN32) || defined(__WIN32__)

    #define UTH_SYSTEM_WINDOWS
    #define UTH_SYSTEM_OPENGL  

// Linux
#elif defined(linux) || defined(__linux)

    #define UTH_SYSTEM_LINUX
    #define UTH_SYSTEM_OPENGL 

// Mac & iOS
#elif defined(__APPLE__) || defined(MACOSX) || defined(macintosh) || defined(Macintosh)
    
    #if defined(TARGET_OS_IPHONE) || defined(TARGET_IPHONE_SIMULATOR)

        #define UTH_SYSTEM_IOS
        #define UTH_SYSTEM_OPENGLES 

    #else

        #define UTH_SYSTEM_MACOS
        #define UTH_SYSTEM_OPENGL 

    #endif

// Android
#elif defined(__ANDROID__) || defined(ANRDOID)

    #define UTH_SYSTEM_ANDROID
    #define UTH_SYSTEM_OPENGLES 

#else

    #error Unknown OS

#endif
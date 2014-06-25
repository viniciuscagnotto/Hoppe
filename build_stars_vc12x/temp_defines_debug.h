#ifndef I3D_OS_S3E
#   define I3D_OS_S3E 1
#endif
#ifndef I3D_PLATFORM_S3E
#   define I3D_PLATFORM_S3E 1
#endif
#ifndef IW_APP_NAME
#   define IW_APP_NAME "Stars"
#endif
#ifndef IW_APP_VERSION
#   define IW_APP_VERSION "1.0"
#endif
#ifndef IW_ASSERTION_CHANNEL_2D
#   define IW_ASSERTION_CHANNEL_2D 1
#endif
#ifndef IW_ASSERTION_CHANNEL_FACEBOOK
#   define IW_ASSERTION_CHANNEL_FACEBOOK 1
#endif
#ifndef IW_ASSERTION_CHANNEL_FLURRY
#   define IW_ASSERTION_CHANNEL_FLURRY 1
#endif
#ifndef IW_ASSERTION_CHANNEL_IW_2DSCENEGRAPH
#   define IW_ASSERTION_CHANNEL_IW_2DSCENEGRAPH 1
#endif
#ifndef IW_ASSERTION_CHANNEL_WEBVIEW
#   define IW_ASSERTION_CHANNEL_WEBVIEW 1
#endif
#ifndef IW_DEBUG
#   define IW_DEBUG 1
#endif
#ifndef IW_MKF_IW2D
#   define IW_MKF_IW2D 1
#endif
#ifndef IW_MKF_IW2DSCENEGRAPH
#   define IW_MKF_IW2DSCENEGRAPH 1
#endif
#ifndef IW_MKF_IW2DSCENEGRAPHCORE
#   define IW_MKF_IW2DSCENEGRAPHCORE 1
#endif
#ifndef IW_MKF_IWGEOM
#   define IW_MKF_IWGEOM 1
#endif
#ifndef IW_MKF_IWGL
#   define IW_MKF_IWGL 1
#endif
#ifndef IW_MKF_IWGX
#   define IW_MKF_IWGX 1
#endif
#ifndef IW_MKF_IWGXFONT
#   define IW_MKF_IWGXFONT 1
#endif
#ifndef IW_MKF_IWRESMANAGER
#   define IW_MKF_IWRESMANAGER 1
#endif
#ifndef IW_MKF_IWTWEEN
#   define IW_MKF_IWTWEEN 1
#endif
#ifndef IW_MKF_IWUTIL
#   define IW_MKF_IWUTIL 1
#endif
#ifndef IW_MKF_LIBJPEG
#   define IW_MKF_LIBJPEG 1
#endif
#ifndef IW_MKF_LIBPNG
#   define IW_MKF_LIBPNG 1
#endif
#ifndef IW_MKF_S3EFACEBOOK
#   define IW_MKF_S3EFACEBOOK 1
#endif
#ifndef IW_MKF_S3EFLURRY
#   define IW_MKF_S3EFLURRY 1
#endif
#ifndef IW_MKF_S3EWEBVIEW
#   define IW_MKF_S3EWEBVIEW 1
#endif
#ifndef IW_MKF_SOUNDENGINE
#   define IW_MKF_SOUNDENGINE 1
#endif
#ifndef IW_MKF_TINICONV
#   define IW_MKF_TINICONV 1
#endif
#ifndef IW_MKF_ZLIB
#   define IW_MKF_ZLIB 1
#endif
#ifndef IW_PLATFORM_S3E
#   define IW_PLATFORM_S3E 1
#endif
#ifndef IW_SDK
#   define IW_SDK 1
#endif
#ifndef IW_TRACE_CHANNEL_FACEBOOK
#   define IW_TRACE_CHANNEL_FACEBOOK 1
#endif
#ifndef IW_TRACE_CHANNEL_FACEBOOK_VERBOSE
#   define IW_TRACE_CHANNEL_FACEBOOK_VERBOSE 2
#endif
#ifndef IW_TRACE_CHANNEL_FLURRY
#   define IW_TRACE_CHANNEL_FLURRY 1
#endif
#ifndef IW_TRACE_CHANNEL_FLURRY_VERBOSE
#   define IW_TRACE_CHANNEL_FLURRY_VERBOSE 2
#endif
#ifndef IW_TRACE_CHANNEL_IW_2DSCENEGRAPH
#   define IW_TRACE_CHANNEL_IW_2DSCENEGRAPH 1
#endif
#ifndef IW_TRACE_CHANNEL_WEBVIEW
#   define IW_TRACE_CHANNEL_WEBVIEW 1
#endif
#ifndef IW_TRACE_CHANNEL_WEBVIEW_VERBOSE
#   define IW_TRACE_CHANNEL_WEBVIEW_VERBOSE 2
#endif
#ifndef IW_USE_ASSERTIONS
#   define IW_USE_ASSERTIONS 1
#endif
#ifndef IW_USE_CALLSTACK
#   define IW_USE_CALLSTACK 1
#endif
#ifndef IW_USE_TRACING
#   define IW_USE_TRACING 1
#endif
#ifndef S3E_INCLUDE_LEGACY
#   define S3E_INCLUDE_LEGACY 1
#endif
#ifndef _CRT_SECURE_NO_DEPRECATE
#   define _CRT_SECURE_NO_DEPRECATE 1
#endif
#ifndef __S3E__
#   define __S3E__ 1
#endif

/* including "extra_body" specified by the mkb plugin */

#undef win32

#ifndef unix
    #define unix
#endif

#ifndef __unix
    #define __unix
#endif

/*
#ifndef _REENTRANT
    #define _REENTRANT
#endif
*/

#if !defined I3D_ARCH_ARM && !defined I3D_ARCH_X86 && !defined I3D_ARCH_AMD64 && !defined I3D_ARCH_MIPS
    #if defined __ARMCC_VERSION || defined __ARMC__ || defined __arm__
        #define I3D_ARCH_ARM
    #elif defined __mipsel || defined __MIPSEL
        #define I3D_ARCH_MIPS
    #elif defined __amd64
        #define I3D_ARCH_AMD64
    #else
        #define I3D_ARCH_X86
    #endif
#endif

#if defined I3D_ARCH_X86 && !defined __i386__
    #define __i386__
#endif

#if defined I3D_ARCH_ARM && !defined __ARM__
    #define __ARM__
#endif

#if defined __cplusplus && defined _MSC_VER && _MSC_VER < 1400 && !defined IW_WCHAR_T_DEFINED && !defined __clang__
    // wchar_t is a builtin in C++ .. but not for MSVC <= 2003
    typedef unsigned short wchar_t;
    #define IW_WCHAR_T_DEFINED
#endif

#if defined _MSC_VER && !defined __clang__
    #pragma warning (disable: 4786)
#endif

#if !defined __S3E_CL_WRAPPER
    #if !defined __INTELLISENSE__
        #error "Wrong compiler used.  Please run the Hub to configure Visual Studio"
    #endif
#endif

#undef _WIN32
#undef WIN32
#undef __linux__
#undef __linux
#undef __gnu_linux__
#undef linux

#if defined __i386__ && defined __ANDROID__
#ifndef S3E_ANDROID_X86
#   define S3E_ANDROID_X86 1
#endif
#endif

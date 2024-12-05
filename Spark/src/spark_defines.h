#ifndef __SPARK_DEFINES_H__
#define __SPARK_DEFINES_H__

#if defined(_WIN32) && defined(SPARK_BUILD_DLL)
/* We are building SPARKAPI as a Win32 DLL */
#define SPARKAPI __declspec(dllexport)
#elif defined(_WIN32) && defined(SPARK_DLL)
/* We are calling a SPARKAPI Win32 DLL */
#define SPARKAPI __declspec(dllimport)
#elif defined(__GNUC__) && defined(_GLFW_BUILD_DLL)
/* We are building SPARKAPI as a Unix shared library */
#define SPARKAPI __attribute__((visibility("default")))
#else
#define SPARKAPI
#endif

#ifdef SPARK_FAST_CALL
#define SPARKCALL __fastcall
#elif defined(SPARK_STD_CALL)
#define SPARKCALL __stdcall
#elif defined(SPARK_C_CALL)
#define SPARKCALL __cdecl
#else
#define SPARKCALL
#endif

#define SPARKSTATIC static

#define SPARK_VERSION_MAJOR 1
#define SPARK_VERSION_MINOR 0
#define SPARK_VERSION_PATCH 0

#define SPARK_SERIALIZER_MAGIC 0x53504152 // 'SPAR' in hexadecimal
#define SPARK_SERIALIZER_VERSION 1

#define SPARK_MAKE_VERSION(major, minor, patch)                                \
  ((major << 22) | (minor << 12) | patch)

#define SPARK_VERSION                                                          \
  SPARK_MAKE_VERSION(SPARK_VERSION_MAJOR, SPARK_VERSION_MINOR,                 \
                     SPARK_VERSION_PATCH)

#define SPARK_IS_VERSION(version) (version == SPARK_VERSION)
#define SPARK_IS_VERSION_OR_GREATER(version) (version >= SPARK_VERSION)
#define SPARK_IS_VERSION_OR_LOWER(version) (version <= SPARK_VERSION)

#define SPARK_MAKE_VERSION_STRING(major, minor, patch)                         \
  #major "." #minor "." #patch

#define SPARK_VERSION_STRING                                                   \
  SPARK_MAKE_VERSION_STRING(SPARK_VERSION_MAJOR, SPARK_VERSION_MINOR,          \
                            SPARK_VERSION_PATCH)

#endif
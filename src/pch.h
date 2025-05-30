#ifndef PCH_H
#define PCH_H

#define ISOLATION_AWARE_ENABLED 1

/*
    Only put files that never change or are rarely changed in this file.
    An include graph will be provided for some headers that were not explicit
    added. VC++ is a requirement.

    We don't care about warnings for library files.
*/
#pragma warning(push)
#pragma warning(disable : 4091 4191 4365 4464 4571 4619 4623 4625 4626 4768 4774 5026 5027 5039 5045)
/* Windows Stuff */
#include "windows_nodefines.h"
#include <ShlObj.h> // CommCtrl
#include <WindowsX.h>
#include <Windows.h>
#include <tchar.h>
#include <Shlwapi.h>
#include <direct.h>
#include <io.h>
#include <wincodec.h>

#if WIN32_LEAN_AND_MEAN
#include <CommDlg.h>
#include <MMSystem.h>
#include <ShellAPI.h>
#endif // WIN32_LEAN_AND_MEAN

/*
    Nuke WinAPI #defines - anything including this file should be using the
    ra versions.
*/
#undef CreateDirectory
#undef GetMessage

/* C Stuff */
#include <cctype>

/* STL Stuff */
#include <array> // algorithm, iterator, tuple
#include <atomic>
#include <chrono>
#include <fstream>
#include <iomanip>
#include <map>
#include <memory>
#include <mutex> // chrono (time.h), functional, thread, utility
#include <queue> // deque, vector, algorithm
#include <set>
#include <sstream> // string
#include <stack>
#include <unordered_map>
#include <variant>

#pragma warning(push)
// Look at this file if you want to know what they are and what they mean
#include "pch_cppcorecheck_suppressions.h"
#include "pch_microsoft_suppressions.h"

/* RapidJSON Stuff */
#define RAPIDJSON_HAS_STDSTRING 1
#define RAPIDJSON_NOMEMBERITERATORCLASS 1
#include <rapidjson\document.h> // has reader.h
#include <rapidjson\error\en.h>
#include <rapidjson\istreamwrapper.h>
#include <rapidjson\ostreamwrapper.h>
#include <rapidjson\writer.h> // has stringbuffer.h

/* gsl stuff */
#define GSL_THROW_ON_CONTRACT_VIOLATION
#include <gsl\gsl>

// the default GSL Expects() macro throws an exception, which we don't try to catch anywhere.
// replace it with our custom handler, which will log and report the error before throwing it.
#ifndef RA_UTEST
 #ifdef NDEBUG
  extern void __gsl_contract_handler(const char* const file, unsigned int line);
  #undef Expects
  #define Expects(cond) (GSL_LIKELY(cond) ? static_cast<void>(0) : __gsl_contract_handler(__FILE__, __LINE__))
 #else
  extern void __gsl_contract_handler(const char* const file, unsigned int line, const char* const error);
  #undef Expects
  #define Expects(cond) (GSL_LIKELY(cond) ? static_cast<void>(0) : __gsl_contract_handler(__FILE__, __LINE__, GSL_STRINGIFY(cond)))
 #endif
#endif

#pragma warning(pop)

#if RA_UTEST
#include <CodeAnalysis\Warnings.h>
#pragma warning(push)
#pragma warning(disable : ALL_CPPCORECHECK_WARNINGS)
#include "CppUnitTest.h"
#pragma warning(pop)
#endif /* RA_UTEST */

/* rcheevos stuff */
#pragma warning(push)
#pragma warning(disable : 4201) // nameless struct
#include <rcheevos.h>
#pragma warning(pop)
#pragma warning(pop)

#endif /* !PCH_H */

/****************************************************************************
 *                                                                          *
 *  This file is part of TidopLib and can not be copied and/or distributed  *
 *  without the express permision of ITOS3D ENGINEERING S.L                 *
 *                                                                          *
 *  Contact: http://www.itos3d.com                                          *
 *           http://tidop.usal.es                                           *
 *                                                                          *
 *--------------------------------------------------------------------------*
 *                                                                          *
 *  Copyright (C) 2018, ITOS3D ENGINEERING S.L - All rights reserved        *
 *                                                                          *
 ****************************************************************************/

#include "tidop/core/exception.h"

#include <boost/filesystem.hpp>

//#if defined WIN32
//#include <atlstr.h>
//#endif
#include <locale>
#include <codecvt>

//TODO: mirar
//https://en.cppreference.com/w/cpp/error/nested_exception
//https://en.cppreference.com/w/cpp/error/throw_with_nested
//https://stackoverflow.com/questions/37227300/why-doesnt-c-use-stdnested-exception-to-allow-throwing-from-destructor/37227893#37227893
//https://github.com/GPMueller/mwe-cpp-exception
//https://www.boost.org/doc/libs/1_65_1/doc/html/stacktrace/getting_started.html#stacktrace.getting_started.how_to_print_current_call_stack

namespace fs = boost::filesystem;

namespace tl
{

/* ---------------------------------------------------------------------------------- */

#ifdef TL_ENABLE_DEPRECATED_METHODS
Exception::Exception(const char *error)
  : mError(error), 
    mFile(""), 
    mLine(-1), 
    mFunction("")
{
  messagef();
}

Exception::Exception(const char *error, const char *file, int line, const char *function)
  : mError(error), mFile(file), mLine(line), mFunction(function)
{
  messagef();
}
#endif

Exception::Exception(const std::string &error)
  : mError(error),
    mFile(""),
    mLine(-1),
    mFunction("")
{
}

Exception::Exception(const std::string &error, const std::string &file, int line, const std::string &function )
  : mError(error), 
    //mFile(file),
    mLine(line), 
    mFunction(function)
{
  mFile = fs::path(file).filename().string();
  messagef();
}

const char *Exception::what() const TL_NOEXCEPT
{
  return mMessage.c_str();
}

std::string Exception::file() const
{
  return mFile;
}

std::string Exception::function() const
{
  return mFunction;
}

int tl::Exception::line() const
{
  return mLine;
}

void Exception::messagef()
{
  char buf[1000];
  if (mLine == -1) {
    mMessage = mError;
  } else {
#if defined _MSC_VER
    sprintf_s(buf, 1000, "%s (%s:%u, %s)", mError.c_str(), mFile.c_str(), mLine, mFunction.c_str());
#else
    snprintf(buf, 1000, "%s (%s:%u, %s)", mError.c_str(), mFile.c_str(), mLine, mFunction.c_str());
#endif
    mMessage = std::string(buf);
  }
}

/* ---------------------------------------------------------------------------------- */

//void throw_exception(const char *error, const char *file, int line, const char *function)
//{
//  throw Exception(error, file, line, function);
//}

Exception make_exception(const char *error, const char *file, int line, const char *function)
{
  return Exception(error, file, line, function);
}

/* ---------------------------------------------------------------------------------- */


#ifdef WIN32
std::string formatWindowsErrorMsg(DWORD errorCode)
{
  DWORD flags = FORMAT_MESSAGE_FROM_SYSTEM
    | FORMAT_MESSAGE_IGNORE_INSERTS
    | FORMAT_MESSAGE_MAX_WIDTH_MASK;
  
  TCHAR errorMessage[1024] = TEXT("");

  FormatMessage(flags,
                nullptr,
                errorCode,
                MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
                errorMessage,
                sizeof(errorMessage)/sizeof(TCHAR),
                nullptr);

  std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
  std::string strError = converter.to_bytes(errorMessage);

  //std::string strError = CW2A(errorMessage);
  return strError;
}
#endif


} // End namespace tl

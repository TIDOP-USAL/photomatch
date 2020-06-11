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


#include "tidop/core/log.h"
#include "tidop/core/messages.h"


#if (__cplusplus >= 201703L)
//C++17
//http://en.cppreference.com/w/cpp/filesystem
#include <filesystem>
namespace fs = std::filesystem;
#else
//Boost
//http://www.boost.org/doc/libs/1_66_0/libs/filesystem/doc/index.htm
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
#endif


namespace tl
{

std::unique_ptr<Log> Log::sObjLog;
std::string Log::sLogFile = "";
EnumFlags<MessageLevel> Log::sLevel = MessageLevel::msg_error;
std::string Log::sTimeLogFormat = "%d/%b/%Y %H:%M:%S";
std::mutex Log::mtx;
#ifdef TL_MESSAGE_HANDLER
bool Log::sPauseListener = false;
#endif

Log::Log()
#ifdef TL_MESSAGE_HANDLER
  : MessageManager::Listener(false)
#endif
{
}

Log::~Log()
{
  sObjLog.release();
}

Log &Log::instance()
{
  if (sObjLog.get() == nullptr) {
    std::lock_guard<std::mutex> lck(Log::mtx);
    if (sObjLog.get() == nullptr) {
      sObjLog.reset(new Log());
    }
  }
  return *sObjLog;
}

void Log::write(const char *msg)
{

  std::string date = formatTimeToString("%d/%b/%Y %H:%M:%S");

  if (sLogFile.empty()) {
    // Log por defecto
    fs::path logPath(getRunfile());
    logPath.replace_extension(".log");
    sLogFile = logPath.string();
  }
  std::ofstream hLog(sLogFile,std::ofstream::app);
  if (hLog.is_open()) {
    std::lock_guard<std::mutex> lck(Log::mtx);
    hLog << date << " - " << msg << "\n";
    hLog.close();
  } else {
    msgError("Permission denied: %s", sLogFile.c_str());
  }
}

#ifdef TL_MESSAGE_HANDLER

void Log::onMsgDebug(const char *msg, const char *date)
{
  if (sLevel.isActive(MessageLevel::msg_debug)) {
    _write(msg, date);
  }
}

void Log::onMsgInfo(const char *msg, const char *date)
{
  if (sLevel.isActive(MessageLevel::msg_info)) {
    _write(msg, date);
  }
}

void Log::onMsgWarning(const char *msg, const char *date)
{
  if (sLevel.isActive(MessageLevel::msg_warning)) {
    _write(msg, date);
  }
}

void Log::onMsgError(const char *msg, const char *date)
{
  if (sLevel.isActive(MessageLevel::msg_error)) {
    _write(msg, date);
  }
}

void Log::_write(const char *msg, const char *date)
{
  if (sLogFile.empty()) {
    // Log por defecto
    fs::path logPath(getRunfile());
    logPath.replace_extension(".log");
    sLogFile = logPath.string();
  }
  std::ofstream hLog(sLogFile,std::ofstream::app);
  if (hLog.is_open()) {
    std::lock_guard<std::mutex> lck(Log::mtx);
    hLog << date << " - " << msg << "\n";
    hLog.close();
  } else {
    //Error al abrir/crear archivo. Se saca el error por consola
    printf("The file %s was not opened\n", sLogFile.c_str());
  }
}


#endif // TL_MESSAGE_HANDLER

#ifdef TL_ENABLE_DEPRECATED_METHODS
Log &Log::getInstance()
{
  if (sObjLog.get() == nullptr) {
    std::lock_guard<std::mutex> lck(Log::mtx);
    if (sObjLog.get() == nullptr) {
      sObjLog.reset(new Log());
    }
  }
  return *sObjLog;
}

EnumFlags<MessageLevel> Log::getLogLevel() const
{
  return sLevel;
}
#endif // TL_ENABLE_DEPRECATED_METHODS

} // End mamespace tl

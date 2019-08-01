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

#include "tidop/core/messages.h"

#include "tidop/core/defs.h"
#include "tidop/core/utils.h"

#ifdef HAVE_OPENCV
#include "opencv2/core/utility.hpp"
#endif

#ifdef HAVE_GDAL
TL_SUPPRESS_WARNINGS
#include "gdal_priv.h"
TL_DEFAULT_WARNINGS
#endif // HAVE_GDAL

#include <cstdarg>
#if defined WIN32
# include <windows.h>
#endif
#define __STDC_WANT_LIB_EXT1__ 1
#include <ctime>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <fstream>



namespace tl
{

#ifdef TL_MESSAGE_HANDLER

TL_DISABLE_WARNING(TL_UNREFERENCED_FORMAL_PARAMETER)

#ifdef HAVE_OPENCV
// manejador de error para OpenCV. Para evitar los mensajes por consola de OpenCV
int handleError( int status, const char* func_name, const char* err_msg, const char* file_name, int line, void* userdata )
{
  MessageManager::release(MessageManager::Message(err_msg).message(), MessageLevel::msg_error, file_name, line, func_name);
  return 0;
}

#endif // HAVE_OPENCV

#ifdef HAVE_GDAL
// Manejador de eventos para GDAL 
void handleErrorGDAL(CPLErr err, CPLErrorNum eNum, const char *err_msg) 
{
  MessageLevel ml;
  if (err == CE_Debug) {
    ml = MessageLevel::msg_debug;
  } else if (err == CE_Warning) {
    ml = MessageLevel::msg_warning;
  } else if (err == CE_Failure) {
    ml = MessageLevel::msg_error;
  } else if (err == CE_Fatal) {
    ml = MessageLevel::msg_error;
  } else {
    ml = MessageLevel::msg_info;
  }
  MessageManager::release(MessageManager::Message(err_msg).message(), ml);
  return;
}
#endif // HAVE_GDAL

TL_ENABLE_WARNING(TL_UNREFERENCED_FORMAL_PARAMETER)


static struct _msgProperties _msgTemplate[] = {   
  { "Debug:   %s", "Debug:   %s (%s:%u, %s)"},
  { "Info:    %s", "Info:    %s (%s:%u, %s)"},
  { "Warning: %s", "Warning: %s (%s:%u, %s)"},
  { "Error:   %s", "Error:   %s (%s:%u, %s)"}
};


std::unique_ptr<MessageManager> MessageManager::sObjMessage;
bool MessageManager::sStopHandler = false;
std::mutex MessageManager::sMutex;

std::string MessageManager::Message::sTimeLogFormat = "%d/%b/%Y %H:%M:%S";

MessageManager::MessageManager() 
  : mListeners(0)
{
}

MessageManager::~MessageManager()
{
  sObjMessage.release();
}

MessageManager &MessageManager::instance()
{
  if (sObjMessage.get() == nullptr) {
    std::lock_guard<std::mutex> lck(MessageManager::sMutex);
    if (sObjMessage.get() == nullptr) {
      sObjMessage.reset(new MessageManager());
    }
  }
  return *sObjMessage;
}

void MessageManager::addListener(Listener *listener)
{ 
  // Se comprueba que no este añadido
  bool bAdded = false;
  for (auto l : mListeners) {
    if (l == listener){
      bAdded = true;
      break;
    }
  }
  if (!bAdded)
    mListeners.push_back(listener);
}

///TODO: esto puede que estuviese mejor fuera
void MessageManager::initExternalHandlers()
{
#ifdef HAVE_OPENCV
  cv::redirectError(handleError);
#endif // HAVE_OPENCV

#ifdef HAVE_GDAL
  CPLPushErrorHandler(static_cast<CPLErrorHandler>(handleErrorGDAL));
#endif // HAVE_GDAL
}

void MessageManager::pause()
{
  sStopHandler = true;
}

void MessageManager::release(const char *msg, const MessageLevel &level, const char *file, int line, const char *function)
{
  MessageManager::instance();

  if (sStopHandler) return;

  // Bloqueo aqui para evitar problemas entre hilos
  std::lock_guard<std::mutex> lck(MessageManager::sMutex);

  std::string date = formatTimeToString("%d/%b/%Y %H:%M:%S");

  char buf[1000];
  #if defined _MSC_VER
    if (line == -1)
      sprintf_s(buf, 1000, messageProperties(level).normal, msg, file, line, function);
    else
      sprintf_s(buf, 1000, messageProperties(level).extend, msg, file, line, function);
  #else
    if (line == -1)
      snprintf(buf, 1000, messageProperties(level).normal, msg, file, line, function);
    else
      snprintf(buf, 1000, messageProperties(level).extend, msg, file, line, function);
  #endif

  switch (level) {
  case MessageLevel::msg_debug:
    sObjMessage->onDebug(buf, date.c_str());
    break;
  case MessageLevel::msg_info:
    sObjMessage->onInfo(buf, date.c_str());
    break;
  case MessageLevel::msg_warning:
    sObjMessage->onWarning(buf, date.c_str());
    break;
  case MessageLevel::msg_error:
    sObjMessage->onError(buf, date.c_str());
    break;
  default:
    break;
  }
}

void MessageManager::release(const Message &msg)
{
  MessageManager::instance();
  
  if (sStopHandler) return;

  std::lock_guard<std::mutex> lck(MessageManager::sMutex);
  std::string msg_out;
  if (msg.line() == -1 && strcmp(msg.file(), "") == 0 && strcmp(msg.function(), "") == 0) {
    msg_out = msg.message();
  } else {
    char buf[1000];
#if defined _MSC_VER
    sprintf_s(buf, 1000, "%s (%s:%u, %s)", msg.message(), msg.file(), msg.line(), msg.function());
#else
    snprintf(buf, 1000, "%s (%s:%u, %s)", msg.message(), msg.file(), msg.line(), msg.function());
#endif
    msg_out =  std::string(buf);
  }

  switch (msg.level()) {
  case MessageLevel::msg_debug:
    sObjMessage->onDebug(msg_out.c_str(), msg.date());
    break;
  case MessageLevel::msg_info:
    sObjMessage->onInfo(msg_out.c_str(), msg.date());
    break;
  case MessageLevel::msg_warning:
    sObjMessage->onWarning(msg_out.c_str(), msg.date());
    break;
  case MessageLevel::msg_error:
    sObjMessage->onError(msg_out.c_str(), msg.date());
    break;
  default:
    break;
  }
}

void MessageManager::removeListener(Listener *listener)
{
  if (!mListeners.empty()) {
    mListeners.remove(listener);
  }
}

void MessageManager::resume()
{
  sStopHandler = false;
}

TL_DISABLE_WARNING(TL_UNREFERENCED_FORMAL_PARAMETER)
void MessageManager::onDebug(const char *msg, const char *date)
{
#ifdef _DEBUG
  if (!sStopHandler && !mListeners.empty()) {
    for (auto &lst : mListeners) {
      lst->onMsgDebug(msg, date);
    }
  }
#endif
}
TL_ENABLE_WARNING(TL_UNREFERENCED_FORMAL_PARAMETER)

void MessageManager::onInfo(const char *msg, const char *date)
{
  if (!sStopHandler && !mListeners.empty()) {
    for (auto &lst : mListeners) {
      lst->onMsgInfo(msg, date);
    }
  }
}

void MessageManager::onWarning(const char *msg, const char *date)
{
  if (!sStopHandler && !mListeners.empty()) {
    for (auto &lst : mListeners) {
      lst->onMsgWarning(msg, date);
    }
  }
}

void MessageManager::onError(const char *msg, const char *date)
{
  if (!sStopHandler && !mListeners.empty()) {
    for (auto &lst : mListeners) {
      lst->onMsgError(msg, date);
    }
  }
}

_msgProperties MessageManager::messageProperties(MessageLevel msgLevel)
{
  int iLevel = 0;
  switch (msgLevel) {
  case MessageLevel::msg_debug:
    iLevel = 0;
    break;
  case MessageLevel::msg_info:
    iLevel = 1;
    break;
  case MessageLevel::msg_warning:
    iLevel = 2;
    break;
  case MessageLevel::msg_error:
    iLevel = 3;
    break;
  default:
    iLevel = 3;
    break;
  }
  return _msgTemplate[iLevel];
}

/* ---------------------------------------------------------------------------------- */

MessageManager::Listener::Listener(bool add)
{
  if (add) {
    MessageManager::instance().addListener(this);
  }
}

MessageManager::Listener::~Listener()
{
  MessageManager::instance().removeListener(this);
}

/* ---------------------------------------------------------------------------------- */


MessageManager::Message::Message(const char *msg, ...)
  : mLevel(MessageLevel::msg_error),
    mFile(""), 
    mLine(-1),
    mFunction("")
{
  try {

    mDate = formatTimeToString("%d/%b/%Y %H:%M:%S");

    char buf[500];
    memset(buf, 0, sizeof(buf));
    std::string aux(msg);
    replaceString(&aux, "% ", "%% ");
    replaceString(&aux, "%(\s)", "%%");
    va_list args;
    va_start(args, msg);
#ifdef _MSC_VER
  vsnprintf_s(buf, _countof(buf), _TRUNCATE, aux.c_str(), args);
#else
  vsnprintf(buf, sizeof(buf), aux.c_str(), args);
#endif
    va_end(args);
    mMessage = buf;
  } catch (...) {

    // Por evitar un error en la constructora... 
  }
}

const char *MessageManager::Message::date() const
{
  return mDate.c_str();
}

const char *MessageManager::Message::file() const
{
  return mFile.c_str();
}

const char *MessageManager::Message::function() const
{
  return mFunction.c_str();
}

MessageLevel MessageManager::Message::level() const
{
  return mLevel;
}

int MessageManager::Message::line() const
{
  return mLine;
}

const char *MessageManager::Message::message() const
{
  return mMessage.c_str();
}

void MessageManager::Message::setTimeLogFormat( const char *timeTemplate)
{
  sTimeLogFormat = timeTemplate;
}

void MessageManager::Message::setMessageLevel(const MessageLevel &level)
{
  mLevel = level;
}
    
void MessageManager::Message::setMessageProperties(const MessageLevel &level, const char *file, int line, const char *function)
{
  mLevel = level;
  mLine = line;
  mFile = file;
  mFunction = function;
}

#endif  // TL_MESSAGE_HANDLER

#ifdef TL_ENABLE_DEPRECATED_METHODS

MessageManager &MessageManager::getInstance()
{
  if (sObjMessage.get() == nullptr) {
    std::lock_guard<std::mutex> lck(MessageManager::sMutex);
    if (sObjMessage.get() == nullptr) {
      sObjMessage.reset(new MessageManager());
    }
  }
  return *sObjMessage;
}

const char *MessageManager::Message::getDate() const
{
  return mDate.c_str();
}

const char *MessageManager::Message::getFile() const
{
  return mFile.c_str();
}

const char *MessageManager::Message::getFunction() const
{
  return mFunction.c_str();
}

MessageLevel MessageManager::Message::getLevel() const
{
  return mLevel;
}

int MessageManager::Message::getLine() const
{
  return mLine;
}

const char *MessageManager::Message::getMessage() const
{
  return mMessage.c_str();
}
#endif // TL_ENABLE_DEPRECATED_METHODS

} // End mamespace tl

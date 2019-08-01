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

#ifndef TL_CORE_EXCEPTION_H
#define TL_CORE_EXCEPTION_H

#include "config_tl.h"

#include <exception>
#include <string>

#include "tidop/core/defs.h"
#include "tidop/core/messages.h"

namespace tl
{

/*!
 * Clase para el manejo de excepciones
 */
class TL_EXPORT Exception
  : public std::exception
{
protected:

  /*!
   * \brief Error
   */
  std::string mError;

  /*!
   * \brief Fichero en el cual se ha producido el error
   */
  std::string mFile;

  /*!
   * \brief Número de línea donde se ha producido el error
   */
  int mLine;

  /*!
   * \brief Nombre de la función donde se ha producido el error
   */
  std::string mFunction;

  /*!
   * \brief Mensaje de error
   */
  std::string mMessage;

public:

#ifdef TL_ENABLE_DEPRECATED_METHODS
  /*!
   * \brief Constructor
   * \deprecated Usar Exception(const std::string &error)
   */
  TL_DEPRECATED("Exception::Exception(const std::string &error)", "2.0")
  explicit Exception(const char *error);

  /*!
   * \brief Constructor
   */
  TL_DEPRECATED("Exception::Exception(const std::string &error)", "2.0")
  explicit Exception(const char *error, const char *file, int line, const char *function);

#endif

  /*!
   * \brief Constructor
   */
  explicit Exception(const std::string &error);

  /*!
   * \brief Constructor
   */
  explicit Exception(const std::string &error, const std::string &file, int line, const std::string &function);

  /*!
   * \brief destructor
   */
  virtual ~Exception() TL_NOEXCEPT override {}

  /*!
   * \brief Descripción del error
   */
  virtual const char *what() const TL_NOEXCEPT override;

  std::string file() const;
  std::string function() const;
  int line() const;

private:

  void messagef();
};

//TL_EXPORT void throw_exception(const char *error, const char *file = nullptr, int line = -1, const char *function = nullptr);
TL_EXPORT Exception make_exception(const char *error, const char *file = nullptr, int line= -1, const char *function = nullptr);



#ifdef WIN32

/*!
 * \brief formatWindowsErrorMsg
 */
TL_EXPORT std::string formatWindowsErrorMsg(DWORD errorCode);

#endif


#ifdef TL_MESSAGE_HANDLER
#ifdef _DEBUG
#define TL_ERROR(...) make_exception(MessageManager::Message(__VA_ARGS__).message(), __FILE__, __LINE__, TL_FUNCTION)
#define TL_THROW_ERROR(...) throw make_exception(MessageManager::Message(__VA_ARGS__).message(), __FILE__, __LINE__, TL_FUNCTION)

//https://www.softwariness.com/articles/assertions-in-cpp/
//#define TL_THROW_ASSERT(EXPRESSION, ...) if(!(EXPRESSION)) { throw Exception(#EXPRESSION MessageManager::Message(__VA_ARGS__).getMessage(), __FILE__, __LINE__, TL_FUNCTION); }
#define TL_THROW_ASSERT(EXPRESSION, MESSAGE) if(!(EXPRESSION)) { TL_THROW_ERROR( "Assertion '" #EXPRESSION "' " MESSAGE); }

#else
#define TL_ERROR(...) make_exception(MessageManager::Message(__VA_ARGS__).message())
#define TL_THROW_ERROR(...) throw make_exception(MessageManager::Message(__VA_ARGS__).message())

//https://www.softwariness.com/articles/assertions-in-cpp/
#define TL_THROW_ASSERT(EXPRESSION, MESSAGE) if(!(EXPRESSION)) { TL_THROW_ERROR(#EXPRESSION MESSAGE); }

#endif
#else  // End TL_MESSAGE_HANDLER

#define TL_ERROR(...)
#define TL_THROW_ERROR(...)
#define TL_THROW_ASSERT(EXPRESSION, MESSAGE)

#endif

} // fin namespace tl

#endif // TL_CORE_EXCEPTION_H

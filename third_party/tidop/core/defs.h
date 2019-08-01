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

/* Archivo para definir macros y constantes de tipo general */

#ifndef TL_CORE_DEFS_H
#define TL_CORE_DEFS_H

#include "config_tl.h"

#include <limits>
#include <cstdlib>

#ifdef __GNUC__
#include <cstdio>
#endif // __GNUC__

#ifdef HAVE_VLD
#ifdef VISUAL_LEAK_DETECTOR
#include <vld.h>
#endif
#endif // HAVE_VLD


#if defined _MSC_VER && _MSC_VER < 1600

//Copiado de stdint.h. Las versiones antiguas de Visual Studio no incluyen stdint.h
  typedef signed char        int8_t;
  typedef short              int16_t;
  typedef int                int32_t;
  typedef long long          int64_t;
  typedef unsigned char      uint8_t;
  typedef unsigned short     uint16_t;
  typedef unsigned int       uint32_t;
  typedef unsigned long long uint64_t;
#else
  #include <cstdint>
#endif

#if defined WIN32
// Para que no den problemas std::numeric_limits<T>().max()
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif
#  ifdef HAVE_RAW
#    include <Winsock2.h> // Necesario para libraw. Incluir antes de windows.h por que si no da error
#  endif
#  include <windows.h>
#endif

/* Definición de constantes de tipo general */

#define TL_PI_2 1.5707963267948966192313216916398
#define TL_PI   3.1415926535897932384626433832795
#define TL_2PI  6.283185307179586476925286766559


/* Conversión de ángulos */

#define TL_RAD_TO_DEG	57.295779513082320876798154814105
#define TL_DEG_TO_RAD	0.01745329251994329576923690768489
#define TL_RAD_TO_GRAD	63.661977236758134307553505349006
#define TL_GRAD_TO_RAD	0.0157079632679489661923132169164


/* Límites maximos y minimos de tipos numéricos */

#define TL_INT_MAX std::numeric_limits<int>().max()
#define TL_INT_MIN -std::numeric_limits<int>().max()
#define TL_DOUBLE_MAX std::numeric_limits<double>().max()
#define TL_DOUBLE_MIN -std::numeric_limits<double>().max()
#define TL_FLOAT_MAX std::numeric_limits<float>().max()
#define TL_FLOAT_MIN -std::numeric_limits<float>().max()



#if defined WIN32 || defined _WIN32
#  ifdef _MSC_VER
#    define TL_MAX_PATH   _MAX_PATH
#    define TL_MAX_DRIVE  _MAX_DRIVE
#    define TL_MAX_DIR    _MAX_DIR
#    define TL_MAX_FNAME  _MAX_FNAME
#    define TL_MAX_EXT    _MAX_EXT
#  else //__GNUC__ No encuentra _MAX_DRIVE, _MAX_DIR, _MAX_FNAME y _MAX_EXT
#    ifdef __GNUC__
#      define TL_MAX_PATH   MAX_PATH
#    else
#      define TL_MAX_PATH  260
#    endif
#    define TL_MAX_DRIVE  3
#    define TL_MAX_DIR    256
#    define TL_MAX_FNAME  256
#    define TL_MAX_EXT    256
#  endif
#else
#  include <linux/limits.h>
#  define TL_MAX_PATH   PATH_MAX
#  define TL_MAX_FNAME  NAME_MAX
#  define TL_MAX_DRIVE  PATH_MAX
#  define TL_MAX_DIR    PATH_MAX
#  define TL_MAX_EXT    NAME_MAX
#endif



#ifdef TIDOPLIB_EXPORTS
#  if (defined WIN32 || defined _WIN32 || defined WINCE || defined __CYGWIN__)
#    define TL_EXPORT __declspec(dllexport)
#  elif defined __GNUC__ && __GNUC__ >= 4
#    define TL_EXPORT __attribute__ ((visibility ("default")))
#  endif
#else
#  define TL_EXPORT
#endif



#ifndef TL_EXTERN_C
#  ifdef __cplusplus
#    define TL_EXTERN_C extern "C"
#  else
#    define TL_EXTERN_C
#  endif
#endif



/*!
 * \brief Warning para informar que una función esta obsoleta
 * Se debe anteceder a la función obsoleta añadiendo el método que lo reemplaza:
 *
 * TL_DEPRECATED("newFunc(int a, float b)", "2.0")
 * void oldFunc(int a, float b);
 *
 * En el caso de una clase o un enum se debe añadir entre class y el nombre de la clase:
 *
 * class TL_DEPRECATED(NewClass, "2.0") OldClass
 * { ...
 *
 * En el caso de las funciones template:
 *
 * template<typename T> inline
 * TL_DEPRECATED("void newFunc(T a, T b)", "2.0")
 * void oldFunc(T a, T b);
 */
//#if __cplusplus >= 201402L // c++ 14
//#  define TL_DEPRECATED(msg)  [[deprecated("Use " msg " instead")]]
//#else
#  ifdef __GNUC__
#    define TL_DEPRECATED(msg, version) __attribute__((deprecated(version " Use " msg " instead")))
#  elif defined _MSC_VER
#    define TL_DEPRECATED(msg, version) __declspec(deprecated("Deprecated in version " version ": use " msg " instead"))
#  else
#    pragma message("WARNING: You need to implement DEPRECATED for this compiler")
#    define TL_DEPRECATED(msg, version)
#  endif
//#endif



// Mensajes de error y warning para mostrar al compilar

#define STRING2(x) #x
#define STRING(x) STRING2(x)

#ifdef __GNUC__
#define MAKE_LINUX_PRAGMA(x) _Pragma (#x)
#endif

#ifdef _MSC_VER
#  define TL_COMPILER_WARNING(msg) __pragma(message( __FILE__ "(" STRING(__LINE__) "): warning(TIDOPLIB): " msg  ) )
#else
// Ver si funciona _Pragma()... Da los errores:
// /home/esteban/desarrollo/tidoplib/src/transform.h:331: error: _Pragma takes a parenthesized string literal
// TL_COMPILER_WARNING("'compute' no esta soportado para TrfMultiple");
//                                                                   ^
// /home/esteban/desarrollo/tidoplib/src/core/defs.h:102: error: there are no arguments to '_Pragma' that depend on a template parameter, so a declaration of '_Pragma' must be available [-fpermissive]
//  #  define TL_COMPILER_WARNING(msg) _Pragma(message( __FILE__ "(" STRING(__LINE__) "): warning(TIDOPLIB): " msg  ) )
//                                                                                                                   ^
// Por ahora no hace nada...
#  define LINUX_PRAGMA(x) MAKE_LINUX_PRAGMA(x)
#  define TL_COMPILER_WARNING(msg) LINUX_PRAGMA(message( __FILE__ "(" STRING(__LINE__) "): warning(TIDOPLIB): " msg  ) )
#endif



// __FUNCTION__ no es estandar (Es de Visual Studio).
// __func__ es valida a partir de C99 / C++11
#if defined (__GNUC__) || __cplusplus >= 201103L
#  define TL_FUNCTION __func__
#elif defined _MSC_VER
#  define TL_FUNCTION __FUNCTION__
#else
#  define TL_FUNCTION ""
#endif
//__FUNCSIG__

// noexcept es valida a partir de C++11. Visual Studio 2013 no cumple todo C++11

#if __cplusplus >= 201103L
#  define TL_NOEXCEPT noexcept
#  define TL_NOEXCEPT_OP(x) noexcept((x))
#else
#  define TL_NOEXCEPT throw ()
#  define TL_NOEXCEPT_OP(x)
#endif

/*-----------------------------------------------------------------------------------*/
/*                                       WARNIGS                                     */
/*-----------------------------------------------------------------------------------*/

#ifdef _MSC_VER
#  define TL_WARNING_DEPRECATED 4996
#  define TL_UNREFERENCED_FORMAL_PARAMETER 4100
#  define TL_UNREFERENCED_LOCAL_VARIABLE 4101
#  define TL_WARNING_C4244 4244
#  define TL_FORCEINLINE_NOT_INLINED 4714
#else
#  define TL_WARNING_DEPRECATED "-Wdeprecated-declarations"
#  define TL_UNREFERENCED_FORMAL_PARAMETER "-Wunused-variable"
#  define TL_UNREFERENCED_LOCAL_VARIABLE "-Wunused-variable"
#  define TL_WARNING_C4244 "-W"
#  define TL_FORCEINLINE_NOT_INLINED 4714 "-W"
#endif



/*!
 * \brief Se suprimen todos los mensajes de advertencia
 *
 * <h4>Ejemplo</h4>
 * \code
 * TL_SUPPRESS_WARNINGS
 * bool f(int v) {      // warning C4100: 'v' : parámetro formal sin referencia
 *   int b = 0;         // warning C4189: 'b' : la variable local se ha inicializado pero no se hace referencia a ella
 *   double d = 1.0;
 *   float f = d;       // warning C4244: '=' : conversión de 'double' a 'float'; posible pérdida de datos
 *   return true;
 * }
 * \endcode
 */
#ifdef _MSC_VER
#  define TL_SUPPRESS_WARNINGS __pragma(warning(push, 0))
#else
#  define TL_SUPPRESS_WARNINGS DIAG_PRAGMA(push) DIAG_PRAGMA(ignored "-Wall")
#endif

/*!
 * \brief Se pone por defecto la configuración de mensajes de advertencia
 */
#ifdef _MSC_VER
#  define TL_DEFAULT_WARNINGS __pragma(warning(pop))
#else
#  define DIAG_DO_PRAGMA(x) _Pragma (#x)
#  define DIAG_PRAGMA(x) DIAG_DO_PRAGMA(GCC diagnostic x)
#  define TL_DEFAULT_WARNINGS DIAG_PRAGMA(pop)
#endif

/*!
 * \brief Se activa un mensaje de advertencia especifico
 *
 * <h4>Ejemplo</h4>
 * \code
 * TL_DISABLE_WARNING(4244)
 * bool f(double d) {
 *   float f = d;       // warning C4244: '=' : conversión de 'double' a 'float'; posible pérdida de datos
 *   return true;
 * }
 * TL_ENABLE_WARNING(4244)
 * \endcode
 */
#ifdef _MSC_VER
#  define TL_DISABLE_WARNING(warn) __pragma(warning(disable : warn))
#else
#  define DIAG_DO_PRAGMA(x) _Pragma (#x)
#  define DIAG_PRAGMA(x) DIAG_DO_PRAGMA(GCC diagnostic x)
#  define TL_DISABLE_WARNING(warn) DIAG_PRAGMA(push) DIAG_PRAGMA(ignored warn)
//#  define TL_DISABLE_WARNING(warn) _Pragma GCC diagnostic push \
//   _Pragma GCC diagnostic ignored warn
#endif

/*!
 * \brief Se desactiva un mensaje de advertencia especifico
 *
 * <h4>Ejemplo</h4>
 * \code
 * TL_DISABLE_WARNING(4244)
 * bool f(double d) {
 *   float f = d;       // warning C4244: '=' : conversión de 'double' a 'float'; posible pérdida de datos
 *   return true;
 * }
 * TL_ENABLE_WARNING(4244)
 * \endcode
 */
#ifdef _MSC_VER
#  define TL_ENABLE_WARNING(warn) __pragma(warning(default : warn))
#else
#  define DIAG_DO_PRAGMA(x) _Pragma (#x)
#  define DIAG_PRAGMA(x) DIAG_DO_PRAGMA(GCC diagnostic x)
#  define TL_ENABLE_WARNING(warn) DIAG_PRAGMA(pop)
#endif

/*-----------------------------------------------------------------------------------*/
/*                                       MACROS                                      */
/*-----------------------------------------------------------------------------------*/

/*!
 * \brief Redondea un doble o float y ademas convierte a entero
 * De esta forma se evita el warning C4244 (conversión de 'double' a 'int')
 * y nos aseguramos de que redondee de la forma correcta.
 */
#define TL_ROUND_TO_INT(n)  static_cast<int>(round(n))

#ifndef _MSC_VER
//En el compilador de LINUX no incluye printf_s de C++11
// De momento lo hago asi...
#define printf_s(...) printf( __VA_ARGS__)
#define sprintf_s(dest, len, format, ...) snprintf(dest, len, format, __VA_ARGS__) 
#endif

#ifndef _MSC_VER
#  define DO_PRAGMA(x) _Pragma (#x)
#  define TL_TODO(x) DO_PRAGMA(message ("TODO: " #x))
#else
#  define TL_TODO(msg) __pragma(message( __FILE__ "(" STRING(__LINE__) "): TODO(TidopLib): " msg  ) )
#endif

#endif // TL_CORE_DEFS_H

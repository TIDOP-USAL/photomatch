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

#ifndef TL_CORE_FLAGS_H
#define TL_CORE_FLAGS_H

#include "config_tl.h"

#include "tidop/core/defs.h"

#include <type_traits>
#include <utility>

namespace tl
{

/*!
 * \brief Clase Flag de enums
 *
 * Esta clase permite utilizar un enum como flag en el caso de declarar la
 * enumeración como 'enum class'.
 *
 * Ejemplo de uso:
 * \code
 * enum class ePrueba : int8_t {
 *  flag_0 = (0 << 0),
 *  flag_1 = (1 << 0),
 *  flag_2 = (1 << 1),
 *  flag_3 = (1 << 2),
 *  flag_4 = (1 << 3),
 *  flag_5 = (1 << 4),
 *  flag_6 = (1 << 5),
 *  flag_7 = (1 << 6)
 * };
 *
 * int main(int argc, char *argv[])
 * {
 *
 *   EnumFlags<ePrueba> flag(ePrueba::flag_1);
 *
 *   // Comprueba si el flag esta activo
 *   bool bActive = flag.isActive(ePrueba::flag_1);
 *
 *   // Activa un flag
 *   flag2.flagOn(ePrueba::flag_3);
 *
 *   // Desactiva un flag
 *   flag2.flagOff(ePrueba::flag_1);
 *
 *   // Invierte un flag
 *   flag2.switchFlag(ePrueba::flag_5);
 *
 *   // Pueden combinarse los enums
 *   EnumFlags<ePrueba> flag2;
 *   flag2 = ePrueba::flag_3 | ePrueba::flag_4;
 *
 *   return 0;
 * }
 *
 * \endcode
 */
template<typename T>
class EnumFlags
{

public:

  /*!
   * \brief Tipo de la enumeración
   */
  typedef typename std::underlying_type<T>::type Type; 

private:

  /*!
   * \brief mFlag
   */
  Type mFlag;

public:

  /*!
   * \brief Constructora por defecto
   */
  EnumFlags();

  /*!
   * \brief Constructora de copia
   * \param[in] flag
   */
  EnumFlags(const EnumFlags<T> &flag);
 
  /*!
   * \brief Constructora de movimiento
   * \param[in] flag
   */
  EnumFlags(EnumFlags<T> &&flag) TL_NOEXCEPT;

  /*!
   * \brief Constructora
   * \param[in] flag
   */
  EnumFlags(T flag);

  /*!
   * \brief Destructora
   */
  ~EnumFlags();

  /*!
   * \brief Operador asignación
   * \param[in] flag Objeto EnumFlags
   * \return Referencia al objeto EnumFlags
   */
  EnumFlags<T> &operator = (const EnumFlags<T> &flag);

  /*!
   * \brief Operador asignación de movimiento
   * \param[in] flag Objeto EnumFlags
   * \return Referencia al objeto EnumFlags
   */
  EnumFlags<T> &operator = (EnumFlags<T> &&flag) TL_NOEXCEPT;

  /*!
   * \brief Operador asignación enumeración
   * \param[in] flag enumeracion o unión de ellas
   * \return Referencia al objeto EnumFlags
   */
  EnumFlags<T> &operator = (T flag);

  /*!
   * \brief Comprueba si el flag esta activo
   * \param[in] flag Flag que se comprueba
   * \return Verdadero si esta activo y falso en caso contrario.
   */
  bool isActive(T flag) const;

  /*!
   * \brief Activa un flag
   * \param[in] flag Flag que se activa
   */
  void flagOn(T flag);

  /*!
   * \brief Desactiva un flag
   * \param[in] flag Flag que se desactiva
   */
  void flagOff(T flag);

  /*!
   * \brief Activa o desactiva un flag
   * \param[in] flag Flag que se desactiva
   * \param[in] active Verdadero para activar el flag
   */
  void activeFlag(T flag, bool active);

  /*!
   * \brief Invierte un flag
   * \param[in] flag Flag que se invierte
   */
  void switchFlag(T flag);

  /*!
   * \brief Pone a cero todos los flags
   */
  void clear();

#ifdef TL_ENABLE_DEPRECATED_METHODS
  /*!
   * \brief Devuelve los flags
   * \return
   * \deprecated Use 'flags()' en su lugar 
   */
  TL_DEPRECATED("EnumFlags::flags", "2.0")
  T getFlags() const;
#endif // TL_ENABLE_DEPRECATED_METHODS
   
  /*!
   * \brief Devuelve los flags
   * \return
   */
  T flags() const;
};

template<typename T> inline
EnumFlags<T>::EnumFlags() 
  : mFlag(0) 
{
}

template<typename T> inline
EnumFlags<T>::EnumFlags(const EnumFlags<T> &flag)
  : mFlag(flag.mFlag) 
{

}

template<typename T> inline
EnumFlags<T>::EnumFlags(EnumFlags<T> &&flag) TL_NOEXCEPT
  : mFlag(std::move(flag.mFlag)) 
{

}


template<typename T> inline
EnumFlags<T>::EnumFlags(T flag) 
  : mFlag(static_cast<Type>(flag))
{
}

template<typename T> inline
EnumFlags<T>::~EnumFlags()
{
}

template<typename T> inline
EnumFlags<T> &EnumFlags<T>::operator = (const EnumFlags<T> &flag)
{
  if (this != &flag) {
    this->mFlag = flag.mFlag;
  }
  return *this;
}

template<typename T> inline
EnumFlags<T> &EnumFlags<T>::operator = (EnumFlags<T> &&flag) TL_NOEXCEPT
{
  if (this != &flag) {
    this->mFlag = std::move(flag.mFlag);
  }
  return *this;
}

template<typename T> inline
EnumFlags<T> &EnumFlags<T>::operator = (T flag)
{
  mFlag = static_cast<Type>(flag);
  return *this;
}

template<typename T> inline
bool EnumFlags<T>::isActive(T flag) const
{
  return 0 != (mFlag & static_cast<Type>(flag) );
}

template<typename T> inline
void EnumFlags<T>::flagOn(T flag)
{
  mFlag |= static_cast<Type>(flag);
}

template<typename T> inline
void EnumFlags<T>::flagOff(T flag)
{
  mFlag &= ~static_cast<Type>(flag);
}

template<typename T> inline
void EnumFlags<T>::activeFlag(T flag, bool active)
{
  if (active) flagOn(flag);
  else flagOff(flag);
}

template<typename T> inline
void EnumFlags<T>::switchFlag(T flag)
{
  if ( isActive(flag) ) flagOff(flag);
  else flagOn(flag);
}

template<typename T> inline
void EnumFlags<T>::clear()
{
  mFlag = static_cast<Type>(0);
}

#ifdef TL_ENABLE_DEPRECATED_METHODS
template<typename T> inline
T EnumFlags<T>::getFlags() const
{
  return static_cast<T> (mFlag);
}
#endif // TL_ENABLE_DEPRECATED_METHODS

template<typename T> inline
T EnumFlags<T>::flags() const
{
  return static_cast<T> (mFlag);
}



/*!
 * \brief Permite operaciones a nivel de bit con un 'enum class'
 *
 * Debe añadirse debajo de la declaración del enum
 *
 * \code
 * enum class ePrueba : int8_t {
 *  flag01 = (1 << 0),
 *  flag02 = (1 << 1),
 *  flag03 = (1 << 2),
 *  flag04 = (1 << 3),
 *  flag05 = (1 << 4),
 *  flag06 = (1 << 5),
 *  flag07 = (1 << 6)
 * };
 *
 * ALLOW_BITWISE_FLAG_OPERATIONS(ePrueba)
 *
 * \endcode
 */
#define ALLOW_BITWISE_FLAG_OPERATIONS(T_FLAG)                       \
inline T_FLAG operator | (T_FLAG flag1, T_FLAG flag2)               \
{                                                                   \
  return static_cast<T_FLAG> (                                      \
    static_cast<std::underlying_type<T_FLAG>::type>(flag1) |        \
    static_cast<std::underlying_type<T_FLAG>::type>(flag2)          \
  );                                                                \
}                                                                   \
                                                                    \
inline T_FLAG operator & (T_FLAG flag1, T_FLAG flag2)               \
{                                                                   \
  return static_cast<T_FLAG> (                                      \
    static_cast<std::underlying_type<T_FLAG>::type>(flag1) &        \
    static_cast<std::underlying_type<T_FLAG>::type>(flag2)          \
  );                                                                \
}                                                                   \
                                                                    \
inline T_FLAG operator ^ (T_FLAG flag1, T_FLAG flag2)               \
{                                                                   \
  return static_cast<T_FLAG> (                                      \
    static_cast<std::underlying_type<T_FLAG>::type>(flag1) ^        \
    static_cast<std::underlying_type<T_FLAG>::type>(flag2)          \
  );                                                                \
}                                                                   \
                                                                    \
inline T_FLAG operator ~ (T_FLAG flag)                              \
{                                                                   \
  return static_cast<T_FLAG> (                                      \
    ~static_cast<std::underlying_type<T_FLAG>::type>(flag)          \
  );                                                                \
}


template<typename T>
class Flags
{

public:

  /*!
   * \brief Tipo del flag
   */
  typedef T Type; 

private:

  /*!
   * \brief mFlag
   */
  Type mFlag;

public:

  /*!
   * \brief Constructora por defecto
   */
  Flags() : mFlag(0) {}

  /*!
   * \brief Constructora de copia
   */
  Flags(const Flags &flag);

  /*!
   * \brief Constructora de lista
   * \param[in] flags listado de flags activos
   */
  Flags(std::initializer_list<int> flags);

  /*!
   * \brief Destructora
   */
  ~Flags();

  /*!
   * \brief Operador asignación
   * \param flag enumeracion o unión de ellas
   * \return Referencia al objeto EnumFlags
   */
  Flags &operator = (const Flags<T> &flag);

  /*!
   * \brief Comprueba si el flag esta activo
   * \param flag Flag que se comprueba
   * \return Verdadero si esta activo y falso en caso contrario.
   */
  bool isActive(int flag) const;

  /*!
   * \brief Activa un flag
   * \param flag Flag que se activa
   */
  void flagOn(int flag);

  /*!
   * \brief Desactiva un flag
   * \param flag Flag que se desactiva
   */
  void flagOff(int flag);

  /*!
   * \brief Invierte un flag
   * \param flag Flag que se invierte
   */
  void switchFlag(int flag);

  /*!
   * \brief Pone a cero todos los flags
   */
  void clear();

#ifdef TL_ENABLE_DEPRECATED_METHODS
  /*!
   * \brief Devuelve los flags
   * \return
   * \deprecated Use 'flags()' en su lugar 
   */
  TL_DEPRECATED("Flags::flags", "2.0")
  T getFlags() const;
#endif // TL_ENABLE_DEPRECATED_METHODS
   
  /*!
   * \brief Devuelve los flags
   * \return
   */
  T flags() const;
};

/* Definición de tipos */

typedef Flags<uint8_t> Flags_8;
typedef Flags<uint16_t> Flags_16;
typedef Flags<uint32_t> Flags_32;
typedef Flags<uint64_t> Flags_64;


template<typename T> inline
Flags<T>::Flags(const Flags &flag) 
  : mFlag(flag.mFlag)
{
}

template<typename T> inline
Flags<T>::Flags(std::initializer_list<int> flags)
{
  for (auto flg : flags) {
    mFlag |= static_cast<Type>(1 << flg);
  }
}

template<typename T> inline
Flags<T>::~Flags()
{
}

template<typename T> inline
Flags<T> &Flags<T>::operator = (const Flags<T> &flag)
{
  if (this != &flag) {
    mFlag = flag.mFlag;
  }
  return *this;
}

template<typename T> inline
bool Flags<T>::isActive(int flag) const
{
  return 0 != (mFlag & static_cast<Type>(1 << flag) );
}

template<typename T> inline
void Flags<T>::flagOn(int flag)
{
  mFlag |= static_cast<Type>(1 << flag);
}

template<typename T> inline
void Flags<T>::flagOff(int flag)
{
  mFlag &= ~static_cast<Type>(1 << flag);
}

template<typename T> inline
void Flags<T>::switchFlag(int flag)
{
  if ( isActive(flag) ) flagOff(flag);
  else flagOn(flag);
}

template<typename T> inline
void Flags<T>::clear()
{
  mFlag = static_cast<Type>(0);
}

#ifdef TL_ENABLE_DEPRECATED_METHODS
template<typename T> inline
T Flags<T>::getFlags() const
{
  return static_cast<T> (mFlag);
}
#endif // TL_ENABLE_DEPRECATED_METHODS

template<typename T> inline
T Flags<T>::flags() const
{
  return static_cast<T> (mFlag);
}

} // End namespace tl

#endif // TL_CORE_FLAGS_H

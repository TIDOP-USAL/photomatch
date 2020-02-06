/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#ifndef PHOTOMATCH_IMAGE_H
#define PHOTOMATCH_IMAGE_H

#include "photomatch/photomatch_global.h"

#include <QString>

namespace photomatch
{

class PHOTOMATCH_EXPORT Image
{
public:

  /*!
   * \brief Constructor Image por defecto
   */
  Image();

  /*!
   * \brief Constructor Image
   * \param[in] file Fichero imagen
   */
  Image(const QString &file);

  /*!
   * \brief Constructor de copia Image
   * \param[in] image Objeto que se copia
   */
  Image(const Image &image);

  /*!
   * \brief Constructor de movimiento Image
   * \param[in] image Objeto que se copia
   */
  Image(Image &&image) noexcept;

  /*!
   * \brief Destructor Image
   */
  ~Image() = default;

  /*!
   * \brief Devuelve la ruta del fichero imagen
   * \return Ruta del fichero
   */
  QString path() const;

  /*!
   * \brief Establece la ruta del fichero imagen
   * \param[in] file Ruta del fichero
   */
  void setPath(const QString &file);

  /*!
   * \brief Nombre del fichero
   * \return Nombre del fichero
   */
  QString name() const;

  /*!
   * \brief longitudeExif
   * \return
   */
  double longitudeExif() const;

  /*!
   * \brief setLongitudeExif
   * \param longitudeExif
   */
  void setLongitudeExif(double longitudeExif);

  /*!
   * \brief latitudeExif
   * \return
   */
  double latitudeExif() const;

  /*!
   * \brief setLatitudeExif
   * \param latitudeExif
   */
  void setLatitudeExif(double latitudeExif);

  /*!
   * \brief altitudeExif
   * \return
   */
  double altitudeExif() const;

  /*!
   * \brief setAltitudeExif
   * \param altitudeExif
   */
  void setAltitudeExif(double altitudeExif);

  /*!
   * \brief Operador de asignación
   * \param[in] image Objeto que se asigna
   * \return Referencia al objeto Image
   */
  Image &operator =(const Image &image);

  /*!
   * \brief Operador de asignación de movimiento
   * \param[in] image Objeto que se mueve
   * \return Referencia al objeto Image
   */
  Image &operator =(Image &&image) noexcept;

private:

  void update();

protected:

  QString mFilePath;
  QString mName;
  double mLongitudeExif;
  double mLatitudeExif;
  double mAltitudeExif;

};

} // namespace photomatch

#endif // PHOTOMATCH_IMAGE_H

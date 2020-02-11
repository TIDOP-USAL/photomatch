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


#ifndef MAINWINDOWMODEL_H
#define MAINWINDOWMODEL_H

#include "mvp.h"

namespace photomatch
{

class IProjectModel;

class MainWindowModel
  : public IModel
{
  Q_OBJECT

public:

  explicit MainWindowModel();

  /*!
   * \brief Devuelve la ruta por defecto donde se situan los proyectos
   * \return
   */
  QString defaultPath() const;

  std::list<std::pair<QString, QString>> exif(const QString &image) const;

  std::vector<QPointF> loadKeyPointsCoordinates(const QString &file) const;
  std::vector<std::tuple<QPointF, double, double>> loadKeyPoints(const QString &file) const;
  std::vector<std::pair<QPointF, QPointF>> loadMatches(const QString &fileMatches,
                                                       const QString &fileKeyPoints1,
                                                       const QString &fileKeyPoints2) const;
  void exportTiePointsCvXml(const QString &dir);

signals:

public slots:


// IModel interface

private:

  void init() override;

protected:

  QString mPrjDefaultPath;
};

} // namespace photomatch

#endif // MAINWINDOWMODEL_H

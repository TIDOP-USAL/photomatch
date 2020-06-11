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

#ifndef PHOTOMATCH_REPEATABILITY_INTERFACES_H
#define PHOTOMATCH_REPEATABILITY_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class RepeatabilityModel
  : public PhotoMatchModel
{

  Q_OBJECT

public:

  RepeatabilityModel(){}
  virtual ~RepeatabilityModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::tuple<QString, QString, QString>> sessions() const = 0;
  virtual std::vector<std::tuple<QString, QString, QString, float, int>> computeRepeatability(const QString &session/*, const QString &imgLeft, const QString &imgRight*/) const = 0;

};



class RepeatabilityView
  : public PhotoMatchDialogView
{

  Q_OBJECT

public:

  RepeatabilityView(QWidget *parent = nullptr,
                    Qt::WindowFlags f = Qt::WindowFlags())
    : PhotoMatchDialogView(parent, f)
  {}

  virtual ~RepeatabilityView() override = default;

  /*!
   * \brief Add a session
   * \param[in] session Session
   */
  virtual void addSession(const QString &session, const QString &detector, const QString &descriptor) = 0;

  /*!
   * \brief setRepeteability
   * \param repeteability
   */
  virtual void setRepeatability(const std::vector<std::tuple<QString, QString, QString, float, int>> &repeatability) = 0;

signals:

  void selectSession(QString);

};



class RepeatabilityPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  RepeatabilityPresenter() : PhotoMatchPresenter() {}
  virtual ~RepeatabilityPresenter() override {}

protected slots:

  virtual void selectSession(const QString &session) = 0;
};


} // namespace photomatch

#endif // PHOTOMATCH_REPEATABILITY_INTERFACES_H

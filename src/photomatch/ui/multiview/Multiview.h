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

#ifndef PHOTOMATCH_MULTIVIEW_INTERFACES_H
#define PHOTOMATCH_MULTIVIEW_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class MultiViewMatchingAssessmentModel
  : public PhotoMatchModel
{

  Q_OBJECT

public:

  MultiViewMatchingAssessmentModel(){}
  virtual ~MultiViewMatchingAssessmentModel() override {}

  virtual QString sessionName() const = 0;
  virtual void setSessionName(const QString &session) = 0;
  virtual void loadPassPoints() = 0;
  virtual std::vector<size_t> passPointIds() const = 0;
  virtual std::vector<std::pair<size_t, size_t>> passPointIdsAndSize() const = 0;
  virtual std::vector<std::pair<QString, QPointF>> images(size_t passPointId) const = 0;
};


class MultiviewMatchingAssessmentView
  : public PhotoMatchDialogView
{

Q_OBJECT

public:

  MultiviewMatchingAssessmentView(QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags())
  : PhotoMatchDialogView(parent, f) {}
  virtual ~MultiviewMatchingAssessmentView() = default;

  virtual void setSessionName(const QString &name) = 0;
  virtual void setPassPointIds(const std::vector<size_t> &id) = 0;
  virtual void addPassPointIds(size_t id) = 0;
  virtual void addPassPointIdsAndNImages(size_t id, size_t size) = 0;
  //virtual void setImages(const QStringList &images) = 0;
  //virtual void setImages(const std::vector<QPixmap> &images) = 0;
  virtual void setImages(const std::vector<std::pair<QString, QPointF>> &images) = 0;

signals:

  void idChange(int);
};


class MultiViewMatchingAssessmentPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  MultiViewMatchingAssessmentPresenter(){}
  virtual ~MultiViewMatchingAssessmentPresenter() {}

public slots:

  virtual void setSession(const QString &session) = 0;

protected slots:


};


} // namespace photomatch

#endif // PHOTOMATCH_MULTIVIEW_INTERFACES_H

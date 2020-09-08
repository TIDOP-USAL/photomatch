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

#ifndef PHOTOMATCH_CURVES_VIEWER_INTERFACES_H
#define PHOTOMATCH_CURVES_VIEWER_INTERFACES_H

#include "photomatch/ui/mvp.h"

#include <QObject>

namespace photomatch
{


class CurvesViewerModel
  : public PhotoMatchModel
{

  Q_OBJECT

public:

  CurvesViewerModel(){}
  virtual ~CurvesViewerModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<QString> sessionNames() const = 0;
  virtual std::vector<std::tuple<QString, QString, QString>> sessions() const = 0;
  virtual std::vector<QPointF> computeCurve(const QString &session,
                                            const QString &imgLeft,
                                            const QString &imgRight) const = 0;
  virtual double computeCurve(const QString &session,
                              const QString &imgLeft,
                              const QString &imgRight,
                              std::vector<QPointF> &curve) const = 0;
  virtual std::vector<std::pair<double, int>> classifiedMatches(const QString &session,
                                                                const QString &imgLeft,
                                                                const QString &imgRight) const = 0;
  virtual QString adjustMatrix() const = 0;
  virtual void setAdjustMatrix(const QString &adjustMatrix) = 0;

};



class CurvesViewerView
  : public PhotoMatchDialogView
{

  Q_OBJECT

public:

  CurvesViewerView(QWidget *parent = nullptr,
                   Qt::WindowFlags f = Qt::WindowFlags())
    : PhotoMatchDialogView(parent, f)
  {}

  ~CurvesViewerView() override = default;

  virtual void addSession(const QString &session,
                          const QString &detector,
                          const QString &descriptor) = 0;
  virtual bool isSessionActive(const QString &session) const = 0;

  virtual QString leftImage() const = 0;
  virtual void setLeftImage(const QString &leftImage) = 0;

  virtual QString rightImage() const = 0;
  virtual void setRightImage(const QString &rightImage) = 0;

  /*!
   * \brief Set the list of images for image selector left
   * \param[in] leftImageList List of left images
   */
  virtual void setLeftImageList(const std::vector<QString> &leftImageList) = 0;

  /*!
   * \brief Set the list of images for image selector right
   * \param[in] rightImageList List of right images
   */
  virtual void setRightImageList(const std::vector<QString> &rightImageList) = 0;

  virtual void setCurve(const QString &title, const std::vector<QPointF> &curve) = 0;
  virtual void eraseCurve(const QString &session) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void activeSession(QString);
  void disableSession(QString);

};


class CurvesViewerPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  CurvesViewerPresenter() : PhotoMatchPresenter() {}
  virtual ~CurvesViewerPresenter() override {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void activeSession(const QString &session) = 0;
  virtual void disableSession(const QString &session) = 0;
  virtual void computeCurve(const QString &session,
                            const QString &imageLeft,
                            const QString &imageRight) = 0;
  virtual void deleteCurve(const QString &session) = 0;
};


} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_INTERFACES_H

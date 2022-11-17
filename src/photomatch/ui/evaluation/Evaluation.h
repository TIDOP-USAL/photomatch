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

#ifndef PHOTOMATCH_EVALUATION_INTERFACES_H
#define PHOTOMATCH_EVALUATION_INTERFACES_H

#include "photomatch/ui/mvp.h"

#include <QObject>
#include <QImage>

namespace photomatch
{

struct Report
{
  int total_matches{0};
  double average_error{0};
  double max_error{0};
  double pts_below_5_px{0};
  double pts_below_10_px{0};
  double pts_below_20_px{0};
  double pts_below_30_px{0};
  QImage image;
};

class EvaluationModel
  : public PhotoMatchModel
{

  Q_OBJECT

public:

  EvaluationModel(){}
  virtual ~EvaluationModel() {}

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<QString> sessionNames() const = 0;
  virtual std::vector<std::tuple<QString, QString, QString>> sessions() const = 0;
  virtual Report computeErrors(const QString &session,
                               const QString &imgLeft,
                               const QString &imgRight,
                               double errorThreshold = 10.) const = 0;
  virtual QString adjustMatrix() const = 0;
  virtual void setAdjustMatrix(const QString &adjustMatrix) = 0;

};



class EvaluationView
  : public PhotoMatchDialogView
{

  Q_OBJECT

public:

  EvaluationView(QWidget *parent = nullptr,
                   Qt::WindowFlags f = Qt::WindowFlags())
    : PhotoMatchDialogView(parent, f)
  {}

  ~EvaluationView() override = default;

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

  //virtual void setCurve(const QString &title, const std::vector<QPointF> &curve) = 0;
  //virtual void eraseCurve(const QString &session) = 0;
  virtual void setErrors(const QString &session, const Report &report) = 0;
  virtual void removeErrors(const QString &session) = 0;
  virtual void removeErrors() = 0;
  
  virtual double errorThreshold() const = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void activeSession(QString);
  void disableSession(QString);
  void error_threshold_changed(double);
};


class EvaluationPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  EvaluationPresenter() : PhotoMatchPresenter() {}
  virtual ~EvaluationPresenter() override {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void activeSession(const QString &session) = 0;
  virtual void disableSession(const QString &session) = 0;
  virtual void setErrorThreshold(double error) = 0;
};


} // namespace photomatch

#endif // PHOTOMATCH_EVALUATION_INTERFACES_H

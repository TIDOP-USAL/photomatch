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

#ifndef PHOTOMATCH_FEATURES_VIEWER_INTERFACES_H
#define PHOTOMATCH_FEATURES_VIEWER_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class ProjectModelImp;


class FeaturesViewerModel
  : public PhotoMatchModel
{

  Q_OBJECT

public:

  FeaturesViewerModel() {}
  virtual ~FeaturesViewerModel() = default;

  virtual QString sessionName() const = 0;
  virtual void setSessionName(const QString &session) = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<std::tuple<QPointF, double, double>> loadKeypoints(const QString &image) = 0;

};


class FeaturesViewerView
  : public PhotoMatchDialogView
{
  Q_OBJECT

public:

  explicit FeaturesViewerView(QWidget *parent = nullptr,
                               Qt::WindowFlags f = Qt::WindowFlags())
       : PhotoMatchDialogView(parent, f) {}
  virtual ~FeaturesViewerView() = default;

  /*!
   * \brief setSessionName
   * \param[in] name Nombre de sesión
   */
  virtual void setSessionName(const QString &name) = 0;

  /*!
   * \brief Set the list of images
   * \param[in] imageList List of images
   */
  virtual void setImageList(const std::vector<QString> &imageList) = 0;

  /*!
   * \brief setCurrentImage
   * \param leftImage
   */
  virtual void setCurrentImage(const QString &leftImage) = 0;

  /*!
   * \brief setKeyPoints
   * \param[in] keyPoints Keypoints
   */
  virtual void setKeyPoints(const std::vector<std::tuple<QPointF, double, double>> &keyPoints) = 0;

  virtual void setBGColor(const QString &bgColor) = 0;
  virtual void setSelectedMarkerStyle(const QString &color, int width) = 0;
  virtual void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) = 0;

signals:

  void imageChange(QString);

};



class FeaturesViewerPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  FeaturesViewerPresenter() {}
  virtual ~FeaturesViewerPresenter() {}

public slots:

  virtual void setSession(const QString &session) = 0;
  virtual void setImageActive(const QString &image) = 0;
  virtual void openKeypointsFromSession(const QString &session) = 0;
  virtual void openKeypointsFromSessionAndImage(const QString &session, const QString &image) = 0;

protected slots:

  virtual void loadKeypoints(const QString &image) = 0;

};


} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_VIEWER_INTERFACES_H

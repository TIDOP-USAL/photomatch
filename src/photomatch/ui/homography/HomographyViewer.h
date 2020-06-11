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

#ifndef PHOTOMATCH_HOMOGRAPHY_VIEWER_INTERFACES_H
#define PHOTOMATCH_HOMOGRAPHY_VIEWER_INTERFACES_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{


class HomographyViewerModel
  : public PhotoMatchModel
{

  Q_OBJECT

public:

  HomographyViewerModel(){}
  virtual ~HomographyViewerModel() {}

  virtual QString currentSession() const = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual QImage homography(const QString &imgName1,
                            const QString &imgName2) const = 0;
  virtual void setUseCuda(bool active) = 0;

};


class HomographyViewerView
  : public PhotoMatchDialogView
{

  Q_OBJECT

public:

  HomographyViewerView(QWidget *parent = nullptr,
                       Qt::WindowFlags f = Qt::WindowFlags())
    : PhotoMatchDialogView(parent, f) {}
  virtual ~HomographyViewerView() = default;

  virtual void setSessionName(const QString &name) = 0;

  /*!
   * \brief Set the left image
   * \param[in] leftImage Left image
   */
  virtual void setLeftImage(const QString &leftImage) = 0;

  /*!
   * \brief Set the right image
   * \param[in] rightImage Right image
   */
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

  /*!
   * \brief setHomography
   * \param matches
   */
  virtual void setHomography(const QImage &homography) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void homography(QString, QString);

};


class HomographyViewerPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  HomographyViewerPresenter() : PhotoMatchPresenter() {}
  virtual ~HomographyViewerPresenter() {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void homography(const QString &imageLeft,
                          const QString &imageRight) = 0;

};


} // namespace photomatch

#endif // PHOTOMATCH_HOMOGRAPHY_VIEWER_INTERFACES_H

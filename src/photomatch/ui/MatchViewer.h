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

#ifndef PHOTOMATCH_MATCH_VIEWER_INTERFACES_H
#define PHOTOMATCH_MATCH_VIEWER_INTERFACES_H

#include "photomatch/ui/mvp.h"

namespace photomatch
{

/*!
 * \brief The IMatchViewerModel class
 */
class MatchViewerModel
  : public IModel
{

  Q_OBJECT

public:

  MatchViewerModel() {}
  virtual ~MatchViewerModel() {}

  virtual QString sessionName() const = 0;
  virtual void setSessionName(const QString &session) = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float>> loadMatches(const QString &imgName1, const QString &imgName2) const = 0;
  virtual void deleteMatch(const QString &imgName1, const QString &imgName2, int query_id, int train_id) = 0;
  virtual void loadPassPoints() = 0;

public slots:

};


class MatchViewerView
  : public IDialogView
{
  Q_OBJECT

public:

  explicit MatchViewerView(QWidget *parent = nullptr,
                            Qt::WindowFlags f = Qt::WindowFlags())
    : IDialogView(parent, f) {}

  virtual ~MatchViewerView() = default;

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

  virtual void setMatches(const std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float>> &matches) = 0;

  virtual void setBGColor(const QString &bgColor) = 0;
  virtual void setSelectedMarkerStyle(const QString &color, int width) = 0;
  virtual void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) = 0;
  virtual void setLineStyle(const QString &color, int width) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void loadMatches(QString, QString);
  void deleteMatch(QString, QString, int, int);
};


/*!
 * \brief The IMatchViewerPresenter class
 */
class MatchViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  MatchViewerPresenter(){}
  virtual ~MatchViewerPresenter() {}

public slots:

  virtual void openFromSession(const QString &session) = 0;
  virtual void openFromSessionAndImages(const QString &session, const QString &imageLeft, const QString &imageRight) = 0;

protected slots:

  virtual void setSession(const QString &session) = 0;
  virtual void setLeftImage(const QString &image) = 0;
  virtual void setRightImage(const QString &image) = 0;
  virtual void loadMatches(const QString &imageLeft, const QString &imageRight) = 0;
  virtual void deleteMatch(const QString &imageLeft, const QString &imageRight, int query_id, int train_id) = 0;
};

} // namespace photomatch

#endif // PHOTOMATCH_MATCH_VIEWER_INTERFACES_H

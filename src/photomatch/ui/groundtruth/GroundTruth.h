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

#ifndef PHOTOMATCH_GROUND_TRUTH_INTERFACES_H
#define PHOTOMATCH_GROUND_TRUTH_INTERFACES_H


#include "photomatch/ui/mvp.h"
#include "photomatch/core/features/groundtruth.h"

namespace photomatch
{


class GroundTruthModel
  : public PhotoMatchModel
{

  Q_OBJECT

public:

  GroundTruthModel(){}
  virtual ~GroundTruthModel() override {}

  virtual void loadGroundTruth() = 0;
  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &imageName) const = 0;
  virtual std::vector<std::pair<QPointF, QPointF>> groundTruth(const QString &imgName1,
                                                               const QString &imgName2) const = 0;
  virtual std::pair<QPointF, QPointF> homologus(const QString &imgName1,
                                                const QString &imgName2,
                                                int pointId) const = 0;
  virtual photomatch::HomologusPoints homologusPoints(const QString &imgName1,
                                                      const QString &imgName2) const = 0;
  virtual QTransform homography(const QString &imgName1,
                                const QString &imgName2) const = 0;
  virtual QTransform homography(const photomatch::HomologusPoints &homologusPoints) const = 0;
  virtual cv::Mat fundamental(const QString &imgName1,
                              const QString &imgName2) const = 0;
  virtual cv::Mat fundamental(const photomatch::HomologusPoints &homologusPoints) const = 0;
  virtual std::vector<double> errorsHomography(const QString &imgName1,
                                               const QString &imgName2) const = 0;
  virtual std::vector<double> errorsFundamental(const QString &imgName1,
                                                const QString &imgName2) const = 0;
  virtual void saveGroundTruth() = 0;
  virtual void setGroundTruth(const QString &file) = 0;
  virtual bool existGroundTruth() const = 0;
  virtual QString projectPath() const = 0;
  virtual QPointF findLeftPoint(const QString &image1,
                                const QString &image2,
                                const QPointF &pt) = 0;
  virtual QPointF findRightPoint(const QString &image1,
                                 const QString &image2,
                                 const QPointF &pt) = 0;
  virtual QPointF findProjectedLeftPoint(const QString &image1,
                                         const QString &image2,
                                         const QPointF &pt) = 0;
  virtual QPointF findProjectedRightPoint(const QString &image1,
                                          const QString &image2,
                                          const QPointF &pt) = 0;

public slots:

  virtual void addHomologus(const QString &image1,
                            const QPointF &pt1,
                            const QString &image2,
                            const QPointF &pt2) = 0;
  virtual void deleteHomologus(const QString &image1,
                               const QString &image2,
                               int pointId) = 0;

};



class GroundTruthView
  : public PhotoMatchDialogView
{

  Q_OBJECT

public:

  GroundTruthView(QWidget *parent = nullptr,
                     Qt::WindowFlags f = Qt::WindowFlags())
    : PhotoMatchDialogView(parent, f)
  {
  }

  virtual ~GroundTruthView() = default;

  /*!
   * \brief Current left image
   * \return
   */
  virtual QString leftImage() const = 0;

  /*!
   * \brief Current right image
   * \return
   */
  virtual QString rightImage() const = 0;

public slots:

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
   * \brief Select left point
   * \param[in] pt Selected point left
   * \param[in] newPoint Point for added
   */
  virtual void setSelectLeftPoint(const QPointF &pt, bool newPoint = false) = 0;

  /*!
   * \brief Select right point
   * \param[in] pt Selected point right
   * \param[in] newPoint Point for added
   */
  virtual void setSelectedRightPoint(const QPointF &pt,
                                     bool newPoint = false) = 0;

  /*!
   * \brief Select homologous points
   * \param[in] ptLeft Left point
   * \param[in] ptRight Right point
   */
  virtual void setSelectedHomologous(const QPointF &ptLeft,
                                     const QPointF &ptRight) = 0;

  /*!
   * \brief Unselect homologous point
   */
  virtual void unselectHomologous() = 0;

  /*!
   * \brief Set pairs of homologous points
   * \param[in] points Pairs of homologous points
   */
  virtual void setHomologousPoints(const std::vector<std::pair<QPointF,QPointF>> &points) = 0;

  /*!
   * \brief Add homologous points to list
   * \param[in] pt1 Left point
   * \param[in] pt2 Right point
   */
  virtual void addHomologous(const QPointF &pt1,
                             const QPointF &pt2) = 0;

  /*!
   * \brief Delete Homologous points
   * \param[in ] pointId Identifier of the homologous points
   */
  virtual void deleteHomologous(int pointId) = 0;

  virtual void setHomologousError(int pointId,
                                  double distance) = 0;

  virtual void setUnsavedChanges(bool value) = 0;
  virtual void enableLockView(bool enable) = 0;

  virtual void clickedPointLeft(const QPointF &pt) = 0;
  virtual void clickedPointRight(const QPointF &pt) = 0;

  //virtual void setTransform(const QTransform &trf) = 0;

  virtual void setBGColor(const QString &bgColor) = 0;
  virtual void setMarkerStyle(const QString &color,
                              int width,
                              int type = 0,
                              int size = 20) = 0;
  virtual void setSelectedMarkerStyle(const QString &color,
                                      int width) = 0;
  virtual void setCenterLeftViewer(const QPointF &pt,
                                   bool zoom11 = true) = 0;
  virtual void setCenterRightViewer(const QPointF &pt,
                                    bool zoom11 = true) = 0;

signals:

  void leftImageChange(QString);
  void rightImageChange(QString);
  void loadHomologousPoints(QString, QString);
  void addHomologousPoints(QString, QPointF, QString,  QPointF);
  void deleteHomologous(QString, QString, int);
  void selectHomologous(QString, QString, int);
  void importGroundTruth();
  void saveGroundTruth();
  void leftPointClicked(QString, QString, QPointF);
  void rightPointClicked(QString, QString, QPointF);
  void findLeftPoint(QString, QString, QPointF);
  void findRightPoint(QString, QString, QPointF);

};



class GroundTruthPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  GroundTruthPresenter(){}
  virtual ~GroundTruthPresenter() override {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void loadGroundTruth(const QString &imageLeft, const QString &imageRight) = 0;
  virtual void addHomologousPoints(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2) = 0;
  virtual void deleteHomologous(const QString &image1, const QString &image2, int pointId) = 0;
  virtual void importGroundTruth() = 0;
  virtual void selectHomologous(const QString &image1, const QString &image2, int pointId) = 0;
  virtual void leftPointClicked(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual void rightPointClicked(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual void findLeftPoint(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual void findRightPoint(const QString &image1, const QString &image2, const QPointF &pt) = 0;

  virtual void save() = 0;
  virtual void discart() = 0;

signals:

  void groundTruthAdded();

};


} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_INTERFACES_H

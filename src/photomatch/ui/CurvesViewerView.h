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


#ifndef PHOTOMATCH_CURVES_VIEWER_VIEW_H
#define PHOTOMATCH_CURVES_VIEWER_VIEW_H

#include "mvp.h"

class QDialogButtonBox;
class QComboBox;
class QTreeWidget;
class QTreeWidgetItem;

namespace QtCharts
{
class QChart;
class QValueAxis;
}

namespace photomatch
{

class ICurvesViewerView
  : public IDialogView
{

  Q_OBJECT

public:

  ICurvesViewerView(QWidget *parent = nullptr,
                    Qt::WindowFlags f = Qt::WindowFlags())
    : IDialogView(parent, f)
  {}

  virtual ~ICurvesViewerView() override = default;

  /*!
   * \brief Add a session
   * \param[in] session Session
   */
  virtual void addSession(const QString &session, const QString &detector, const QString &descriptor) = 0;

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
  void drawCurve(QString, QString, QString);
  void deleteCurve(QString);
};

class CurvesViewerView
  : public ICurvesViewerView
{

  Q_OBJECT

public:

  CurvesViewerView(QWidget *parent = nullptr,
                   Qt::WindowFlags f = Qt::WindowFlags());

  virtual ~CurvesViewerView() override;

protected slots :

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  void onTreeWidgetSessionsItemChanged(QTreeWidgetItem *item,int column);

// ICurvesViewerView interface

  virtual void addSession(const QString &session, const QString &detector, const QString &descriptor) override;
  virtual QString leftImage() const override;
  virtual void setLeftImage(const QString &leftImage) override;
  virtual QString rightImage() const override;
  virtual void setRightImage(const QString &rightImage) override;
  virtual void setLeftImageList(const std::vector<QString> &leftImageList) override;
  virtual void setRightImageList(const std::vector<QString> &rightImageList) override;
  virtual void setCurve(const QString &title, const std::vector<QPointF> &curve) override;
  virtual void eraseCurve(const QString &session) override;

// IDialogView interface

private:

  virtual void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QDialogButtonBox *mButtonBox;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  QTreeWidget *mTreeWidgetSessions;
  QtCharts::QChart *mChart;
  QtCharts::QValueAxis *mAxisX;
  QtCharts::QValueAxis *mAxisY;
};


/*!
 * \brief ROC curve (receiver operating characteristic)
 */
class ROCCurvesViewer
  : public CurvesViewerView
{

  Q_OBJECT

public:

  ROCCurvesViewer(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~ROCCurvesViewer() override;

// IDialogView interface

private:

  void init() override;

};


/*!
 * \brief Precision-Recall Curve
 */
class PRCurvesViewer
    : public CurvesViewerView
{

  Q_OBJECT

public:

  PRCurvesViewer(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~PRCurvesViewer() override;

// IDialogView interface

private:

  void init() override;

};



/*!
 * \brief DET (Detection Error Tradeoff) Curve
 */
class DETCurvesViewer
    : public CurvesViewerView
{

  Q_OBJECT

public:

  DETCurvesViewer(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~DETCurvesViewer() override;

// IDialogView interface

private:

  void init() override;

};



} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_VIEW_H

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

#include "photomatch/ui/curves/CurvesViewer.h"

class QDialogButtonBox;
class QComboBox;
class QTreeWidget;
class QTreeWidgetItem;
class QLabel;

namespace QtCharts
{
class QChart;
class QValueAxis;
}

namespace photomatch
{

class CurvesViewerViewImp
  : public CurvesViewerView
{

  Q_OBJECT

public:

  CurvesViewerViewImp(QWidget *parent = nullptr,
                      Qt::WindowFlags f = Qt::WindowFlags());
  ~CurvesViewerViewImp() override;

protected slots :

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  void onTreeWidgetSessionsItemChanged(QTreeWidgetItem *item,int column);

// CurvesViewerView interface

  virtual void addSession(const QString &session, const QString &detector, const QString &descriptor) override;
  virtual bool isSessionActive(const QString &session) const override;
  virtual QString leftImage() const override;
  virtual void setLeftImage(const QString &leftImage) override;
  virtual QString rightImage() const override;
  virtual void setRightImage(const QString &rightImage) override;
  virtual void setLeftImageList(const std::vector<QString> &leftImageList) override;
  virtual void setRightImageList(const std::vector<QString> &rightImageList) override;
  virtual void setCurve(const QString &title, const std::vector<QPointF> &curve) override;
  virtual void eraseCurve(const QString &session) override;

// PhotoMatchDialogView interface

private:

  virtual void initUI() override;
  virtual void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QDialogButtonBox *mButtonBox;
  QLabel *mLabelLeftImage;
  QComboBox  *mComboBoxLeftImage;
  QLabel *mLabelRightImage;
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
  : public CurvesViewerViewImp
{

  Q_OBJECT

public:

  ROCCurvesViewer(QWidget *parent = nullptr,
                  Qt::WindowFlags f = Qt::WindowFlags());
  ~ROCCurvesViewer() override;

// PhotoMatchDialogView interface

private:

  void initUI() override;

private slots:

  void retranslate() override;
};


/*!
 * \brief Precision-Recall Curve
 */
class PRCurvesViewer
    : public CurvesViewerViewImp
{

  Q_OBJECT

public:

  PRCurvesViewer(QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags());
  ~PRCurvesViewer() override;

// PhotoMatchDialogView interface

private:

  void initUI() override;

private slots:

  void retranslate() override;
};



/*!
 * \brief DET (Detection Error Tradeoff) Curve
 */
class DETCurvesViewer
    : public CurvesViewerViewImp
{

  Q_OBJECT

public:

  DETCurvesViewer(QWidget *parent = nullptr,
                  Qt::WindowFlags f = Qt::WindowFlags());
  ~DETCurvesViewer() override;

// PhotoMatchDialogView interface

private:

  void initUI() override;

private slots:

  void retranslate() override;
};



} // namespace photomatch

#endif // PHOTOMATCH_CURVES_VIEWER_VIEW_H

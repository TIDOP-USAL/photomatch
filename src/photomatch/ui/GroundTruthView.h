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

#ifndef PHOTOMATCH_GROUND_TRUTH_VIEW_H
#define PHOTOMATCH_GROUND_TRUTH_VIEW_H

#include "photomatch/ui/GroundTruth.h"

class QComboBox;
class QTreeWidgetItem;
class QTreeWidget;
class QDialogButtonBox;
class QLineEdit;
class QLabel;


namespace photomatch
{

class GraphicViewer;
class CrossGraphicItem;





class GroundTruthViewImp
  : public GroundTruthView
{

  Q_OBJECT

public:

  GroundTruthViewImp(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~GroundTruthViewImp() override;

  QString leftImage() const override;
  QString rightImage() const override;

protected slots:

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  void onTreeWidgetItemSelectionChanged();
  void onGraphicsViewLeftSelectionChanged();
  void onGraphicsViewRightSelectionChanged();
  void onPushButtonAddPoints(bool active);
  void onPushButtonAddPointClicked();
  void onPushButtonLockViewsToggled(bool active);
  void onPushButtonDeleteClicked();
  void onAccept();

private:

  void removeHomologousPointInGraphicsViews(int id);
  void removeHomologousPointsInGraphicsViews();

// IGroundTruthView interface

public slots:

  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setSelectLeftPoint(const QPointF &pt, bool newPoint = false) override;
  void setSelectedRightPoint(const QPointF &pt, bool newPoint = false) override;
  void setSelectedHomologous(const QPointF &ptLeft, const QPointF &ptRight) override;
  void unselectHomologous() override;
  void setHomologousPoints(const std::vector<std::pair<QPointF,QPointF>> &points) override;
  void addHomologous(const QPointF &pt1, const QPointF &pt2) override;
  void deleteHomologous(int pointId) override;
  void setHomologousDistance(int pointId, double distance) override;
  void setUnsavedChanges(bool value) override;
  void enableLockView(bool enable) override;
  void clickedPointLeft(const QPointF &pt) override;
  void clickedPointRight(const QPointF &pt) override;
  void setBGColor(const QString &bgColor) override;
  void setSelectedMarkerStyle(const QString &color, int width) override;
  void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) override;
  void setCenterLeftViewer(const QPointF &pt, bool zoom11 = true) override;
  void setCenterRightViewer(const QPointF &pt, bool zoom11 = true) override;

// IDialogView interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

// QWidget interface

protected:

  void closeEvent(QCloseEvent *event) override;

protected:

  QDialogButtonBox *mButtonBox;
  QTreeWidget *mTreeWidget;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  GraphicViewer *mGraphicsViewRight;
  GraphicViewer *mGraphicsViewLeft;
  QLineEdit *mLineEditLeftX;
  QLineEdit *mLineEditLeftY;
  QLabel *mLabelDetailLeft;
  QLineEdit *mLineEditRightX;
  QLineEdit *mLineEditRightY;
  QLabel *mLabelDetailRight;
  QPushButton *mPushButtonAddPoint;
  QPushButton *mPushButtonDelete;
  QPushButton *mPushButtonLockViews;
  QAction *mImportGroundTruth;
  QAction *mSaveGroundTruth;
  QAction *mAddPoints;
  //QAction *mDeletePoints;
  CrossGraphicItem *mCrossGraphicItem1;
  CrossGraphicItem *mCrossGraphicItem2;
  bool bUnsavedChanges;
  bool bEnableLockViews;
  QTransform mTrf;
  bool bLockViews;
  QString mMarkerColor;
  int mMarkerSize;
  int mMarkerWidth;
  int mMarkerType;
  int mPointsCounter;
  QString mSelectedMarkerColor;
  int mSelectedMarkerWidth;


};

} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_VIEW_H

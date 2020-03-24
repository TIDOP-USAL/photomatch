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


#ifndef PHOTOMATCH_MATCH_VIEWER_VIEW_H
#define PHOTOMATCH_MATCH_VIEWER_VIEW_H

#include "photomatch/ui/MatchViewer.h"

class QDialogButtonBox;
class QTreeWidget;
class QComboBox;
class QTreeWidgetItem;

namespace photomatch
{

class GraphicViewer;


class MatchViewerViewImp
  : public MatchViewerView
{

  Q_OBJECT

public:

  MatchViewerViewImp(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~MatchViewerViewImp() override;

protected slots :

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);
  void onTreeWidgetMatchesItemClicked(QTreeWidgetItem *item, int col);
  void onTreeWidgetMatchesItemSelectionChanged();
  void onGraphicsViewLeftSelectionChanged();
  void onGraphicsViewRightSelectionChanged();
  void onPushButtonDeleteMatchClicked();

// IMatchViewerView interface

public:

  void setSessionName(const QString &name) override;
  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setMatches(const std::vector<std::tuple<size_t, size_t, QPointF, size_t, QPointF, float>> &matches) override;
  void setBGColor(const QString &bgColor) override;
  void setSelectedMarkerStyle(const QString &color, int width) override;
  void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) override;
  void setLineStyle(const QString &color, int width) override;

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
  QTreeWidget *mTreeWidgetMatches;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  GraphicViewer *mGraphicsViewRight;
  GraphicViewer *mGraphicsViewLeft;
  QPushButton *mPushButtonDeleteMatch;
  bool bUnsavedChanges;
  QString mMarkerColor;
  int mMarkerSize;
  int mMarkerWidth;
  int mMarkerType;
  QString mLineColor;
  int mLineWidth;
  QString mSelectedMarkerColor;
  int mSelectedMarkerWidth;
};

} // namespace photomatch

#endif // PHOTOMATCH_MATCH_VIEWER_VIEW_H

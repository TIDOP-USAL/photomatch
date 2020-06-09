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

#ifndef PHOTOMATCH_FEATURES_VIEWER_VIEW_H
#define PHOTOMATCH_FEATURES_VIEWER_VIEW_H

#include "photomatch/ui/FeaturesViewer.h"

class QTreeWidget;
class QComboBox;
class QDialogButtonBox;
class QLabel;
class QMenu;

namespace photomatch
{

class GraphicViewerImp;

class FeaturesViewerViewImp
  : public FeaturesViewerView
{
  Q_OBJECT

public:

  FeaturesViewerViewImp(QWidget *parent = nullptr,
                        Qt::WindowFlags f = Qt::WindowFlags());
  ~FeaturesViewerViewImp() override;

protected slots:

  void onGraphicsViewSelectionChanged();
  void onTreeWidgetItemSelectionChanged();

// FeaturesViewerView interface

  void setSessionName(const QString &name) override;
  void setImageList(const std::vector<QString> &imageList) override;
  void setCurrentImage(const QString &leftImage) override;
  void setKeyPoints(const std::vector<std::tuple<QPointF, double, double>> &keyPoints) override;
  void setBGColor(const QString &bgColor) override;
  void setSelectedMarkerStyle(const QString &color, int width) override;
  void setMarkerStyle(const QString &color, int width, int type = 0, int size = 20) override;

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
  QLabel *mLabelImages;
  QComboBox *mComboBoxImages;
  GraphicViewerImp *mGraphicView;
  QTreeWidget *mTreeWidget;
  QMenu *mContextMenuLeft;
  QAction *mActionZoomIn;
  QAction *mActionZoomOut;
  QAction *mActionZoomExtend;
  QAction *mActionZoom11;
  QString mMarkerColor;
  QString mSelectedMarkerColor;
  int mMarkerType;
  int mMarkerSize;
  int mMarkerWidth;
  int mSelectedMarkerWidth;
};


} // namespace photomatch

#endif // PHOTOMATCH_FEATURES_VIEWER_VIEW_H

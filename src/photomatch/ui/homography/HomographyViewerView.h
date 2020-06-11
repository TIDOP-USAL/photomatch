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


#ifndef PHOTOMATCH_HOMOGRAPHY_VIEWER_VIEW_H
#define PHOTOMATCH_HOMOGRAPHY_VIEWER_VIEW_H

#include "photomatch/ui/homography/HomographyViewer.h"

class QDialogButtonBox;
class QComboBox;

namespace photomatch
{

class GraphicViewerImp;




class HomographyViewerViewImp
  : public HomographyViewerView
{
  Q_OBJECT

public:

  HomographyViewerViewImp(QWidget *parent = nullptr,
                          Qt::WindowFlags f = Qt::WindowFlags());
  ~HomographyViewerViewImp() override;

protected slots :

  void onComboBoxLeftImageIndexChanged(int idx);
  void onComboBoxRightImageIndexChanged(int idx);

// HomographyViewerView interface

public:

  void setSessionName(const QString &name) override;
  void setLeftImage(const QString &leftImage) override;
  void setRightImage(const QString &rightImage) override;
  void setLeftImageList(const std::vector<QString> &leftImageList) override;
  void setRightImageList(const std::vector<QString> &rightImageList) override;
  void setHomography(const QImage &homography) override;

// PhotoMatchDialogView interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QDialogButtonBox *mButtonBox;
  QComboBox  *mComboBoxLeftImage;
  QComboBox  *mComboBoxRightImage;
  GraphicViewerImp *mGraphicsView;

};

} // namespace photomatch


#endif // PHOTOMATCH_HOMOGRAPHY_VIEWER_VIEW_H

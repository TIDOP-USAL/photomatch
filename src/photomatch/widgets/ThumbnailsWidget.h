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


#ifndef PHOTOMATCH_THUMBNAILS_WIDGET_H
#define PHOTOMATCH_THUMBNAILS_WIDGET_H

#include <QImage>

#include "photomatch/widgets/PhotoMatchWidget.h"

class QListWidget;
class QListWidgetItem;
class QGridLayout;
template <typename T> class QFutureWatcher;

namespace photomatch
{

class PHOTOMATCH_EXPORT ThumbnailsWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  explicit ThumbnailsWidget(QWidget *parent = nullptr);
  virtual ~ThumbnailsWidget() override {}

  void setActiveImage(const QString &image);
  void setActiveImages(const QStringList &images);

signals:

  void openImage(QString);
  void selectImage(QString);
  void selectImages(QStringList);
  void deleteImages(QStringList);
  void imagesLoaded();

public slots:

  void addThumbnail(const QString &thumb);
  void addThumbnails(const QStringList &thumb);
  void deleteThumbnail(const QString &thumb);
  void clear();

private slots:

  void onThumbnailDoubleClicked(QListWidgetItem *item);
  void onSelectionChanged();

  void onThumbnailClicked();
  void onThumbnailSmallClicked();
  void onDetailsClicked();
  void onDeleteImageClicked();

  void showThumbnail(int id);
  void finished();

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  virtual void initUI() override;
  void initSignalAndSlots() override;

// QWidget interface

protected:

  void changeEvent(QEvent *event) override;

protected:

  QListWidget *mListWidget;
  QGridLayout *mGridLayout;
  QSize mIconSize;
  QAction *mThumbnailAction;
  QAction *mThumbnailSmallAction;
  QAction *mDetailsAction;
  QAction *mDeleteImageAction;
  QFutureWatcher<QImage> *mFutureWatcherThumbnail;
  int mThumbnaislSize;
  bool bLoadingImages;
};

} // namespace photomatch

#endif // PHOTOMATCH_THUMBNAILS_WIDGET_H

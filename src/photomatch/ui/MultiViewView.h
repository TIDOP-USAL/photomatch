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


#ifndef PHOTOMATCH_MULTIVIEW_VIEW_H
#define PHOTOMATCH_MULTIVIEW_VIEW_H

#include "mvp.h"

class QLabel;
class QDialogButtonBox;
class QListWidget;
class QGridLayout;
//template <typename T> class QFutureWatcher;

namespace photomatch
{

class IMultiviewView
  : public IDialogView
{

Q_OBJECT

public:

  IMultiviewView(QWidget *parent = nullptr,
                 Qt::WindowFlags f = Qt::WindowFlags())
  : IDialogView(parent, f) {}
  virtual ~IMultiviewView() = default;

  virtual void setSessionName(const QString &name) = 0;
  virtual void setPassPointIds(const std::vector<size_t> &id) = 0;
  virtual void addPassPointIds(size_t id) = 0;
  virtual void addPassPointIdsAndNImages(size_t id, size_t size) = 0;
  //virtual void setImages(const QStringList &images) = 0;
  //virtual void setImages(const std::vector<QPixmap> &images) = 0;
  virtual void setImages(const std::vector<std::pair<QString, QPointF>> &images) = 0;

signals:

  void idChange(int);
};


class MultiviewView
  : public IMultiviewView
{

  Q_OBJECT

public:

  MultiviewView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~MultiviewView() override;

private slots:

  //void showImages(int id);
  //void finished();
  void onListWidgetIdsCurrentRowChanged(int row);

// IDialogView interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

// IMultiViewView interface

public:

  void setSessionName(const QString &name) override;
  void setPassPointIds(const std::vector<size_t> &id) override;
  void addPassPointIds(size_t id) override;
  void addPassPointIdsAndNImages(size_t id, size_t size) override;
  //void setImages(const std::vector<QPixmap> &images) override;
  void setImages(const std::vector<std::pair<QString, QPointF>> &images) override;

protected:

  QLabel *mLabelIds;
  QListWidget *mListWidgetIds;
  QListWidget *mListWidgetImages;
  QDialogButtonBox *mButtonBox;
  //QFutureWatcher<QPixmap> *mFutureWatcher;

};

} // namespace photomatch

#endif // PHOTOMATCH_MULTIVIEW_VIEW_H

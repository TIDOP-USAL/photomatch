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

#ifndef PHOTOMATCH_PREPROCESS_INTERFACES_H
#define PHOTOMATCH_PREPROCESS_INTERFACES_H

#include "photomatch/ui/process/ProcessView.h"
#include "photomatch/ui/process/ProcessPresenter.h"

namespace photomatch
{

class PreprocessModel
{

public:

  PreprocessModel(){}

};


class PreprocessView
  : public ProcessView
{

  Q_OBJECT

public:

  PreprocessView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
    : ProcessView(parent, f) {}
  virtual ~PreprocessView(){}

  virtual void setSessionName(const QString &name) = 0;
  virtual void addPreprocess(QWidget *detector) = 0;
  virtual QString currentPreprocess() const = 0;
  virtual void setCurrentPreprocess(const QString &preprocess) = 0;
  virtual int maxImageSize() const = 0;
  virtual void setMaxImageSize(int imageSize) = 0;
  virtual void setFullImageSize(bool fullImageSize) = 0;
  virtual bool fullImageSize() const = 0;

signals:

  void preprocessChange(QString);

};


class PreprocessPresenter
  : public ProcessPresenter
{

  Q_OBJECT

public:

  PreprocessPresenter() {}
  virtual ~PreprocessPresenter() = default;

signals:

  void imagePreprocessed(QString);

private slots:

  virtual void setCurrentPreprocess(const QString &preprocess) = 0;

};


} // namespace photomatch

#endif // PREPROCESS_H

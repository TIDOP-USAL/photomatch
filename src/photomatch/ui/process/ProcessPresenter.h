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

#ifndef PHOTOMATCH_PROCESS_PRESENTER_H
#define PHOTOMATCH_PROCESS_PRESENTER_H

#include <QObject>

#include "photomatch/ui/mvp.h"

class MultiProcess;

namespace photomatch
{

class ProgressHandler;


class ProcessPresenter
  : public PhotoMatchPresenter
{

  Q_OBJECT

public:

  ProcessPresenter();
  ~ProcessPresenter() override;

protected slots:

  virtual void onError(int code, const QString &msg);
  virtual void onFinished();
  virtual void createProcess() = 0;

public slots:

  virtual void setProgressHandler(ProgressHandler *progressHandler);
  virtual void run();
  virtual void cancel();

signals:

  void running();
  void finished();

protected:

  MultiProcess *mMultiProcess;
  ProgressHandler *mProgressHandler;
};



} // namespace photomatch


#endif // PHOTOMATCH_PROCESS_PRESENTER_H

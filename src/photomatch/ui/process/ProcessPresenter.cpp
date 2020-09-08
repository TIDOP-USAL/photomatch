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

#include "ProcessPresenter.h"

#include "photomatch/ui/utils/ProgressHandler.h"
#include "photomatch/process/MultiProcess.h"

#include <QStandardPaths>
#include <QDir>

namespace photomatch
{

	
ProcessPresenter::ProcessPresenter()
  : PhotoMatchPresenter(),
    mMultiProcess(new MultiProcess(true)),
    mProgressHandler(nullptr)
{
}

ProcessPresenter::~ProcessPresenter()
{
  if (mMultiProcess){
    delete mMultiProcess;
    mMultiProcess = nullptr;
  }
}

void ProcessPresenter::setProgressHandler(ProgressHandler *progressHandler)
{
  mProgressHandler = progressHandler;
}

void ProcessPresenter::onFinished()
{
  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->finish();
    mProgressHandler->setDescription(tr("Process Finished"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(finish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(next()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(finish()));
    
  }

  mMultiProcess->clearProcessList();

  emit finished();
}

void ProcessPresenter::onError(int code, const QString &msg)
{
  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->finish();
    mProgressHandler->setDescription(msg);

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(finish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(next()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(finish()));
  }

  mMultiProcess->clearProcessList();

  emit finished();
}

void ProcessPresenter::run()
{
  try {

    connect(mMultiProcess, SIGNAL(error(int, QString)),          this, SLOT(onError(int, QString)));
    connect(mMultiProcess, SIGNAL(finished()),                   this, SLOT(onFinished()));

    if (mProgressHandler){
      connect(mMultiProcess, SIGNAL(finished()),             mProgressHandler,    SLOT(finish()));
      connect(mMultiProcess, SIGNAL(statusChangedNext()),    mProgressHandler,    SLOT(next()));
      connect(mMultiProcess, SIGNAL(error(int, QString)),    mProgressHandler,    SLOT(finish()));

      mProgressHandler->setTitle("Process...");
      mProgressHandler->setDescription("Process...");
    }

    createProcess();

    if (mProgressHandler){
      if (mProgressHandler->max() == 1)
        mProgressHandler->setRange(0, mMultiProcess->count());
      mProgressHandler->setValue(0);
      mProgressHandler->init();
    }

    emit running();

    mMultiProcess->start();
  } catch (std::exception &e) {
    onError(0, e.what());
  } catch (...) {
    onError(0, "Unknown exception");
  }
}

void ProcessPresenter::cancel()
{
  mMultiProcess->stop();

  disconnect(mMultiProcess, SIGNAL(error(int, QString)), this, SLOT(onError(int, QString)));
  disconnect(mMultiProcess, SIGNAL(finished()),          this, SLOT(onFinished()));

  if (mProgressHandler){
    mProgressHandler->setRange(0,1);
    mProgressHandler->setValue(1);
    mProgressHandler->finish();
    mProgressHandler->setDescription(tr("Processing has been canceled by the user"));

    disconnect(mMultiProcess, SIGNAL(finished()),                 mProgressHandler,    SLOT(finish()));
    disconnect(mMultiProcess, SIGNAL(statusChangedNext()),        mProgressHandler,    SLOT(next()));
    disconnect(mMultiProcess, SIGNAL(error(int, QString)),        mProgressHandler,    SLOT(finish()));
  }

  mMultiProcess->clearProcessList();

  emit finished();
}


} // namespace photomatch

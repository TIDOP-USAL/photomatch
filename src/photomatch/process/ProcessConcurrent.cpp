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

#include "ProcessConcurrent.h"


#include <QtConcurrent/QtConcurrentRun>
#include <QtConcurrent/QtConcurrentMap>
#include <QFutureWatcher>

#include <iostream>


ProcessConcurrent::ProcessConcurrent()
  : mRunning(false),
    mWatcher(nullptr),
    mWait(false)
{
}

ProcessConcurrent::~ProcessConcurrent()
{
  if (mWatcher) {
    delete mWatcher;
    mWatcher = nullptr;
  }
}

void ProcessConcurrent::start()
{
  mWatcher = new QFutureWatcher<int>();

  connect(mWatcher, SIGNAL(finished()), this, SLOT(on_mProcessFinished()));

  mRunning = true;
  QFuture<int> future = QtConcurrent::run(this, &ProcessConcurrent::runLauncher);
  mWatcher->setFuture(future);
  if (mWait)
    future.waitForFinished();
}

void ProcessConcurrent::setWaitForFinished(bool wait)
{
  mWait = wait;
}

bool ProcessConcurrent::isRunning()
{
  return mRunning;
}

QByteArray ProcessConcurrent::readStdout()
{
  return "";
}

QByteArray ProcessConcurrent::readStderr()
{
  return "";
}

void ProcessConcurrent::stop()
{
  mWatcher->cancel();
  if (mWatcher->isRunning())
    mWatcher->waitForFinished();
  mRunning = false;

  if (mWatcher) {
    delete mWatcher;
    mWatcher = nullptr;
  }
}

void ProcessConcurrent::on_mProcessFinished()
{
  mRunning = false;

  if (mWatcher) {
    delete mWatcher;
    mWatcher = nullptr;
  }

  emit finished();
}

int ProcessConcurrent::runLauncher()
{
  run();
  return 0;
}

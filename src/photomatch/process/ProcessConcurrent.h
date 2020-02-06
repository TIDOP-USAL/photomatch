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


#ifndef PHOTOMATCH_PROCESS_CONCURRENT_H
#define PHOTOMATCH_PROCESS_CONCURRENT_H

#include <QFutureWatcher>

#include "Process.h"

class  PHOTOMATCH_EXPORT ProcessConcurrent 
  : public Process
{   
    Q_OBJECT

public:

  ProcessConcurrent();
  virtual ~ProcessConcurrent() override = default;

  virtual void start() override;
  virtual void setWaitForFinished(bool wait) override;
  virtual bool isRunning() override;

  virtual QByteArray readStdout() override;
  virtual QByteArray readStderr() override;

public slots:

  virtual void stop() override;
  void on_mProcessFinished();

protected:

  virtual void run()=0;
  int runLauncher();

private:

  bool mRunning;
  QFutureWatcher<int> *mWatcher;
  bool mWait;

};

#endif // PHOTOMATCH_PROCESS_CONCURRENT_H

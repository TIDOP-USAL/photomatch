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


#ifndef PHOTOMATCH_PROCESS_H
#define PHOTOMATCH_PROCESS_H

#include "photomatch/photomatch_global.h"

#include <QStringList>
#include <QObject>


class PHOTOMATCH_EXPORT Process
  : public QObject
{
  Q_OBJECT

public:

  Process();
  virtual ~Process() = default;
  
  virtual void start() = 0;
  virtual void setWaitForFinished(bool wait) = 0;
  virtual bool isRunning() = 0;
  virtual QByteArray readStdout() = 0;
  virtual QByteArray readStderr() = 0;
  
  virtual bool isStopped();
  virtual int getSteps();
  
  void addIntputs (const QStringList &inputs);
  QString startupMessage();
  void setStartupMessage(const QString &message);
  void setSteps(int steps);

public slots:

  virtual void stop();

signals:

  void statusChanged(int, const QString &);
  void statusChangedNext();
  void finished();
  void error(int, const QString &);

  //For real-time output reading.
  void readyReadStandardOutput();
  void readyReadStandardError();
  void newStdData(const QString &);
  void newErrorData(const QString &);

protected:

  QStringList mInputs;
  bool mStopped;

private:

  int mSteps;
  QString mStartupMessage;

};

#endif // PHOTOMATCH_PROCESS_H

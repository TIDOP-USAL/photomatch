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


#ifndef PHOTOMATCH_EXTERNALPROCESS_H
#define PHOTOMATCH_EXTERNALPROCESS_H

#include <QProcess>
//#include <QFileSystemWatcher>
#include <QTimer>
//

#include "Process.h"

class QFileSystemWatcher;
class QFile;

class PHOTOMATCH_EXPORT ExternalProcess
  : public Process
{

  Q_OBJECT

public:

  explicit ExternalProcess(const QString &commandPath);
  ~ExternalProcess() override;

  void start() override;
  void setWaitForFinished(bool wait) override;
  bool isRunning() override;

  void setWorkingDir(const QString &workingDir);
  void setErroLogFile(const QString &filePath);
  void setStdOutputFilePath(const QString &filePath);
  void setStdErrorFilePath(const QString &filePath);
  qint64 write(const char *data);

  QByteArray readStdout() override;
  QByteArray readStderr() override;

  //! Insert a evironment variable in the execution environment of de process overwriting it if existing
  /*!
      \param varName variable name
      \param  value new value
    */
  void insertEnvironmentVar(const QString &varName, const QString &value);

  //! Append a value to an environment variable in the execution environment of de process using ";" as separator
  /*!
      \param varName variable name
      \param  value new value
      \param position 0 insert de value before (default). 1 insert value after.
    */
  void appendEnvironmentValue(const QString &varName, const QString &value, int position=0);

  //! direct call to QProcess::error()
  /*!
      \return Error code
    */
  virtual int error();

public slots:

  void stop() override;

protected:

  void run();

private:

  void openLogFiles();
  void closeLogFiles();

protected slots:

  void onError(QProcess::ProcessError commandError);
  void onError(const QString &path);
  void onTimeout();

private slots:

  void on_newStdData();
  void on_newErrorData();
  void on_mProcessFinished(int code);

private:

  void cascadeKill(Q_PID pid);

protected:

  QString mCommandPath;
  QString mWorkingDir;

private:

  QProcess *mProcess;
  int mErrorFileSize;
  QString mErrorFilePath;
  QString mStdOutputFilePath;
  QString mStdErrorFilePath;
  QFile *mStdOutFile;
  QFile *mErrOutFile;
  QFileSystemWatcher *mErrorWatcher;
  QTimer mTimer;
  bool mRunning;

};

#endif // PHOTOMATCH_EXTERNALPROCESS_H

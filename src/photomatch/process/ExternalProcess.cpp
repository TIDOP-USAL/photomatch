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

#include "ExternalProcess.h"

#include <iostream>

#include <QDir>
#include <QWaitCondition>
#include <QDebug>
#include <csignal>
#include <QFileSystemWatcher>
#include <QFile>

ExternalProcess::ExternalProcess(const QString &commandPath)
  : mCommandPath(commandPath),
    mWorkingDir(),
    mProcess(new QProcess()),
    mErrorFilePath("pwErrors.log"),
    mStdOutFile(new QFile()),
    mErrOutFile(new QFile()),
    mRunning(false)
{

  setSteps(1);
  QFileInfo fileInfo(mErrorFilePath);
  mErrorFileSize = fileInfo.size();

  mErrorWatcher = new QFileSystemWatcher(QStringList() << mErrorFilePath);

  connect(mErrorWatcher, SIGNAL(fileChanged(QString)), this, SLOT(onError(QString)));
  connect(this, SIGNAL(error(QProcess::ProcessError)), this, SLOT(onError(QProcess::ProcessError)));
  connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SIGNAL(readyReadStandardOutput()));
  connect(mProcess, SIGNAL(readyReadStandardError()), this, SIGNAL(readyReadStandardError()));
  connect(mProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(on_newStdData()));
  connect(mProcess, SIGNAL(readyReadStandardError()), this, SLOT(on_newErrorData()));
}

ExternalProcess::~ExternalProcess()
{
  if (mProcess) {
    delete mProcess;
    mProcess = nullptr;
  }

  if (mErrorWatcher) {
    delete mErrorWatcher;
    mErrorWatcher = nullptr;
  }

  if (mStdOutFile) {
    delete mStdOutFile;
    mStdOutFile = nullptr;
  }

  if (mErrOutFile) {
    delete mErrOutFile;
    mErrOutFile = nullptr;
  }
}

void ExternalProcess::start()
{
  run();
}

void ExternalProcess::setWaitForFinished(bool wait)
{
  mProcess->waitForFinished();
}

bool ExternalProcess::isRunning()
{
  return mRunning;
}

void ExternalProcess::run()
{
  mRunning = true;

  this->openLogFiles();

  QDir workingDir(mWorkingDir);
  if (workingDir.exists(mWorkingDir))
    mProcess->setWorkingDirectory(mWorkingDir);
    
  connect(mProcess, SIGNAL(finished(int)), this, SLOT(on_mProcessFinished(int)));
    
  emit statusChanged(0, startupMessage());

  mProcess->start(mCommandPath, mInputs);
}

void ExternalProcess::openLogFiles()
{
  mStdOutFile->setFileName(mStdOutputFilePath);
  if (mStdOutFile->exists())
    mStdOutFile->open(QFile::WriteOnly);
  mErrOutFile->setFileName(mStdErrorFilePath);
  if (mErrOutFile->exists())
    mErrOutFile->open(QFile::WriteOnly);
}

void ExternalProcess::closeLogFiles()
{
  if (mStdOutFile->exists())
    mStdOutFile->close();
  if (mErrOutFile->exists())
    mErrOutFile->close();
}

void ExternalProcess::setWorkingDir(const QString &workingDir)
{
  mWorkingDir = workingDir;
}

void ExternalProcess::onError(QProcess::ProcessError commandError)
{
  stop();
  emit Process::error(1, mCommandPath);
}

void ExternalProcess::onError(const QString &path)
{
  QFileInfo fileInfo(mErrorFilePath);
  int errorFileSize = fileInfo.size();
  if (errorFileSize > 0 && (errorFileSize - mErrorFileSize) < 0) {
    stop();
    emit Process::error(1, mCommandPath);
  }
}

void ExternalProcess::onTimeout()
{
  mProcess->write("\n");
  mTimer.start(5000);
}

void ExternalProcess::on_newStdData()
{
  QByteArray array = readStdout();
  QString out(array);
  emit newStdData(out);
  if(mStdOutFile->exists()){
    mStdOutFile->write(array);
  }
}

void ExternalProcess::on_newErrorData()
{
  QByteArray array = readStderr();
  QString out(array);
  emit newErrorData(out);
  if(mErrOutFile->exists()){
    mErrOutFile->write(array);
  }
}

void ExternalProcess::on_mProcessFinished(int code)
{
  disconnect(mProcess, SIGNAL(finished(int)), this, SLOT(on_mProcessFinished(int)));
  emit statusChanged(1, startupMessage());
  mRunning = false;

  this->closeLogFiles();

  qDebug() << QString(" ************** Finishing: ") << mCommandPath <<
              QString(" ExitCode: ") << QString::number(code) << QString(" ExitCode: ") << this->objectName();
  emit finished();
}

void ExternalProcess::stop()
{
  Process::stop();
  cascadeKill(mProcess->pid());
  mProcess->kill();
}

void ExternalProcess::setErroLogFile(const QString &filePath)
{
  mErrorWatcher->removePath(mErrorFilePath);
  mErrorFilePath = filePath;

  QFileInfo fileInfo(mErrorFilePath);
  mErrorFileSize = fileInfo.size();

  mErrorWatcher->addPath(mErrorFilePath);
}

void ExternalProcess::setStdOutputFilePath(const QString &filePath)
{
  mStdOutputFilePath = filePath;
}

void ExternalProcess::setStdErrorFilePath(const QString &filePath)
{
  mStdErrorFilePath = filePath;
}

qint64 ExternalProcess::write(const char *data)
{
  return mProcess->write(data);
}

QByteArray ExternalProcess::readStdout()
{
  return mProcess->readAllStandardOutput();
}

QByteArray ExternalProcess::readStderr()
{
  return mProcess->readAllStandardError();
}

void ExternalProcess::insertEnvironmentVar(const QString &varName, const QString &value)
{
  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  env.insert(varName, value);
  mProcess->setProcessEnvironment(env);
}

void ExternalProcess::appendEnvironmentValue(const QString &varName, const QString &value, int position)
{
  QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
  QString newValue = env.value(varName);
  QString separator = "";
  if (!newValue.isEmpty())
    separator = ";";
  if (position)
    newValue = newValue + separator + value;
  else
    newValue = value + separator + newValue;
  env.insert(varName, newValue);
  mProcess->setProcessEnvironment(env);
}

int ExternalProcess::error()
{
  return mProcess->error();
}

void ExternalProcess::cascadeKill(Q_PID pid){
#ifdef Q_OS_LINUX
    QProcess killer;
    QStringList params;
    params << "--ppid";
    params << QString::number(pid);
    params << "-o";
    params << "pid";
    params << "--noheaders";
    killer.start("/bin/ps",params,QIODevice::ReadOnly);
    if(killer.waitForStarted(-1))
    {
        if(killer.waitForFinished(-1))
        {
            QByteArray temp=killer.readAllStandardOutput();
            QString str=QString::fromLocal8Bit(temp);
            QStringList list=str.split("\n");

            for(int i=0;i<list.size();i++)
            {
                if(!list.at(i).isEmpty())
//                    ::kill(list.at(i).toInt(),SIGKILL);
                    cascadeKill(list.at(i).toInt());
            }
            ::kill(pid,SIGKILL);
        }
    }
#endif
}

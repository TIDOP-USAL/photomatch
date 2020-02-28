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


#ifndef PHOTOMATCH_MULTIPROCESS_H
#define PHOTOMATCH_MULTIPROCESS_H

#include <QList>

#include "photomatch/process/Process.h"


class PHOTOMATCH_EXPORT MultiProcess
  : public Process
{

    Q_OBJECT

public:

    MultiProcess();
    explicit MultiProcess(bool isSequential);
    ~MultiProcess() override;

    virtual void start() override;
    virtual void setWaitForFinished(bool wait) override;
    virtual bool isRunning() override;

    virtual QByteArray readStdout() override;
    virtual QByteArray readStderr() override;

    void appendProcess(const std::shared_ptr<Process> &process);
    void appendProcess(const QList<std::shared_ptr<Process> > &processList);
    void clearProcessList();
    int count();
    Process *at(int i);

    virtual int getSteps() override;

public slots:

    virtual void stop() override;

protected:

    void run();

private:

    QList<std::shared_ptr<Process>> mProcessList;
    bool mIsSequential;
    int mCurrentProcess;
    int mRunningCount;
    int mIdealThreadCount;
    int mFinishedCount;
    int mCurrentStep;
    bool mConcatenateMessages;
    bool mWaitForFinished;

private slots:

    void onError(int code, QString cause);
    void onAProcessFinished();
    void OnChildStatusChanged(int step, QString childMessage);
    void OnChildStatusChangedNext();
};


#endif // PHOTOMATCH_MULTIPROCESS_H

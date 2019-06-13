#ifndef FME_MULTIPROCESS_H
#define FME_MULTIPROCESS_H

#include <QList>

#include "fme/process/Process.h"


class FME_EXPORT MultiProcess
  : public Process
{

    Q_OBJECT

public:

    MultiProcess();
    MultiProcess(bool isSequential);
    ~MultiProcess() override;

    virtual void start() override;
    virtual void setWaitForFinished(bool wait) override;
    virtual bool isRunning() override;

    virtual QByteArray readStdout() override;
    virtual QByteArray readStderr() override;

    void appendProcess(Process *process);
    void appendProcess(QList<Process*> processList);
    void clearProcessList();
    int count();
    Process * at(int i);

    virtual int getSteps() override;

public slots:

    virtual void stop() override;

protected:

    void run();

private:

    QList<Process*> mProcessList;
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


#endif // FME_MULTIPROCESS_H

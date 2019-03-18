#include "Process.h"


Process::Process() :
    mStopped(false)
{
}

void Process::addIntputs(QStringList inputs)
{
    mInputs = inputs;
}

QString Process::getStartupMessage()
{
    return mStartupMessage;
}

void Process::setStartupMessage(QString message)
{
    mStartupMessage = message;
}

void Process::stop()
{
    mStopped = true;
//    quit();
}

bool Process::isStopped()
{
    return mStopped;
}

int Process::getSteps()
{
    return mSteps;
}

void Process::setSteps(int steps)
{
    mSteps = steps;
}

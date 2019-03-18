#ifndef GROUNTTRUTHBUILDERPROCESS_H
#define GROUNTTRUTHBUILDERPROCESS_H
#include "ProcessManager/ExternalProcess.h"
#include <QFileInfo>

class GrountTruthBuilderProcess: public ExternalProcess
{
public:
    GrountTruthBuilderProcess(QFileInfo *leftImage,
                              QFileInfo *rightImage);
    ~GrountTruthBuilderProcess();
};

#endif // GROUNTTRUTHBUILDERPROCESS_H

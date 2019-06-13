#ifndef GROUNTTRUTHBUILDERPROCESS_H
#define GROUNTTRUTHBUILDERPROCESS_H

#include <QFileInfo>

#include "fme/process/ExternalProcess.h"

class GrountTruthBuilderProcess: public ExternalProcess
{
public:
    GrountTruthBuilderProcess(QFileInfo *leftImage,
                              QFileInfo *rightImage);
    ~GrountTruthBuilderProcess();
};

#endif // GROUNTTRUTHBUILDERPROCESS_H

#include "GrountTruthBuilderProcess.h"
#include <QDir>

GrountTruthBuilderProcess::GrountTruthBuilderProcess(QFileInfo *leftImage,
                                                     QFileInfo *rightImage):
    ExternalProcess(QDir::currentPath()+"/GTBuilder.exe")
{
    setWorkingDir(leftImage->absolutePath());
    setStartupMessage("Launching ground truth builder...");

//    QFileInfo inputFileInfo(inputFile);

    QStringList inputs;

    inputs <<rightImage->absoluteFilePath()<< leftImage->absoluteFilePath() ;

    addIntputs(inputs);
}

GrountTruthBuilderProcess::~GrountTruthBuilderProcess()
{

}


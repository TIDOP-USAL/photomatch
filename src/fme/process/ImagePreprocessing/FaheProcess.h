#ifndef FME_FAHE_PROCESS_H
#define FME_FAHE_PROCESS_H

#include <QDir>

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess.h"

namespace fme
{

class FME_EXPORT FaheProcess
  : public ProcessConcurrent,
    public IFahe
{

public:

  FaheProcess();
  FaheProcess(const QString &imgInput,
              const QString &imgOutput,
              const QSize &blockSize);

  QString imgInput() const;
  void setImgInput(const QString &imgInput);
  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

// Process interface

public slots:

  void run() override;

// IFahe interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;

  void reset() override;

private:

  QString mImgInput;
  QString mImgOutput;
  QSize mBlockSize;

};

} // namespace fme

#endif // FME_FAHE_PROCESS_H

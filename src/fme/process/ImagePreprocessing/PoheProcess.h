#ifndef FME_POHE_PROCESS_H
#define FME_POHE_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess.h"

namespace fme
{

class FME_EXPORT PoheProcess
  : public ProcessConcurrent,
    public IPohe
{

public:

  PoheProcess();
  PoheProcess(const QString &imgInput,
              const QString &imgOutput,
              const QSize &blockSize);
  ~PoheProcess() override {}

  QString imgInput() const;
  void setImgInput(const QString &imgInput);

  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

// IPohe interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;
  void reset() override;

// ProcessConcurrent interface

protected:

  void run() override;

private:

  QString mImgInput;
  QString mImgOutput;
  QSize mBlockSize;
};

} // namespace fme

#endif // FME_POHE_PROCESS_H

#ifndef FME_CMBFHE_PROCESS_H
#define FME_CMBFHE_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess.h"

namespace fme
{

class FME_EXPORT CmbfheProcess
  : public ProcessConcurrent,
    public ICmbfhe
{

public:

  CmbfheProcess();
  CmbfheProcess(const QString &imgInput,
                const QString &imgOutput,
                const QSize &blockSize);
  ~CmbfheProcess() override {}

// ICmbfhe interface

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
  //QSize mBlockRegions;
};

} // namespace fme

#endif // FME_CMBFHE_PROCESS_H

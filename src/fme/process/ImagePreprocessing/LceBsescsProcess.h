#ifndef FME_LCE_BSESCS_PROCESS_H
#define FME_LCE_BSESCS_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess/preprocess.h"

namespace fme
{

class FME_EXPORT LceBsescsProcess
  : public ProcessConcurrent,
    public ILceBsescs
{

public:

  LceBsescsProcess();
  LceBsescsProcess(const QString &imgInput,
                   const QString &imgOutput,
                   const QSize &blockSize);
  ~LceBsescsProcess() override {}

  QString imgInput() const;
  void setImgInput(const QString &imgInput);
  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

// ILceBsescs interface

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

#endif // FME_LCE_BSESCS_PROCESS_H

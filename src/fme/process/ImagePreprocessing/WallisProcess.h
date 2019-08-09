#ifndef FME_WALLISFILTER_PROCESS_H
#define FME_WALLISFILTER_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess/preprocess.h"

namespace fme
{

class FME_EXPORT WallisProcess
  : public ProcessConcurrent,
    public IWallis
{

public:

  WallisProcess();
  WallisProcess(const QString &imgInput,
                const QString &imgOutput,
                double contrast,
                double brightness,
                int imposedAverage,
                int imposedLocalStdDev,
                int kernelSize);
  ~WallisProcess() override;

// IWallis interface

public:

  double contrast() const override;
  void setContrast(double contrast) override;
  double brightness() const override;
  void setBrightness(double brightness) override;
  int imposedAverage() const override;
  void setImposedAverage(int imposedAverage) override;
  int imposedLocalStdDev() const override;
  void setImposedLocalStdDev(int imposedLocalStdDev) override;
  int kernelSize() const override;
  void setKernelSize(int kernelSize) override;
  void reset() override;

// ProcessConcurrent interface

protected:

  void run() override;

private:

  QString mImgInput;
  QString mImgOutput;
  double mContrast;
  double mBrightness;
  int mImposedAverage;
  int mImposedLocalStdDev;
  int mKernelSize;
};

} // namespace fme

#endif // FME_WALLISFILTER_PROCESS_H

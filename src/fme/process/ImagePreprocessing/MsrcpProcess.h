#ifndef FME_MSRCP_PROCESS_H
#define FME_MSRCP_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess/preprocess.h"

namespace fme
{

class FME_EXPORT MsrcpProcess
  : public ProcessConcurrent,
    public IMsrcp
{
public:

  MsrcpProcess();
  MsrcpProcess(const QString &imgInput,
               const QString &imgOutput,
               double mSmallScale,
               double mMidScale,
               double mLargeScale);
  ~MsrcpProcess() override {}

// IMsrcp interface

public:

  double smallScale() const override;
  void setSmallScale(double smallScale) override;
  double midScale() const override;
  void setMidScale(double midScale) override;
  double largeScale() const override;
  void setLargeScale(double largeScale) override;
  void reset() override;

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mImgInput;
  QString mImgOutput;
  double mSmallScale;
  double mMidScale;
  double mLargeScale;
};

} // namespace fme

#endif // FME_MSRCP_PROCESS_H

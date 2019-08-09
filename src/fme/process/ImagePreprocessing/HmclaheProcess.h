#ifndef FME_HMCLAHE_PROCESS_H
#define FME_HMCLAHE_PROCESS_H

#include <opencv2/core.hpp>

#include <QDir>

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess/preprocess.h"

namespace fme
{

class FME_EXPORT HmclaheProcess
  : public ProcessConcurrent,
    public IHmclahe
{

public:

  HmclaheProcess();
  HmclaheProcess(const QString &imgInput,
                 const QString &imgOutput,
                 const QSize &blockSize,
                 double l, double phi);
  ~HmclaheProcess() override;

  QString imgInput() const;
  void setImgInput(const QString &imgInput);

  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

// IHmclahe interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;
  double l() const override;
  void setL(double l) override;
  double phi() const override;
  void setPhi(double phi) override;

  void reset() override;

// ProcessConcurrent interface

protected:

  void run() override;

private:

  QString mImgInput;
  QString mImgOutput;
  QSize mBlockSize;
  double mL;
  double mPhi;

};

} // namespace fme

#endif // FME_HMCLAHE_PROCESS_H

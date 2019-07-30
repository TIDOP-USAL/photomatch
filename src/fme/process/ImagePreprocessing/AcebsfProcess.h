#ifndef FME_ACEBS_PROCESS_H
#define FME_ACEBS_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess.h"

namespace fme
{

class FME_EXPORT AcebsfProcess
  : public ProcessConcurrent,
    public IAcebsf
{

public:

  AcebsfProcess();
  AcebsfProcess(const QString &imgInput,
                const QString &imgOutput,
                const QSize &blockSize,
                double l, double k1, double k2);
  ~AcebsfProcess() override;

  QString imgInput() const;
  void setImgInput(const QString &imgInput);

  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

// IAcebsf interface

public:

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;
  double l() const override;
  void setL(double l) override;
  double k1() const override;
  void setK1(double k1) override;
  double k2() const override;
  void setK2(double k2) override;

  void reset() override;

// ProcessConcurrent interface

protected:

  void run() override;

private:

  QString mImgInput;
  QString mImgOutput;
  QSize mBlockSize;
  double mL;
  double mK1;
  double mK2;
};


} // namespace fme

#endif // FME_ACEBS_PROCESS_H

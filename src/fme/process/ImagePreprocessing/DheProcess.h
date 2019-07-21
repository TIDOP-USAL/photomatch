#ifndef FME_DHE_PROCESS_H
#define FME_DHE_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess.h"

namespace fme
{

class FME_EXPORT DheProcess
  : public ProcessConcurrent,
    public IDhe
{

public:

  DheProcess();
  DheProcess(const QString &imgInput,
             const QString &imgOutput,
             int x);
  ~DheProcess() override;

  QString imgInput() const;
  void setImgInput(const QString &imgInput);

  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

// IDhe interface

public:

  int x() const override;
  void setX(int x) override;

  void reset() override;

// ProcessConcurrent interface

protected:

  void run() override;

private:

  QString mImgInput;
  QString mImgOutput;
  int mX;
};

} // namespace fme

#endif // FME_DHE_PROCESS_H

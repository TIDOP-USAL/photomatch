#ifndef FME_RSWHE_PROCESS_H
#define FME_RSWHE_PROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess/preprocess.h"

namespace fme
{

class FME_EXPORT RswheProcess
  : public ProcessConcurrent,
    public IRswhe
{

public:

  RswheProcess();
  RswheProcess(const QString &imgInput,
               const QString &imgOutput,
               int histogramDivisions,
               HistogramCut histogramCut);
  ~RswheProcess() override;

  QString imgInput() const;
  void setImgInput(const QString &imgInput);

  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

// IRswhe interface

public:

  int histogramDivisions() const override;
  void setHistogramDivisions(int histogramDivisions) override;
  HistogramCut histogramCut() const override;
  void setHistogramCut(HistogramCut histogramCut) override;
  void reset() override;

// ProcessConcurrent interface

protected:

  void run() override;

private:

  QString mImgInput;
  QString mImgOutput;
  int mHistogramDivisions;
  HistogramCut mHistogramCut;
};

} // namespace fme

#endif // FME_RSWHE_PROCESS_H

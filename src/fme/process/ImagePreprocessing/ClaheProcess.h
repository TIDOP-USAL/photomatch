#ifndef FME_CLAHE_PROCESS_H
#define FME_CLAHE_PROCESS_H

#include <opencv2/photo.hpp>

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess.h"

namespace fme
{

class FME_EXPORT ClaheProcess
  : public ProcessConcurrent,
    public IClahe
{

public:

  ClaheProcess();
  ClaheProcess(const QString &imgInput,
               const QString &imgOutput,
               double clipLimit,
               const QSize &tilesGridSize);
  ~ClaheProcess() override {}

  QString imgInput() const;
  void setImgInput(const QString &imgInput);

  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

// IClahe interface

public:

  double clipLimit() const override;
  void setClipLimit(double clipLimit) override;
  QSize tilesGridSize() const override;
  void setTilesGridSize(const QSize &tilesGridSize) override;

  void reset() override;

// ProcessConcurrent interface

protected:

  void run() override;

private:

  QString mImgInput;
  QString mImgOutput;
//  double mClipLimit;
//  QSize mTilesGridSize;
  cv::Ptr<cv::CLAHE> mCvClahe;
};

} // namespace fme

#endif // FME_CLAHE_PROCESS_H

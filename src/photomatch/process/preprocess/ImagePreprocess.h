#ifndef PHOTOMATCH_IMAGE_PREPROCESS_H
#define PHOTOMATCH_IMAGE_PREPROCESS_H

#include "photomatch/process/ProcessConcurrent.h"
#include "photomatch/core/preprocess/preprocess.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT ImagePreprocess
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  ImagePreprocess(const QString &img,
                  const QString &imgPreprocess,
                  const std::shared_ptr<ImageProcess> &preprocess,
                  int maxSize = -1);

  QString imgInput() const;
  void setImgInput(const QString &imgInput);

  QString imgOutput() const;
  void setImgOutput(const QString &imgOutput);

  void setMaxImageSize(int size);

  std::shared_ptr<ImageProcess> preprocess() const;

signals:

  void preprocessed(QString);

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mImgInput;
  QString mImgOutput;
  std::shared_ptr<ImageProcess> mPreprocess;
  int mMaxSize;
};


} // namespace photomatch

#endif // PHOTOMATCH_IMAGE_PREPROCESS_H

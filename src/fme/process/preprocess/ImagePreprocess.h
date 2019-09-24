#ifndef FME_IMAGE_PREPROCESS_H
#define FME_IMAGE_PREPROCESS_H

#include "fme/process/ProcessConcurrent.h"
#include "fme/core/preprocess/preprocess.h"

namespace fme
{

class FME_EXPORT ImagePreprocess
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


} // namespace fme

#endif // FME_IMAGE_PREPROCESS_H

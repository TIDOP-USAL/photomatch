#ifndef FME_FAHE_PREPROCESS_H
#define FME_FAHE_PREPROCESS_H

#include "fme/fme_global.h"

#include "fme/core/preprocess/preprocess.h"

#include <opencv2/photo.hpp>

#include <QString>

namespace fme
{


/*!
 * \brief Fahe image preprocess class
 */
class FME_EXPORT FaheProperties
  : public IFahe
{

public:

  FaheProperties();
  ~FaheProperties() override = default;

  virtual QSize blockSize() const override;
  virtual void setBlockSize(const QSize &blockSize) override;

// Preprocess interface

public:

  virtual void reset() override;

private:

  QSize mBlockSize;

};


/*----------------------------------------------------------------*/


class FME_EXPORT FahePreprocess
  : public FaheProperties,
    public ImageProcess
{

public:

  FahePreprocess();
  FahePreprocess(const QSize &blockSize);
  ~FahePreprocess() override;

// Preprocess interface

public:

  void reset() override;

// IFahe interface

public:

  void setBlockSize(const QSize &blockSize) override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;

};

} // namespace fme

#endif // FME_FAHE_PREPROCESS_H

#ifndef PHOTOMATCH_ACEBSF_PREPROCESS_H
#define PHOTOMATCH_ACEBSF_PREPROCESS_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/preprocess/preprocess.h"

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT AcebsfProperties
  : public IAcebsf
{

public:

  AcebsfProperties();
  AcebsfProperties(const AcebsfProperties &acebsfProperties);
  AcebsfProperties(AcebsfProperties &&acebsfProperties) PHOTOMATCH_NOEXCEPT;
  ~AcebsfProperties() override {}

  AcebsfProperties &operator = (const AcebsfProperties& acebsfProperties);
  AcebsfProperties &operator = (AcebsfProperties &&acebsfProperties) PHOTOMATCH_NOEXCEPT;

// IAcebs interface

public:

  virtual QSize blockSize() const override;
  virtual void setBlockSize(const QSize &blockSize) override;
  virtual double l() const override;
  virtual void setL(double l) override;
  virtual double k1() const override;
  virtual void setK1(double k1) override;
  virtual double k2() const override;
  virtual void setK2(double k2) override;

// Preprocess interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  QSize mBlockSize;
  double mL;
  double mK1;
  double mK2;

};



class PHOTOMATCH_EXPORT AcebsfPreprocess
  : public AcebsfProperties,
    public ImageProcess
{

public:

  AcebsfPreprocess();
  AcebsfPreprocess(const AcebsfPreprocess &acebsfPreprocess);
  AcebsfPreprocess(AcebsfPreprocess &&acebsfPreprocess) PHOTOMATCH_NOEXCEPT;
  AcebsfPreprocess(const QSize &blockSize,
                   double l,
                   double k1,
                   double k2);
  ~AcebsfPreprocess() override;

// ImageProcess interface

public:

  cv::Mat process(const cv::Mat &img) override;
};

} // namespace photomatch

#endif // PHOTOMATCH_ACEBSF_PREPROCESS_H

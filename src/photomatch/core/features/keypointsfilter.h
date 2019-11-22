#ifndef PHOTOMATCH_KEYPOINTSFILTER_H
#define PHOTOMATCH_KEYPOINTSFILTER_H

#include "photomatch/photomatch_global.h"

#include <vector>

#include <opencv2/features2d.hpp>

#include <tidop/core/flags.h>

namespace photomatch
{


class PHOTOMATCH_EXPORT KeyPointsFilter
{

public:

  enum class Type
  {
    n_best,
    size,
    duplicated,
    mask
  };

public:

  KeyPointsFilter(Type type) : mFilterType(type) {}
  virtual ~KeyPointsFilter() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  Type type() const { return mFilterType.flags(); }

protected:

  tl::EnumFlags<Type> mFilterType;
};
ALLOW_BITWISE_FLAG_OPERATIONS(KeyPointsFilter::Type)


/*----------------------------------------------------------------*/


class KeyPointsFilterProcess
{

public:

  KeyPointsFilterProcess() {}
  virtual ~KeyPointsFilterProcess() = default;

  virtual bool filter(const std::vector<cv::KeyPoint> &keypoins,
                      std::vector<cv::KeyPoint> &filteredKeypoins) = 0;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT KeyPointsFilterNBestProperties
  : public KeyPointsFilter
{

public:

  KeyPointsFilterNBestProperties();
  ~KeyPointsFilterNBestProperties() override = default;

  virtual int nPoints() const;
  virtual void setNPoints(int nPoints);

// KeyPointsFilter interface

public:

  virtual void reset() override;

private:

  int mPointsNumber;
};


/*----------------------------------------------------------------*/


class KeyPointsFilterNBest
  : public KeyPointsFilterNBestProperties,
    public KeyPointsFilterProcess
{

public:

  KeyPointsFilterNBest();
  KeyPointsFilterNBest(int nPoints);
  ~KeyPointsFilterNBest() override = default;

// KeyPointsFilterNBestProperties interface

public:

  void setNPoints(int nPoints) override;

// KeyPointsFilter interface

public:

  void reset() override;

// KeyPointsFilterProcess interface

public:

  bool filter(const std::vector<cv::KeyPoint> &keypoins, std::vector<cv::KeyPoint> &filteredKeypoins) override;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT KeyPointsFilterBySizeProperties
  : public KeyPointsFilter
{

public:

  KeyPointsFilterBySizeProperties();
  ~KeyPointsFilterBySizeProperties() override = default;

  virtual double minSize() const;
  virtual void setMinSize(double minSize);

  virtual double maxSize() const;
  virtual void setMaxSize(double maxSize);

// KeyPointsFilter interface

public:

  virtual void reset() override;

private:

  double mMinSize;
  double mMaxSize;

};


/*----------------------------------------------------------------*/


class KeyPointsFilterBySize
  : public KeyPointsFilterBySizeProperties,
    public KeyPointsFilterProcess
{

public:

  KeyPointsFilterBySize();
  KeyPointsFilterBySize(double minSize, double maxSize);
  ~KeyPointsFilterBySize() override = default;

// KeyPointsFilterBySizeProperties interface

public:

  void setMinSize(double minSize) override;
  void setMaxSize(double maxSize) override;

// KeyPointsFilterProcess interface

public:

  bool filter(const std::vector<cv::KeyPoint> &keypoins, std::vector<cv::KeyPoint> &filteredKeypoins) override;

// KeyPointsFilter interface

public:

  void reset() override;

};


} // namespace photomatch

#endif // PHOTOMATCH_KEYPOINTSFILTER_H

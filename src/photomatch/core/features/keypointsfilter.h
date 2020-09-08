/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#ifndef PHOTOMATCH_KEYPOINTSFILTER_H
#define PHOTOMATCH_KEYPOINTSFILTER_H

#include "photomatch/photomatch_global.h"

#include <vector>

#include <opencv2/features2d.hpp>

#include <tidop/core/flags.h>

#include <QString>

namespace photomatch
{


class PHOTOMATCH_EXPORT KeyPointsFilter
{

public:

  enum class Type
  {
    n_best,
    size,
    remove_duplicated,
    mask
  };

public:

  KeyPointsFilter() {}
  virtual ~KeyPointsFilter() = default;

  /*!
   * \brief Recover the default values
   */
  virtual void reset() = 0;

  /*!
   * \brief type of keypoints filter
   * \return filter type
   */
  virtual Type type() const = 0;
  virtual QString name() const = 0;

};
ALLOW_BITWISE_FLAG_OPERATIONS(KeyPointsFilter::Type)



class PHOTOMATCH_EXPORT KeyPointsFilterBase
  : public KeyPointsFilter
{

public:

  KeyPointsFilterBase(Type type) : mFilterType(type) {}
  ~KeyPointsFilterBase() override = default;

  /*!
   * \brief type of keypoints filter
   * \return filter type
   */
  Type type() const override
  { 
    return mFilterType.flags(); 
  }

protected:

  tl::EnumFlags<Type> mFilterType;
};



/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT KeyPointsFilterProcess
{

public:

  KeyPointsFilterProcess() {}
  virtual ~KeyPointsFilterProcess() = default;

  /*!
   * \brief filter
   * \param[in] keypoints
   * \return Filtered Keypoints
   */
  virtual std::vector<cv::KeyPoint> filter(const std::vector<cv::KeyPoint> &keypoints) = 0;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT KeyPointsFilterNBestProperties
  : public KeyPointsFilterBase
{

public:

  KeyPointsFilterNBestProperties();
  ~KeyPointsFilterNBestProperties() override = default;

  /*!
   * \brief Number of points to retain
   * \return Number of points
   */
  virtual int nPoints() const;

  /*!
   * \brief Set the number of points to retain
   * \param[in] nPoints number of points to retain
   */
  virtual void setNPoints(int nPoints);

// KeyPointsFilter interface

public:

  void reset() override;
  QString name() const final;

private:

  int mPointsNumber;
};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT KeyPointsFilterNBest
  : public KeyPointsFilterNBestProperties,
    public KeyPointsFilterProcess
{

public:

  KeyPointsFilterNBest();
  explicit KeyPointsFilterNBest(int nPoints);
  ~KeyPointsFilterNBest() override = default;

// KeyPointsFilterNBestProperties interface

public:

  void setNPoints(int nPoints) override;

// KeyPointsFilter interface

public:

  void reset() override;

// KeyPointsFilterProcess interface

public:

  std::vector<cv::KeyPoint> filter(const std::vector<cv::KeyPoint> &keypoints) override;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT KeyPointsFilterBySizeProperties
  : public KeyPointsFilterBase
{

public:

  KeyPointsFilterBySizeProperties();
  ~KeyPointsFilterBySizeProperties() override = default;

  /*!
   * \brief Minimum size
   * \return Minimum size
   */
  virtual double minSize() const;

  /*!
   * \brief set minimum size
   * \param[in] minSize
   */
  virtual void setMinSize(double minSize);

  /*!
   * \brief maximum size
   * \return maximum size
   */
  virtual double maxSize() const;

  /*!
   * \brief Set maximum size
   * \param[in] maxSize Maximum size
   */
  virtual void setMaxSize(double maxSize);

// KeyPointsFilter interface

public:

  void reset() override;
  QString name() const final;

private:

  double mMinSize;
  double mMaxSize;

};


/*----------------------------------------------------------------*/


class PHOTOMATCH_EXPORT KeyPointsFilterBySize
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

  std::vector<cv::KeyPoint> filter(const std::vector<cv::KeyPoint> &keypoints) override;

// KeyPointsFilter interface

public:

  void reset() override;

};



/*----------------------------------------------------------------*/

class PHOTOMATCH_EXPORT KeyPointsFilterRemoveDuplicatedProperties
  : public KeyPointsFilterBase
{

public:

  KeyPointsFilterRemoveDuplicatedProperties();
  ~KeyPointsFilterRemoveDuplicatedProperties() override = default;

// KeyPointsFilter interface

public:

  void reset() override;
  QString name() const final;

};


/*----------------------------------------------------------------*/



class PHOTOMATCH_EXPORT KeyPointsFilterRemoveDuplicated
  : public KeyPointsFilterRemoveDuplicatedProperties,
    public KeyPointsFilterProcess
{

public:

  KeyPointsFilterRemoveDuplicated();
  ~KeyPointsFilterRemoveDuplicated() override = default;

// KeyPointsFilterProcess interface

public:

  std::vector<cv::KeyPoint> filter(const std::vector<cv::KeyPoint> &keypoints) override;

// KeyPointsFilter interface

public:

  void reset() override;
};


} // namespace photomatch

#endif // PHOTOMATCH_KEYPOINTSFILTER_H

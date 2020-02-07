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


#ifndef PHOTOMATCH_FEATURE_EXTRACTOR_PROCESS_H
#define PHOTOMATCH_FEATURE_EXTRACTOR_PROCESS_H

#include "photomatch/process/ProcessConcurrent.h"
#include "photomatch/core/features/features.h"
#include "photomatch/core/features/keypointsfilter.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT FeatureExtractor
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  /*!
   * \brief Constructor FeatureExtractor
   * \param[in] image Image file
   * \param[in] features Features output file
   * \param[in] imageScale Image scale
   * \param[in] keypointDetector KeypointDetector object
   * \param[in] descriptorExtractor DescriptorExtractor object
   * \param[in] keyPointsFiltersProcess KeyPointsFilterProcess object
   */
  FeatureExtractor(const QString &image,
                   const QString &features,
                   double imageScale,
                   const std::shared_ptr<KeypointDetector> &keypointDetector,
                   const std::shared_ptr<DescriptorExtractor> &descriptorExtractor,
                   const std::list<std::shared_ptr<KeyPointsFilterProcess>> &keyPointsFiltersProcess);


  QString image() const;
  void setImage(const QString &image);
  QString features() const;
  void setFeatures(const QString &features);
  void setScale(double scale);

  std::shared_ptr<KeypointDetector> keypointDetector() const;
  std::shared_ptr<DescriptorExtractor> descriptorExtractor() const;

signals:

  void featuresExtracted(QString);

// ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mImage;
  QString mFeatures;
  double mImageScale;
  std::shared_ptr<KeypointDetector> mKeypointDetector;
  std::shared_ptr<DescriptorExtractor> mDescriptorExtractor;
  std::list<std::shared_ptr<KeyPointsFilterProcess>> mKeyPointsFiltersProcess;
};


} // namespace photomatch

#endif // PHOTOMATCH_FEATURE_EXTRACTOR_PROCESS_H

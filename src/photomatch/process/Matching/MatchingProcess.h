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


#ifndef PHOTOMATCH_MATCHING_PROCESS_H
#define PHOTOMATCH_MATCHING_PROCESS_H

#include "photomatch/process/ProcessConcurrent.h"
#include "photomatch/core/features/matcher.h"

namespace photomatch
{

class PHOTOMATCH_EXPORT MatchingProcess
  : public ProcessConcurrent
{

  Q_OBJECT

public:

  MatchingProcess(const QString &queryDescriptors,
                  const QString &trainDescriptors,
                  const QString &matches,
                  const std::shared_ptr<MatchingAlgorithm> &descriptorMatcher,
                  const QString &queryImage,
                  const QString &trainImage);

  QString queryDescriptors() const;
  void setQueryDescriptors(const QString &descriptors);

  QString trainDescriptors() const;
  void setTrainDescriptors(const QString &descriptors);

  QString matches() const;
  void setMatches(const QString &matches);

  QString queryImage() const;
  void setQueryImage(const QString &queryImage);

  QString trainImage() const;
  void setTrainImage(const QString &trainImage);

signals:

  void matchCompute(QString, QString, QString);

  // ProcessConcurrent interface

protected:

  void run() override;

protected:

  QString mQueryDescriptors;
  QString mTrainDescriptors;
  QString mMatches;
  std::shared_ptr<MatchingAlgorithm> mDescriptorMatcher;
  QString mQueryImage;
  QString mTrainImage;
};

} // namespace photomatch

#endif // PHOTOMATCH_MATCHING_PROCESS_H

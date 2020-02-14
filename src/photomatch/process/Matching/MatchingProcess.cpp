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


#include "MatchingProcess.h"

#include "photomatch/core/features/featio.h"
#include "photomatch/core/features/matchio.h"

#include <tidop/core/messages.h>

#include <QFileInfo>
#include <QImageReader>

namespace photomatch
{

MatchingProcess::MatchingProcess(const QString &queryDescriptors,
                                 const QString &trainDescriptors,
                                 const QString &matches,
                                 const std::shared_ptr<MatchingAlgorithm> &descriptorMatcher,
                                 const QString &queryImage,
                                 const QString &trainImage)
  : ProcessConcurrent(),
    mQueryDescriptors(queryDescriptors),
    mTrainDescriptors(trainDescriptors),
    mMatches(matches),
    mDescriptorMatcher(descriptorMatcher),
    mQueryImage(queryImage),
    mTrainImage(trainImage)
{

}

QString MatchingProcess::queryDescriptors() const
{
  return mQueryDescriptors;
}

void MatchingProcess::setQueryDescriptors(const QString &descriptors)
{
  mQueryDescriptors = descriptors;
}

QString MatchingProcess::trainDescriptors() const
{
  return mTrainDescriptors;
}

void MatchingProcess::setTrainDescriptors(const QString &descriptors)
{
  mTrainDescriptors = descriptors;
}

QString MatchingProcess::matches() const
{
  return mMatches;
}

void MatchingProcess::setMatches(const QString &matches)
{
  mMatches = matches;
}

void MatchingProcess::run()
{
  try {

    std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(mQueryDescriptors);
    featuresRead->read();
    std::vector<cv::KeyPoint> keyPoints1 = featuresRead->keyPoints();
    cv::Mat descriptors1 = featuresRead->descriptors();

    featuresRead = FeaturesReaderFactory::createReader(mTrainDescriptors);
    featuresRead->read();
    std::vector<cv::KeyPoint> keyPoints2 = featuresRead->keyPoints();
    cv::Mat descriptors2 = featuresRead->descriptors();

    std::vector<cv::DMatch> wrongMatches;
    std::vector<cv::DMatch> goodMatches;

    QSize query_size;
    QSize train_size;
    if (mQueryImage.isEmpty() == false && mTrainImage.isEmpty() == false){
      QImageReader imageReader(mQueryImage);
      query_size = imageReader.size();
      imageReader.setFileName(mTrainImage);
      train_size = imageReader.size();
    }

    mDescriptorMatcher->compute(descriptors1, descriptors2, keyPoints1, keyPoints2, &goodMatches, &wrongMatches, query_size, train_size);

    std::unique_ptr<MatchesWriter> writer = MatchesWriterFactory::createWriter(mMatches);
    writer->setGoodMatches(goodMatches);
    writer->setWrongMatches(wrongMatches);
    writer->write();

    QByteArray ba = mMatches.toLocal8Bit();
    const char *cfeat = ba.data();
    msgInfo("Write matches at: %s", cfeat);

    emit matchCompute(QFileInfo(mQueryDescriptors).baseName(), QFileInfo(mTrainDescriptors).baseName(), mMatches);
    emit statusChangedNext();

  } catch (std::exception &e) {
    msgError(e.what());
  }
}

QString MatchingProcess::trainImage() const
{
    return mTrainImage;
}

void MatchingProcess::setTrainImage(const QString &trainImage)
{
    mTrainImage = trainImage;
}

QString MatchingProcess::queryImage() const
{
    return mQueryImage;
}

void MatchingProcess::setQueryImage(const QString &queryImage)
{
    mQueryImage = queryImage;
}

} // namespace photomatch

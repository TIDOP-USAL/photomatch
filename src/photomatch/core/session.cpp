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


#include "session.h"

#include "photomatch/core/preprocess/preprocess.h"
#include "photomatch/core/features/features.h"
#include "photomatch/core/features/matcher.h"

#include <QFileInfo>

namespace photomatch
{

SessionImp::SessionImp()
  : Session(),
    mName(""),
    mDescription(""),
    mMaxImageSize(2000)
{

}

SessionImp::SessionImp(const QString &name, const QString &description)
  : Session(),
    mName(name),
    mDescription(description),
    mMaxImageSize(2000)
{

}

QString SessionImp::name() const
{
  return mName;
}

void SessionImp::setName(const QString &name)
{
  mName = name;
}

QString SessionImp::description() const
{
  return mDescription;
}

void SessionImp::setDescription(const QString &description)
{
  mDescription = description;
}

int SessionImp::maxImageSize() const
{
  return mMaxImageSize;
}

void SessionImp::setMaxImageSize(int size)
{
  mMaxImageSize = size;
}

void SessionImp::setFullImageSize(bool fullImageSize)
{
  mMaxImageSize = fullImageSize ? -1 : 2000;
}

bool SessionImp::fullImageSize() const
{
  return (mMaxImageSize == -1);
}

std::shared_ptr<Preprocess> SessionImp::preprocess()
{
  return mPreprocess;
}

void SessionImp::setPreprocess(const std::shared_ptr<Preprocess> &preprocess)
{
  mPreprocess = preprocess;
}

std::shared_ptr<Feature> SessionImp::detector()
{
  return mFeatureDetector;
}

void SessionImp::setDetector(const std::shared_ptr<Feature> &detector)
{
  mFeatureDetector = detector;
}

std::shared_ptr<Feature> SessionImp::descriptor()
{
  return mFeatureDescriptor;
}

void SessionImp::setDescriptor(const std::shared_ptr<Feature> &descriptor)
{
  mFeatureDescriptor = descriptor;
}

std::shared_ptr<MatchingMethod> SessionImp::matchingMethod()
{
  return mMatchingMethod;
}

void SessionImp::setMatchingMethod(const std::shared_ptr<MatchingMethod> &matcher)
{
  mMatchingMethod = matcher;
}

std::shared_ptr<MatchingStrategy> SessionImp::matchingStrategy()
{
  return mMatchingStrategy;
}

void SessionImp::setMatchingStrategy(const std::shared_ptr<MatchingStrategy> &matchingStrategy)
{
  mMatchingStrategy = matchingStrategy;
}

void SessionImp::addPreprocessImage(const QString &img)
{
  for (auto &image : mPreprocessImages) {
    if (image.compare(img) == 0) {
      return;
    }
  }
  mPreprocessImages.push_back(img);
}

void SessionImp::deletePreprocessImage(const QString &img)
{
  for (size_t i = 0; i < mPreprocessImages.size(); i++){
    if (mPreprocessImages[i].compare(img) == 0) {
      mPreprocessImages.erase(mPreprocessImages.begin()+ static_cast<long long>(i));
      break;
    }
  }
}

void SessionImp::deletePreprocessImages()
{
  mPreprocessImages.clear();
}

std::vector<QString> SessionImp::preprocessImages() const
{
  return mPreprocessImages;
}

QString SessionImp::preprocessImage(const QString &image) const
{
  QString preprocess_image;
  for (size_t i = 0; i < mPreprocessImages.size(); i++){
    QString pre_file_name = QFileInfo(mPreprocessImages[i]).baseName();
    if (pre_file_name.compare(image) == 0) {
      preprocess_image = mPreprocessImages[i];
      break;
    }
  }
  return preprocess_image;
}

void SessionImp::addFeatures(const QString &feat)
{
  for (auto &f : mFeatures) {
    if (f.compare(feat) == 0) {
      return;
    }
  }
  mFeatures.push_back(feat);
}

void SessionImp::deleteFeatures(const QString &feat)
{
  for (size_t i = 0; i < mFeatures.size(); i++){
    if (mFeatures[i].compare(feat) == 0) {
      mFeatures.erase(mFeatures.begin()+ static_cast<long long>(i));
      break;
    }
  }
}

void SessionImp::deleteFeatures()
{
  mFeatures.clear();
}

std::vector<QString> SessionImp::features() const
{
  return mFeatures;
}

QString SessionImp::features(const QString &image) const
{
  QString feat_file;
  for (size_t i = 0; i < mFeatures.size(); i++){
    QString feat_file_name = QFileInfo(mFeatures[i]).baseName();
    if (feat_file_name.compare(image) == 0) {
      feat_file = mFeatures[i];
      break;
    }
  }
  return feat_file;
}

void SessionImp::addMatches(const QString &img1, const QString &img2, const QString &fileMatch)
{
  for (auto &f : mImagesPairs[img1]) {
    if (f.first.compare(img2) == 0 && f.second.compare(fileMatch) == 0) {
      return;
    }
  }
  mImagesPairs[img1].push_back(std::make_pair(img2, fileMatch));
  mImagesPairs[img2].push_back(std::make_pair(img1, fileMatch));
}

void SessionImp::deleteMatches(const QString &img1, const QString &img2, const QString &fileMatch)
{
  for (size_t i = 0; i < mImagesPairs[img1].size(); i++){
    if (mImagesPairs[img1][i].first.compare(img2) == 0 && mImagesPairs[img1][i].second.compare(fileMatch) == 0) {
      mImagesPairs[img1].erase(mImagesPairs[img1].begin()+ static_cast<long long>(i));
    }
  }
}

void SessionImp::deleteMatches(const QString &img1)
{
  mImagesPairs[img1].clear();
}

void SessionImp::deleteMatches()
{
  mImagesPairs.clear();
}

std::map<QString, std::vector<std::pair<QString, QString>>> SessionImp::matches() const
{
  return mImagesPairs;
}

std::vector<std::pair<QString, QString>> SessionImp::matches(const QString &image) const
{
  std::vector<std::pair<QString, QString>> pairs;
  for (auto &matches : mImagesPairs){
    if (image.compare(matches.first) == 0) {
      pairs = matches.second;
      break;
    }
  }
  return pairs;
}

QString SessionImp::passPoints() const
{
  return mPassPoints;
}

void SessionImp::setPassPoints(const QString &passPoint)
{
  mPassPoints = passPoint;
}

void SessionImp::clear()
{
  mName.clear();
  mDescription.clear();
  mMaxImageSize = 2000;
  mPreprocess.reset();
  mFeatureDetector.reset();
  mFeatureDescriptor.reset();
  mMatchingMethod.reset();
  mMatchingStrategy.reset();
  mPreprocessImages.clear();
  mFeatures.clear();
  mImagesPairs.clear();
  mPassPoints.clear();
}

} // namespace photomatch

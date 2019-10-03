#include "session.h"

#include "fme/core/preprocess/preprocess.h"
#include "fme/core/features/features.h"
#include "fme/core/features/matcher.h"

#include <QFileInfo>

namespace fme
{

Session::Session()
  : ISession(),
    mName(""),
    mDescription(""),
    mMaxImageSize(2000)
{

}

Session::Session(const QString &name, const QString &description)
  : ISession(),
    mName(name),
    mDescription(description),
    mMaxImageSize(2000)
{

}

QString Session::name() const
{
  return mName;
}

void Session::setName(const QString &name)
{
  mName = name;
}

QString Session::description() const
{
  return mDescription;
}

void Session::setDescription(const QString &description)
{
  mDescription = description;
}

int Session::maxImageSize() const
{
  return mMaxImageSize;
}

void Session::setMaxImageSize(int size)
{
  mMaxImageSize = size;
}

void Session::setFullImageSize(bool fullImageSize)
{
  mMaxImageSize = fullImageSize ? -1 : 2000;
}

bool Session::fullImageSize() const
{
  return (mMaxImageSize == -1);
}

std::shared_ptr<Preprocess> Session::preprocess()
{
  return mPreprocess;
}

void Session::setPreprocess(const std::shared_ptr<Preprocess> &preprocess)
{
  mPreprocess = preprocess;
}

std::shared_ptr<Feature> Session::detector()
{
  return mFeatureDetector;
}

void Session::setDetector(const std::shared_ptr<Feature> &detector)
{
  mFeatureDetector = detector;
}

std::shared_ptr<Feature> Session::descriptor()
{
  return mFeatureDescriptor;
}

void Session::setDescriptor(const std::shared_ptr<Feature> &descriptor)
{
  mFeatureDescriptor = descriptor;
}

std::shared_ptr<Match> Session::matcher()
{
  return mMatcher;
}

void Session::setMatcher(const std::shared_ptr<Match> &matcher)
{
  mMatcher = matcher;
}

std::shared_ptr<IRobustMatcherRefinement> Session::robustMatcherRefinement()
{
  return mRobustMatcherRefinement;
}

void Session::setRobustMatcherRefinement(const std::shared_ptr<IRobustMatcherRefinement> &robustMatcherRefinement)
{
  mRobustMatcherRefinement = robustMatcherRefinement;
}

void Session::addPreprocessImage(const QString &img)
{
  for (auto &image : mPreprocessImages) {
    if (image.compare(img) == 0) {
      return;
    }
  }
  mPreprocessImages.push_back(img);
}

void Session::deletePreprocessImage(const QString &img)
{
  for (size_t i = 0; i < mPreprocessImages.size(); i++){
    if (mPreprocessImages[i].compare(img) == 0) {
      mPreprocessImages.erase(mPreprocessImages.begin()+ static_cast<long long>(i));
      break;
    }
  }
}

void Session::deletePreprocessImages()
{
  mPreprocessImages.clear();
}

std::vector<QString> Session::preprocessImages() const
{
  return mPreprocessImages;
}

void Session::addFeatures(const QString &feat)
{
  for (auto &f : mFeatures) {
    if (f.compare(feat) == 0) {
      return;
    }
  }
  mFeatures.push_back(feat);
}

void Session::deleteFeatures(const QString &feat)
{
  for (size_t i = 0; i < mFeatures.size(); i++){
    if (mFeatures[i].compare(feat) == 0) {
      mFeatures.erase(mFeatures.begin()+ static_cast<long long>(i));
      break;
    }
  }
}

void Session::deleteFeatures()
{
  mFeatures.clear();
}

std::vector<QString> Session::features() const
{
  return mFeatures;
}

QString Session::features(const QString &image) const
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

void Session::addMatches(const QString &img1, const QString &img2, const QString &fileMatch)
{
  for (auto &f : mImagesPairs[img1]) {
    if (f.first.compare(img2) == 0 && f.second.compare(fileMatch) == 0) {
      return;
    }
  }
  mImagesPairs[img1].push_back(std::make_pair(img2, fileMatch));
  mImagesPairs[img2].push_back(std::make_pair(img1, fileMatch));
}

void Session::deleteMatches(const QString &img1, const QString &img2, const QString &fileMatch)
{
  for (size_t i = 0; i < mImagesPairs[img1].size(); i++){
    if (mImagesPairs[img1][i].first.compare(img2) == 0 && mImagesPairs[img1][i].second.compare(fileMatch) == 0) {
      mImagesPairs[img1].erase(mImagesPairs[img1].begin()+ static_cast<long long>(i));
    }
  }
}

void Session::deleteMatches(const QString &img1)
{
  mImagesPairs[img1].clear();
}

void Session::deleteMatches()
{
  mImagesPairs.clear();
}

std::map<QString, std::vector<std::pair<QString, QString>>> Session::matches() const
{
  return mImagesPairs;
}

std::vector<std::pair<QString, QString>> Session::matches(const QString &image) const
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

void Session::clear()
{
  mName.clear();
  mDescription.clear();
  mMaxImageSize = 2000;
}

} // namespace fme

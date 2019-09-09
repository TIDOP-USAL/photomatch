#include "matcher.h"

#include <tidop/core/messages.h>

#include <opencv2/xfeatures2d.hpp>

#include <QFileInfo>

namespace fme
{


/*----------------------------------------------------------------*/


FlannMatcherProperties::FlannMatcherProperties()
  : IFlannMatcher()
{
}

FlannMatcherProperties::~FlannMatcherProperties()
{
}

void FlannMatcherProperties::reset()
{
}

QString FlannMatcherProperties::name() const
{
  return QString("Flann Based Matching");
}


/*----------------------------------------------------------------*/


FlannMatcher::FlannMatcher()
  : FlannMatcherProperties(),
    DescriptorMatcher()
{
  mFlannBasedMatcher = cv::FlannBasedMatcher::create();
}

FlannMatcher::~FlannMatcher()
{

}

void FlannMatcher::match(cv::InputArray &queryDescriptors,
                         cv::InputArray &trainDescriptors,
                         std::vector<cv::DMatch> &matches,
                         cv::InputArray mask)
{
  mFlannBasedMatcher->match(queryDescriptors, trainDescriptors, matches, mask);
}

void FlannMatcher::reset()
{
  mFlannBasedMatcher = cv::FlannBasedMatcher::create();
}



/*----------------------------------------------------------------*/



BruteForceMatcherProperties::BruteForceMatcherProperties()
  : IBruteForceMatcher(),
    mNormType(BruteForceMatcherProperties::Norm::l2)
{
}

BruteForceMatcherProperties::~BruteForceMatcherProperties()
{
}

void BruteForceMatcherProperties::reset()
{
  mNormType = BruteForceMatcherProperties::Norm::l2;
}

QString BruteForceMatcherProperties::name() const
{
  return QString("Brute Force Matching");
}

BruteForceMatcherProperties::Norm BruteForceMatcherProperties::normType() const
{
  return mNormType;
}

void BruteForceMatcherProperties::setNormType(IBruteForceMatcher::Norm normType)
{
  mNormType = normType;
}

/*----------------------------------------------------------------*/


BruteForceMatcher::BruteForceMatcher()
  : BruteForceMatcherProperties(),
    DescriptorMatcher()
{
  update();
}

BruteForceMatcher::BruteForceMatcher(IBruteForceMatcher::Norm normType)
  : BruteForceMatcherProperties(),
    DescriptorMatcher()
{
  BruteForceMatcherProperties::setNormType(normType);
  update();
}

void BruteForceMatcher::update()
{
  int norm = cv::NORM_L2;
  BruteForceMatcherProperties::Norm norm_type = BruteForceMatcherProperties::normType();
  if (norm_type == BruteForceMatcherProperties::Norm::l1) {
    norm = cv::NORM_L1;
  } else if (norm_type == BruteForceMatcherProperties::Norm::l2) {
    norm = cv::NORM_L2;
  } else if (norm_type == BruteForceMatcherProperties::Norm::hamming) {
    norm = cv::NORM_HAMMING;
  } else if (norm_type == BruteForceMatcherProperties::Norm::hamming2) {
    norm = cv::NORM_HAMMING2;
  }

  mBFMatcher = cv::BFMatcher::create(norm);
}

void BruteForceMatcher::match(cv::InputArray &queryDescriptors,
                                 cv::InputArray &trainDescriptors,
                                 std::vector<cv::DMatch> &matches,
                                 cv::InputArray mask)
{
  //mBFMatcher->knnMatch(queryDescriptors, trainDescriptors, matches, 2, mask);
  mBFMatcher->match(queryDescriptors, trainDescriptors, matches, mask);
}

void BruteForceMatcher::reset()
{
  BruteForceMatcherProperties::reset();
  update();
}

void BruteForceMatcher::setNormType(IBruteForceMatcher::Norm normType)
{
  BruteForceMatcherProperties::setNormType(normType);
}


/*----------------------------------------------------------------*/


void matchesWrite(const QString &fname, const std::vector<cv::DMatch> &matches)
{

  QByteArray ba = fname.toLocal8Bit();
  const char *matches_file = ba.data();
  QString ext = QFileInfo(fname).suffix();
  int flags = 0;
  if (ext.compare("xml") == 0) {
    flags = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_XML;
  } else if (ext.compare("yml") == 0) {
    flags = cv::FileStorage::WRITE | cv::FileStorage::FORMAT_YAML;
  } else if (ext.compare("bin") == 0) {

  } else {
    ba = ext.toLocal8Bit();
    const char *cext = ba.data();
    msgError("file extension '%s' not valid", cext);
    return;
  }

  if (ext.compare("bin") == 0) {
    FILE* fp = std::fopen(matches_file, "wb");
    if (fp) {
      // Cabecera
      int size = static_cast<int>(matches.size());
      std::fwrite("TIDOPLIB-Matching-#01", sizeof("TIDOPLIB-Matching-#01"), 1, fp);
      std::fwrite(&size, sizeof(int32_t), 1, fp);
      char extraHead[100]; // Reserva de espacio para futuros usos
      std::fwrite(&extraHead, sizeof(char), 100, fp);
      //Cuerpo
      for (size_t i = 0; i < matches.size(); i++) {
        std::fwrite(&matches[i].queryIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&matches[i].trainIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&matches[i].imgIdx, sizeof(int32_t), 1, fp);
        std::fwrite(&matches[i].distance, sizeof(float), 1, fp);
      }
      std::fclose(fp);
    } else {
      //msgError("No pudo escribir archivo %s", matches_file);
    }
  } else {
    cv::FileStorage fs(matches_file, flags);
    if (fs.isOpened()) {
      if (!matches.empty()) write(fs, "matches", matches);
      fs.release();
    } else {
      //msgError("No pudo escribir archivo %s", matches_file);
    }
  }
}

void matchesRead(const QString &fname, std::vector<cv::DMatch> &matches)
{
  QByteArray ba = fname.toLocal8Bit();
  const char *feat_file = ba.data();
  QString ext = QFileInfo(fname).suffix();
  if (ext.isEmpty() == false) {
    if (ext.compare("bin") == 0) {
      if (FILE* fp = std::fopen(feat_file, "rb")) {
        //cabecera
        char h[22];
        int size;
        char extraHead[100];
        std::fread(h, sizeof(char), 22, fp);
        std::fread(&size, sizeof(int32_t), 1, fp);
        std::fread(&extraHead, sizeof(char), 100, fp);
        //Cuerpo
        matches.resize(static_cast<size_t>(size));
        for (auto &match : matches) {
          std::fread(&match.queryIdx, sizeof(int32_t), 1, fp);
          std::fread(&match.trainIdx, sizeof(int32_t), 1, fp);
          std::fread(&match.imgIdx, sizeof(int32_t), 1, fp);
          std::fread(&match.distance, sizeof(float), 1, fp);
        }
        std::fclose(fp);
      } /*else
        msgError("No pudo leer archivo %s", fname);*/
    } else if (ext.compare("xml") == 0 || ext.compare("yml") == 0) {

      cv::FileStorage fs(feat_file, cv::FileStorage::READ);
      if (fs.isOpened()) {
        matches.resize(0);
        fs["matches"] >> matches;
        fs.release();
      } else {
        //msgError("No pudo leer archivo %s", fname.c_str());
      }
    }
  } /*else msgError("Fichero no valido: %s", fname);*/
}


/*----------------------------------------------------------------*/


//DescriptorMatcherProperties::DescriptorMatcherProperties()
//  : IDescriptorMatcher(),
//    mMatchingMethod("BRUTE_FORCE"),
//    mNorm("NORM_L2"),
//    mRatio(0.8),
//    mDistance(0.7),
//    mConfidence(0.999),
//    mCrossMatching(true)
//{

//}

//DescriptorMatcherProperties::~DescriptorMatcherProperties()
//{

//}

//QString DescriptorMatcherProperties::matchingMethod() const
//{
//  return mMatchingMethod;
//}

//QString DescriptorMatcherProperties::normType() const
//{
//  return mNorm;
//}

//double DescriptorMatcherProperties::ratio() const
//{
//  return mRatio;
//}

//double DescriptorMatcherProperties::distance() const
//{
//  return mDistance;
//}

//double DescriptorMatcherProperties::confidence() const
//{
//  return mConfidence;
//}

//bool DescriptorMatcherProperties::crossMatching() const
//{
//  return mCrossMatching;
//}

//void DescriptorMatcherProperties::setMatchingMethod(const QString &matchingMethod)
//{
//  mMatchingMethod = matchingMethod;
//}

//void DescriptorMatcherProperties::setNormType(const QString &normType)
//{
//  mNorm = normType;
//}

//void DescriptorMatcherProperties::setRatio(double ratio)
//{
//  mRatio = ratio;
//}

//void DescriptorMatcherProperties::setDistance(double distance)
//{
//  mDistance = distance;
//}

//void DescriptorMatcherProperties::setConfidence(double confidence)
//{
//  mConfidence = confidence;
//}

//void DescriptorMatcherProperties::setCrossMatching(bool crossMatching)
//{
//  mCrossMatching = crossMatching;
//}

//void DescriptorMatcherProperties::reset()
//{
//  mMatchingMethod = "Brute-Force";
//  mNorm = "NORM_L2";
//  mRatio = 0.8;
//  mDistance = 0.7;
//  mConfidence = 0.999;
//  mCrossMatching = true;
//}



} // namespace fme








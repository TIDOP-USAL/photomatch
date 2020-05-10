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


#include "HomographyViewerModel.h"

#include "photomatch/core/utils.h"
#include "photomatch/core/features/featio.h"
#include "photomatch/core/features/matchio.h"
#include "photomatch/ui/ProjectModel.h"

#include <tidop/core/messages.h>

#include <opencv2/calib3d.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/imgcodecs.hpp>
#ifdef HAVE_CUDA
#include <opencv2/cudawarping.hpp>
#include <opencv2/cudaarithm.hpp>
#endif

#include <QFileInfo>

namespace photomatch
{

HomographyViewerModelImp::HomographyViewerModelImp(ProjectModel *mProjectModel)
  : HomographyViewerModel(),
    mProjectModel(mProjectModel),
    bUseCuda(false)
{
  init();
}

HomographyViewerModelImp::~HomographyViewerModelImp()
{

}

QString HomographyViewerModelImp::currentSession() const
{
  if (mProjectModel->currentSession())
    return mProjectModel->currentSession()->name();
  else
    return QString();
}

std::vector<QString> HomographyViewerModelImp::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> HomographyViewerModelImp::imagePairs(const QString &imageName) const
{
  std::vector<QString> pairs;
  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
    std::vector<std::pair<QString, QString>> matches = session->matches(imageName);
    if (!matches.empty()){
      for (auto &m : matches){
        QString name = m.first;
        for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
          if ((*it)->name().compare(name) == 0){
            pairs.push_back((*it)->path());
            break;
          }
        }
      }
    }
  }

  return pairs;
}

QImage HomographyViewerModelImp::homography(const QString &imgName1,
                                            const QString &imgName2) const
{
  QImage image;
  QString imgPath1 = mProjectModel->findImageByName(imgName1)->path();
  QString imgPath2 = mProjectModel->findImageByName(imgName2)->path();

  if (QFileInfo(imgPath1).exists() == false || QFileInfo(imgPath2).exists() == false)
    return image;

  if (std::shared_ptr<Session> session = mProjectModel->currentSession()){
    std::vector<std::pair<QString, QString>> matches = session->matches(imgName1);

    if (!matches.empty()){
      for (auto &m : matches){
        if (m.first.compare(imgName2) == 0){

          std::unique_ptr<MatchesReader> matchesReader = MatchesReaderFactory::createReader(m.second);
          matchesReader->read();
          std::vector<cv::DMatch> match = matchesReader->goodMatches();
          matchesReader.reset();

          std::unique_ptr<FeaturesReader> featuresRead = FeaturesReaderFactory::createReader(session->features(imgName1));
          featuresRead->read();
          std::vector<cv::KeyPoint> keyPoints1 = featuresRead->keyPoints();
          featuresRead = FeaturesReaderFactory::createReader(session->features(imgName2));
          featuresRead->read();
          std::vector<cv::KeyPoint> keyPoints2 = featuresRead->keyPoints();

          /// Un tanto artificioso.... Revisar
          QString nameMatchesFile = QFileInfo(m.second).baseName();
          int idx = nameMatchesFile.indexOf(imgName1);
          std::vector<cv::Point2f> pts_query;
          std::vector<cv::Point2f> pts_train;

          for (size_t i = 0; i < match.size(); i++){
            size_t query_id = (idx == 0) ? static_cast<size_t>(match[i].queryIdx) : static_cast<size_t>(match[i].trainIdx);
            size_t train_id = (idx == 0) ? static_cast<size_t>(match[i].trainIdx) : static_cast<size_t>(match[i].queryIdx);
            pts_query.push_back(keyPoints1[query_id].pt);
            pts_train.push_back(keyPoints2[train_id].pt);
          }

          cv::Mat H = cv::findHomography(pts_query, pts_train);

          QByteArray ba = imgPath1.toLocal8Bit();
          const char *img_left = ba.data();
          cv::Mat imgLeft = cv::imread(img_left, cv::IMREAD_IGNORE_ORIENTATION | cv::IMREAD_COLOR);
          ba = imgPath2.toLocal8Bit();
          const char *img_right = ba.data();
          cv::Mat imgRight = cv::imread(img_right, cv::IMREAD_IGNORE_ORIENTATION | cv::IMREAD_COLOR);

          cv::Mat merged;
//#ifdef HAVE_CUDA
//          if (bUseCuda){
//            cv::cuda::GpuMat gpuImgLeft;
//            gpuImgLeft.upload(imgLeft);
//            cv::cuda::GpuMat gpuOut;
//            cv::cuda::GpuMat gpuH;
//            gpuImgLeft.upload(H);
//            cv::cuda::warpPerspective(gpuImgLeft, gpuOut, gpuH, gpuImgLeft.size(), cv::INTER_LINEAR);
//            imgLeft.release();
//            cv::cuda::GpuMat gpuImgRight(imgRight);
//            cv::cuda::GpuMat gpuMerged;
//            cv::cuda::addWeighted(imgRight, 0.5, gpuOut, 0.3, 0.0, gpuMerged);
//            gpuMerged.download(merged);
//          } else {
//#endif
            cv::Mat out;
            cv::warpPerspective(imgLeft, out, H, imgRight.size(), cv::INTER_LINEAR);
            imgLeft.release();
            cv::addWeighted(imgRight, 0.5, out, 0.3, 0.0, merged);
//#ifdef HAVE_CUDA
//          }
//#endif
          ///cv::cuda::warpPerspective


          imgRight.release();
          ///cv::cuda::addWeighted

          image = cvMatToQImage(merged);
          break;
        }
      }
    }
  }

  return image;
}

void HomographyViewerModelImp::setUseCuda(bool active)
{
  bUseCuda = active;
}

void HomographyViewerModelImp::init()
{
}

} // namespace photomatch



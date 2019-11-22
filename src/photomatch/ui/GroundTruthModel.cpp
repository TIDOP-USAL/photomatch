#include "GroundTruthModel.h"

#include "photomatch/ui/ProjectModel.h"
#include "photomatch/core/features/groundtruth.h"
#include "photomatch/core/utils.h"

#include <QImageReader>

namespace photomatch
{

GroundTruthModel::GroundTruthModel(IProjectModel *mProjectModel)
  : IGroundTruthModel(),
    mProjectModel(mProjectModel),
    mGroundTruth(nullptr)
{

}

GroundTruthModel::~GroundTruthModel()
{
  if (mGroundTruth) {
    delete mGroundTruth;
    mGroundTruth = nullptr;
  }
}

QPointF GroundTruthModel::findPoint(const QString &image1, const QString &image2, const QPointF &ptImage1)
{
  QTransform trf = this->transform(image1, image2);
  if (trf.isIdentity() == false){
    QPointF trf_point = trf.map(ptImage1);

    /// Matriz de transformación en OpenCV
    cv::Mat h(3,3, CV_64FC1);
    h.at<double>(0, 0) = trf.m11();
    h.at<double>(1, 0) = trf.m12();
    h.at<double>(2, 0) = trf.m13();
    h.at<double>(0, 1) = trf.m21();
    h.at<double>(1, 1) = trf.m22();
    h.at<double>(2, 1) = trf.m23();
    h.at<double>(0, 2) = 0; // trf.m31();
    h.at<double>(1, 2) = 0; // trf.m32();
    h.at<double>(2, 2) = trf.m33();

    /// - se calcula una ventana a partir de pt
    /// - se lee el trozo de imagen correspondiente a la ventana
    QImageReader reader1(mProjectModel->findImageByName(image1)->path());
    double offset_x = ptImage1.x() - round(ptImage1.x());
    double offset_y = ptImage1.y() - round(ptImage1.y());
    QRect rect1(static_cast<int>(ptImage1.x()) - 10, static_cast<int>(ptImage1.y()) - 10, 20, 20);

    reader1.setClipRect(rect1);
    QImage qImage1 = reader1.read();
    
    //cv::Rect2f rect;
    //QPointF trf_pt_tl = trf_inv.map(rectRight.topLeft());
    //QPointF trf_pt_tr = trf_inv.map(rectRight.topRight());
    //QPointF trf_pt_br = trf_inv.map(rectRight.bottomRight());
    //QPointF trf_pt_bl = trf_inv.map(rectRight.bottomLeft());
    //rect.x = trf_pt_tl.x() < trf_pt_bl.x() ? trf_pt_tl.x() : trf_pt_bl.x();
    //rect.y = trf_pt_tl.y() < trf_pt_tr.y() ? trf_pt_tl.y() : trf_pt_tr.y();
    //rect.width = trf_pt_tr.x() > trf_pt_br.x() ? trf_pt_tr.x() - rect.x : trf_pt_br.x() - rect.x;
    //rect.height = trf_pt_br.y() > trf_pt_bl.y() ? trf_pt_br.y() - rect.y : trf_pt_bl.y() - rect.y;
    //cv::Size size = rect.size();

    /// - se aplica la transformación proyectiva a la imagen y se utiliza como template
    cv::Mat templ1 = qImageToCvMat(qImage1);
    //cv::cvtColor(templ1, templ1, cv::COLOR_BGR2GRAY);
    //cv::Mat warp_templ1;
    //cv::Size size(trf_pt_br.x() - trf_pt_tl.x(), trf_pt_br.y() - trf_pt_tl.y());
    //cv::warpPerspective(templ1, warp_templ1, h, templ1.size());


    QImageReader reader2(mProjectModel->findImageByName(image2)->path());
    QRect rect2(static_cast<int>(trf_point.x()) - 150, static_cast<int>(trf_point.y()) - 150, 300, 300);
    reader2.setClipRect(rect2);
    QImage qImage2 = reader2.read();
    cv::Mat search_mat = qImageToCvMat(qImage2);
    //cv::cvtColor(search_mat, search_mat, cv::COLOR_BGR2GRAY);

    cv::Mat result(search_mat.rows - templ1.rows + 1, search_mat.cols - templ1.cols + 1, CV_32FC1);

    int mMatchMmethod = cv::TM_CCORR_NORMED;
    cv::matchTemplate(search_mat, templ1, result, mMatchMmethod);
    double minVal; double maxVal;
    cv::Point minLoc;
    cv::Point maxLoc;

    cv::Point matchLoc;
    minMaxLoc(result, &minVal, &maxVal, &minLoc, &maxLoc, cv::Mat());
    if (mMatchMmethod == cv::TM_SQDIFF || mMatchMmethod == cv::TM_SQDIFF_NORMED) {
      matchLoc = minLoc;
    } else {
      matchLoc = maxLoc;
    }

    if (maxVal > 0.99) {
      return QPointF(matchLoc.x + 10 + rect2.x() + offset_x, matchLoc.y + 10 + rect2.y() + offset_y);
    }

  }

  return QPointF();
}

QPointF GroundTruthModel::findProjectedPoint(const QString & image1, const QString & image2, const QPointF & ptImage1)
{
  QTransform trf = this->transform(image1, image2);
  if (trf.isIdentity() == false)
    return trf.map(ptImage1);
  else 
    return QPointF();
}

void GroundTruthModel::init()
{

}

void GroundTruthModel::loadGroundTruth()
{
  if (mGroundTruth == nullptr){
    mGroundTruth = new GroundTruth;
  } else {
    mGroundTruth->clear();
  }

  if (mProjectModel->groundTruth().isEmpty() == false)
    mGroundTruth->read(mProjectModel->groundTruth());
}

std::vector<QString> GroundTruthModel::images() const
{
  std::vector<QString> images;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    images.push_back((*it)->path());
  }
  return images;
}

std::vector<QString> GroundTruthModel::imagePairs(const QString &imageName) const
{
  std::vector<QString> pairs;
  for (auto it = mProjectModel->imageBegin(); it != mProjectModel->imageEnd(); it++){
    if (imageName.compare((*it)->name()) != 0){
      pairs.push_back((*it)->path());
    }
  }
  return pairs;
}

std::vector<std::pair<QPointF, QPointF> > GroundTruthModel::groundTruth(const QString &imgName1, const QString &imgName2) const
{
  std::vector<std::pair<QPointF,QPointF>> r_ground_truth;

  std::shared_ptr<HomologusPoints> ground_truth = mGroundTruth->findPair(imgName1, imgName2);
  if (ground_truth){
    r_ground_truth = ground_truth->homologusPoints();
  }

  std::shared_ptr<HomologusPoints> ground_truth_inv = mGroundTruth->findPair(imgName2, imgName1);
  if (ground_truth_inv){
    for (auto &homologusPoint : ground_truth_inv->homologusPoints()){
      r_ground_truth.push_back(std::make_pair(homologusPoint.second, homologusPoint.first)); /// .....
    }
  }

  return r_ground_truth;
}

std::pair<QPointF, QPointF> GroundTruthModel::homologus(const QString &imgName1, const QString &imgName2, int pointId) const
{
  std::pair<QPointF, QPointF> homologus;
  if (std::shared_ptr<HomologusPoints> homologus = mGroundTruth->pair(imgName1, imgName2)){
    QPointF ptLeft = homologus->at(static_cast<size_t>(pointId-1)).first;
    QPointF ptRight = homologus->at(static_cast<size_t>(pointId-1)).second;
    return std::make_pair(ptLeft,ptRight);
  }
  return homologus;
}

QTransform GroundTruthModel::transform(const QString &imgName1, const QString &imgName2,
                                       std::vector<double> *distances, double *rootMeanSquareError) const
{
  QTransform trf;
  HomologusPoints homologusPoints(imgName1, imgName2);
  if (std::shared_ptr<HomologusPoints> ground_truth_direct = mGroundTruth->findPair(imgName1, imgName2)){
    for (auto &homolPoint : ground_truth_direct->homologusPoints()){
      homologusPoints.push_back(homolPoint);
    }
  }

  if (std::shared_ptr<HomologusPoints> ground_truth_inverse = mGroundTruth->findPair(imgName2, imgName1)){
    for (auto &homolPoint : ground_truth_inverse->homologusPoints()){
      homologusPoints.addPoints(homolPoint.second, homolPoint.first);
    }
  }

  if (homologusPoints.empty() == false && homologusPoints.size() >= 4) {
    cv::Mat h = homologusPoints.homography();
    if (h.empty() == false){
      trf.setMatrix(h.at<double>(0, 0), h.at<double>(1, 0), h.at<double>(2, 0),
                    h.at<double>(0, 1), h.at<double>(1, 1), h.at<double>(2, 1),
                    h.at<double>(0, 2), h.at<double>(1, 2), h.at<double>(2, 2));

      std::vector<double> dist(homologusPoints.size(), -1.);
      double sum_error = 0.;
      int n = 0;
      for (size_t i = 0; i < homologusPoints.size(); i++){
        QPointF pt1 = homologusPoints[i].first;
        QPointF pt2 = homologusPoints[i].second;
        if (!pt1.isNull() && !pt2.isNull()){
          QPointF pt1_trf = trf.map(pt1);
          QPointF v = pt1_trf - pt2;
          double aux = QPointF::dotProduct(v, v);
          dist[i] = sqrt(aux);
          sum_error += aux;
          n++;
        }
      }

      if (distances != nullptr){
        *distances = dist;
      }
      if (rootMeanSquareError != nullptr){
        *rootMeanSquareError = sqrt(sum_error/(2*(n - 4)));
      }
    }
  }

  return trf;
}

void GroundTruthModel::saveGroundTruth()
{
  if (mProjectModel->groundTruth().isEmpty()){
    QString gt = mProjectModel->projectFolder();
    gt.append("/GroundTruth.txt");
    mProjectModel->setGroundTruth(gt);
  }
  mGroundTruth->write(mProjectModel->groundTruth());
}

void GroundTruthModel::setGroundTruth(const QString &file)
{
  mProjectModel->setGroundTruth(file);
  this->loadGroundTruth();
}

bool GroundTruthModel::existGroundTruth() const
{
  return !mProjectModel->groundTruth().isEmpty();
}

QString GroundTruthModel::projectPath() const
{
  return mProjectModel->projectFolder();
}

QPointF GroundTruthModel::findLeftPoint(const QString &image1,
                                        const QString &image2,
                                        const QPointF &pt)
{
  return findPoint(image2, image1, pt);
}

QPointF GroundTruthModel::findRightPoint(const QString &image1,
                                         const QString &image2,
                                         const QPointF &pt)
{
  return findPoint(image1, image2, pt);
}

QPointF GroundTruthModel::findProjectedLeftPoint(const QString &image1, const QString &image2, const QPointF &pt)
{
  return findProjectedPoint(image2, image1, pt);
}

QPointF GroundTruthModel::findProjectedRightPoint(const QString &image1, const QString &image2, const QPointF &pt)
{
  return findProjectedPoint(image1, image2, pt);
}

void GroundTruthModel::addHomologus(const QString &image1, const QPointF &pt1,
                                          const QString &image2, const QPointF &pt2)
{
  if (std::shared_ptr<HomologusPoints> homologus = mGroundTruth->pair(image1, image2)){
    homologus->addPoints(pt1, pt2);
  }
}

void GroundTruthModel::deleteHomologus(const QString &image1, const QString &image2, int pointId)
{
  if (std::shared_ptr<HomologusPoints> homologus = mGroundTruth->pair(image1, image2)){
    /// Se marca como nulo
    homologus->at(static_cast<size_t>(pointId-1)).first = QPoint();
    homologus->at(static_cast<size_t>(pointId-1)).second = QPoint();
  }
}




} // namespace photomatch

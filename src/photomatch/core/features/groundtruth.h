#ifndef PHOTOMATCH_GROUND_TRUTH_H
#define PHOTOMATCH_GROUND_TRUTH_H

#include "photomatch/photomatch_global.h"

#include <vector>
#include <memory>

#include <QPointF>
#include <QString>

#include <opencv2/calib3d.hpp>

namespace photomatch
{

class HomologusPoints
{
public:

  typedef typename std::vector<std::pair<QPointF, QPointF>>::allocator_type allocator_type;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::value_type value_type;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::size_type size_type;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::difference_type difference_type;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::pointer pointer;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::const_pointer const_pointer;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::reference reference;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::const_reference const_reference;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::iterator iterator;
  typedef typename std::vector<std::pair<QPointF, QPointF>>::const_iterator const_iterator;

public:

  HomologusPoints(const QString &idImg1, const QString &idImg2);

  void addPoints(const QPointF &pt1, const QPointF &pt2);

  iterator begin();
  const_iterator begin() const;
  iterator end();
  const_iterator end() const;
  void push_back(const std::pair<QPointF, QPointF> &points);
  const_reference at(size_type position) const;
  reference at(size_type position);
  void clear();
  bool empty() const;
  void reserve(size_type size);
  void resize(size_type count);
  void resize(size_type count, const std::pair<QPointF, QPointF> &points);
  size_type size() const;
  const_reference operator[](size_type position) const;
  reference operator[](size_type position);
  iterator erase(const_iterator first, const_iterator last);

  QString idImg1() const;
  QString idImg2() const;

  std::vector<std::pair<QPointF, QPointF>> homologusPoints() const;
  cv::Mat homography() const;

private:

  QString mIdImg1;
  QString mIdImg2;
  std::vector<std::pair<QPointF, QPointF>> mHomologusPoints;

};


class GroundTruth
{

public:

  GroundTruth();
  GroundTruth(const QString &gtFile);

  void read(const QString &gtFile);
  void write(const QString &gtFile);

  std::shared_ptr<HomologusPoints> findPair(const QString &idImg1, const QString &idImg2);
  std::shared_ptr<HomologusPoints> pair(const QString &idImg1, const QString &idImg2);

  void clear();

private:

  QString mGroundTruthFile;
  std::vector<std::shared_ptr<HomologusPoints>> mHomologusPoints;

};

} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_H

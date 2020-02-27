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

  /*!
   * \brief Id image 1 (base name of image file)
   * \return Id
   */
  QString idImg1() const;

  /*!
   * \brief Id image 2 (base name of image file)
   * \return Id
   */
  QString idImg2() const;

  /*!
   * \brief List of homologus points
   * \return
   */
  std::vector<std::pair<QPointF, QPointF>> homologusPoints() const;

  /*!
   * \brief homography
   * \return
   */
  cv::Mat homography() const;

  //std::vector<std::pair<QPointF, QPointF>> invert() const;

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
  virtual ~GroundTruth(){}

  /*!
   * \brief Read ground truth file
   * \param[in] gtFile ground truth file
   */
  virtual void read(const QString &gtFile);

  /*!
   * \brief Write ground truth file
   * \param[in] gtFile ground truth file
   */
  virtual void write(const QString &gtFile);

  /*!
   * \brief findPair
   * \param[in] idImg1 Id image 1 (base name of image file)
   * \param[in] idImg2 Id image 2 (base name of image file)
   * \return
   */
  std::shared_ptr<HomologusPoints> findPair(const QString &idImg1, const QString &idImg2);

  /*!
   * \brief pair
   * \param[in] idImg1 Id image 1 (base name of image file)
   * \param[in] idImg2 Id image 2 (base name of image file)
   * \return
   */
  std::shared_ptr<HomologusPoints> pair(const QString &idImg1, const QString &idImg2);

  void clear();

protected:

  QString mGroundTruthFile;
  std::vector<std::shared_ptr<HomologusPoints>> mHomologusPoints;

};

} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_H

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


#ifndef PHOTOMATCH_MSD_DETECTOR_H
#define PHOTOMATCH_MSD_DETECTOR_H

#include "photomatch/photomatch_global.h"

#include "photomatch/core/features/features.h"

#include <memory>

#include <QString>

#include "msd/MSD.h"

namespace photomatch
{


class PHOTOMATCH_EXPORT MsdProperties
  : public Msd
{
public:

  MsdProperties();
  MsdProperties(const MsdProperties &msdProperties);
  ~MsdProperties() override;

// IMsd interface
public:

  virtual double thresholdSaliency() const override;
  virtual int patchRadius() const override;
  virtual int knn() const override;
  virtual int searchAreaRadius() const override;
  virtual double scaleFactor() const override;
  virtual int NMSRadius() const override;
  virtual int nScales() const override;
  virtual int NMSScaleRadius() const override;
  virtual bool computeOrientation() const override;
  virtual bool affineMSD() const override;
  virtual int affineTilts() const override;
  //virtual int tilts() const override;
  virtual void setThresholdSaliency(double thresholdSaliency) override;
  virtual void setPatchRadius(int patchRadius) override;
  virtual void setKNN(int knn) override;
  virtual void setSearchAreaRadius(int searchAreaRadius) override;
  virtual void setScaleFactor(double scaleFactor) override;
  virtual void setNMSRadius(int NMSRadius) override;
  virtual void setNScales(int nScales) override;
  virtual void setNMSScaleRadius(int NMSScaleR) override;
  virtual void setComputeOrientation(bool computeOrientation) override;
  virtual void setAffineMSD(bool affineMSD) override;
  //virtual void setTilts(int tilts) override;
  virtual void setAffineTilts(int affineTilts) override;

// Feature interface

public:

  virtual void reset() override;
  QString name() const final;

private:

  double mThresholdSaliency;
  int mPatchRadius;
  int mKNN;
  int mAreaRadius;
  double mScaleFactor;
  int mNMSRadius;
  int mNScales;
  int mNMSScaleR;
  bool mComputeOrientations;
  bool mAffineMSD;
  //int mTilts;
  int mAffineTilts;
};


/*----------------------------------------------------------------*/


class MsdDetector
  : public MsdProperties,
    public KeypointDetector
{

public:

  MsdDetector();
  MsdDetector(const MsdDetector &msdDetector);
  MsdDetector(double thresholdSaliency,
              int patchRadius,
              int knn,
              int searchAreaRadius,
              double scaleFactor,
              int NMSRadius,
              int nScales,
              int NMSScaleR,
              bool computeOrientation,
              bool affineMSD,
              int affineTilts);
  ~MsdDetector() override;

private:

  bool pointIsAcceptable(const cv::KeyPoint &vl_keypoint, int width, int height);
  void compensateAffineCoor1(float *x0, float *y0, int w1, int h1, float t1, float t2, float Rtheta);
  void affineSkew(double tilt, double phi, cv::Mat &img, cv::Mat &mask, cv::Mat &Ai);
  void updateMSD();

// KeypointDetector interface

public:

  bool detect(const cv::Mat &img,
              std::vector<cv::KeyPoint> &keyPoints,
              cv::InputArray &mask = cv::noArray()) override;

// IMsd interface

public:

  void setThresholdSaliency(double thresholdSaliency) override;
  void setPatchRadius(int patchRadius) override;
  void setKNN(int knn) override;
  void setSearchAreaRadius(int searchAreaRadius) override;
  void setScaleFactor(double scaleFactor) override;
  void setNMSRadius(int NMSRadius) override;
  void setNScales(int nScales) override;
  void setNMSScaleRadius(int NMSScaleR) override;
  void setComputeOrientation(bool computeOrientation) override;
  void setAffineMSD(bool affineMSD) override;
  void setAffineTilts(int affineTilts) override;

// Feature interface

public:

  void reset() override;

protected:

  std::shared_ptr<::MsdDetector> mMSD;

};


} // namespace photomatch

#endif // PHOTOMATCH_MSD_DETECTOR_H

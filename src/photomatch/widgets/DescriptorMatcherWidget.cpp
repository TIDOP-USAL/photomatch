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


#include "DescriptorMatcherWidget.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QStandardItemModel>

namespace photomatch
{

DescriptorMatcherWidgetImp::DescriptorMatcherWidgetImp(QWidget *parent)
  : DescriptorMatcherWidget(parent),
    mMatchingMethod(new QComboBox(this)),
    mMatchingStrategy(new QComboBox(this)),
    mNormType(new QComboBox(this)),
    mRatio(new QDoubleSpinBox(this)),
    mGeometricTest(new QComboBox(this)),
    mDistance(new QDoubleSpinBox(this)),
    mConfidence(new QDoubleSpinBox(this)),
    mMaxIters(new QSpinBox(this)),
    mCrossMatching(new QCheckBox(this)),
    mHComputeMethod(new QComboBox(this)),
    mFComputeMethod(new QComboBox(this)),
    mEComputeMethod(new QComboBox(this)),
    mRotationGMS(new QCheckBox(this)),
    mScaleGMS(new QCheckBox(this)),
    mThresholdGMS(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

DescriptorMatcherWidgetImp::~DescriptorMatcherWidgetImp()
{

}

QString DescriptorMatcherWidgetImp::matchingMethod() const
{
  return mMatchingMethod->currentText();
}

QString DescriptorMatcherWidgetImp::matchingStrategy() const
{
  return mMatchingStrategy->currentText();
}

QString DescriptorMatcherWidgetImp::normType() const
{
  return mNormType->currentText();
}

double DescriptorMatcherWidgetImp::ratio() const
{
  return mRatio->value();
}

QString DescriptorMatcherWidgetImp::geometricTest() const
{
  return mGeometricTest->currentText();
}

QString DescriptorMatcherWidgetImp::homographyComputeMethod() const
{
  return mHComputeMethod->currentText();
}

QString DescriptorMatcherWidgetImp::fundamentalComputeMethod() const
{
  return mFComputeMethod->currentText();
}

QString DescriptorMatcherWidgetImp::essentialComputeMethod() const
{
  return mEComputeMethod->currentText();
}

double DescriptorMatcherWidgetImp::distance() const
{
  return mDistance->value();
}

double DescriptorMatcherWidgetImp::confidence() const
{
  return mConfidence->value();
}

int DescriptorMatcherWidgetImp::maxIters() const
{
  return mMaxIters->value();
}

bool DescriptorMatcherWidgetImp::crossMatching() const
{
  return mCrossMatching->isChecked();
}

bool DescriptorMatcherWidgetImp::gmsRotation() const
{
  return mRotationGMS->isChecked();
}

bool DescriptorMatcherWidgetImp::gmsScale() const
{
  return mScaleGMS->isChecked();
}

double DescriptorMatcherWidgetImp::gmsThreshold() const
{
  return mThresholdGMS->value();
}

void DescriptorMatcherWidgetImp::setMatchingMethod(const QString &matchingMethod)
{
  const QSignalBlocker blockerMatchingMethod(mMatchingMethod);
  mMatchingMethod->setCurrentText(matchingMethod);
  update();
}

void DescriptorMatcherWidgetImp::setMatchingStrategy(const QString &matchingStrategy)
{
  const QSignalBlocker blockerMatchingMethod(mMatchingStrategy);
  mMatchingStrategy->setCurrentText(matchingStrategy);
  update();
}

void DescriptorMatcherWidgetImp::setNormType(const QString &normType)
{
  const QSignalBlocker blockerNormType(mNormType);
  mNormType->setCurrentText(normType);
}

void DescriptorMatcherWidgetImp::setRatio(double ratio)
{
  const QSignalBlocker blockerRatio(mRatio);
  mRatio->setValue(ratio);
}

void DescriptorMatcherWidgetImp::setGeometricTest(const QString &geometricTest)
{
  const QSignalBlocker blockerGeometricTest(mGeometricTest);
  mGeometricTest->setCurrentText(geometricTest);
  update();
}

void DescriptorMatcherWidgetImp::setHomographyComputeMethod(const QString &computeMethod)
{
  const QSignalBlocker blockerHomographyComputeMethod(mHComputeMethod);
  mHComputeMethod->setCurrentText(computeMethod);
  update();
}

void DescriptorMatcherWidgetImp::setFundamentalComputeMethod(const QString &computeMethod)
{
  const QSignalBlocker blockerFundamentalComputeMethod(mFComputeMethod);
  mFComputeMethod->setCurrentText(computeMethod);
  update();
}

void DescriptorMatcherWidgetImp::setEssentialComputeMethod(const QString &computeMethod)
{
  const QSignalBlocker blockerEssentialComputeMethod(mEComputeMethod);
  mEComputeMethod->setCurrentText(computeMethod);
  update();
}

void DescriptorMatcherWidgetImp::setDistance(double distance)
{
  const QSignalBlocker blockerDistance(mDistance);
  mDistance->setValue(distance);
}

void DescriptorMatcherWidgetImp::setConfidence(double confidence)
{
  const QSignalBlocker blockerConfidence(mConfidence);
  mConfidence->setValue(confidence);
}

void DescriptorMatcherWidgetImp::setMaxIters(int maxIter)
{
  const QSignalBlocker blockerMaxIters(mMaxIters);
  mMaxIters->setValue(maxIter);
}

void DescriptorMatcherWidgetImp::setCrossMatching(bool crossMatching)
{
  mCrossMatching->setChecked(crossMatching);
}

void DescriptorMatcherWidgetImp::disableBruteForceNorm(const QString &norm)
{
  QStandardItemModel *model = qobject_cast<QStandardItemModel *>(mNormType->model());
  if (model != nullptr) {
    QList<QStandardItem *> items = model->findItems(norm);
    for (auto &item : items){
      item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
  }
}

void DescriptorMatcherWidgetImp::enableBruteForceNorm(const QString &norm)
{
  QStandardItemModel *model = qobject_cast<QStandardItemModel *>(mNormType->model());
  if (model != nullptr) {
    QList<QStandardItem *> items = model->findItems(norm);
    for (auto &item : items){
      item->setFlags(item->flags() | Qt::ItemIsEnabled);
    }
  }
}

void DescriptorMatcherWidgetImp::setGmsRotation(bool active)
{
  mRotationGMS->setChecked(active);
}

void DescriptorMatcherWidgetImp::setGmsScale(bool active)
{
  mScaleGMS->setChecked(active);
}

void DescriptorMatcherWidgetImp::setGmsThreshold(double threshold)
{
  const QSignalBlocker blocker(mThresholdGMS);
  mThresholdGMS->setValue(threshold);
}

void DescriptorMatcherWidgetImp::update()
{
  if (mMatchingMethod->currentText().compare("FLANN") == 0){
    mGroupBoxBFParameters->hide();
  } else {
    mGroupBoxBFParameters->show();
  }

  if (mMatchingStrategy->currentText().compare("GMS") == 0){
    mGroupBoxFilteringTest->hide();
    mGroupBoxGMS->show();
  } else {
    mGroupBoxFilteringTest->show();
    mGroupBoxGMS->hide();
  }

  QString geomTest = mGeometricTest->currentText();
  if (geomTest.compare("Homography Matrix") == 0){
    mHComputeMethod->show();
    mHComputeMethodLabel->show();
    mFComputeMethod->hide();
    mFComputeMethodLabel->hide();
    mEComputeMethod->hide();
    mEComputeMethodLabel->hide();
    QString computeMethod = mHComputeMethod->currentText();
    mConfidence->show();
    mConfidenceLabel->show();
    if (computeMethod.compare("All Points") == 0){
      mDistance->hide();
      mDistanceLabel->hide();
      mMaxIters->hide();
      mMaxItersLabel->hide();
    } else if (computeMethod.compare("RANSAC") == 0){
      mDistance->show();
      mDistanceLabel->show();
      mMaxIters->show();
      mMaxItersLabel->show();
    } else if (computeMethod.compare("LMedS") == 0){
      mDistance->hide();
      mDistanceLabel->hide();
      mMaxIters->hide();
      mMaxItersLabel->hide();
    } else if (computeMethod.compare("RHO") == 0){
      mDistance->show();
      mDistanceLabel->show();
      mMaxIters->hide();
      mMaxItersLabel->hide();
    }
  } else if (geomTest.compare("Fundamental Matrix") == 0){
    mHComputeMethod->hide();
    mHComputeMethodLabel->hide();
    mFComputeMethod->show();
    mFComputeMethodLabel->show();
    mEComputeMethod->hide();
    mEComputeMethodLabel->hide();
    QString computeMethod = mFComputeMethod->currentText();
    mMaxIters->hide();
    mMaxItersLabel->hide();
    if (computeMethod.compare("7-point algorithm") == 0){
      mDistance->hide();
      mDistanceLabel->hide();
      mConfidence->hide();
      mConfidenceLabel->hide();
    } else if (computeMethod.compare("8-point algorithm") == 0){
      mDistance->hide();
      mDistanceLabel->hide();
      mConfidence->hide();
      mConfidenceLabel->hide();
    } else if (computeMethod.compare("RANSAC") == 0){
      mDistance->show();
      mDistanceLabel->show();
      mConfidence->show();
      mConfidenceLabel->show();
    } else if (computeMethod.compare("LMedS") == 0){
      mDistance->hide();
      mDistanceLabel->hide();
      mConfidence->show();
      mConfidenceLabel->show();
    }
  } else if (geomTest.compare("Essential Matrix") == 0) {
    mHComputeMethod->hide();
    mHComputeMethodLabel->hide();
    mFComputeMethod->hide();
    mFComputeMethodLabel->hide();
    mEComputeMethod->show();
    mEComputeMethodLabel->show();
    mConfidence->show();
    mConfidenceLabel->show();
    mMaxIters->hide();
    mMaxItersLabel->hide();
    QString computeMethod = mEComputeMethod->currentText();
    if (computeMethod.compare("RANSAC") == 0){
      mDistance->show();
      mDistanceLabel->show();
    } else if (computeMethod.compare("LMedS") == 0){
      mDistance->hide();
      mDistanceLabel->hide();
    }
  }
}

void DescriptorMatcherWidgetImp::retranslate()
{

}

void DescriptorMatcherWidgetImp::reset()
{
  const QSignalBlocker blockerMatchingMethod(mMatchingMethod);
  const QSignalBlocker blockerMatchingStrategy(mMatchingStrategy);
  const QSignalBlocker blockerNormType(mNormType);
  const QSignalBlocker blockerRatio(mRatio);
  const QSignalBlocker blockerGeometricTest(mGeometricTest);
  const QSignalBlocker blockerHomographyComputeMethod(mHComputeMethod);
  const QSignalBlocker blockerFundamentalComputeMethod(mFComputeMethod);
  const QSignalBlocker blockerEssentialComputeMethod(mEComputeMethod);
  const QSignalBlocker blockerDistance(mDistance);
  const QSignalBlocker blockerConfidence(mConfidence);
  const QSignalBlocker blockerMaxIters(mMaxIters);
  const QSignalBlocker blockerThresholdGMS(mThresholdGMS);

  mMatchingMethod->setCurrentText("Brute-Force");
  mNormType->setCurrentText("NORM_L1");
  mGroupBoxBFParameters->show();
  mMatchingStrategy->setCurrentText("Robust Matching");
  mGroupBoxFilteringTest->show();
  mGroupBoxGMS->hide();
  mRatio->setValue(0.8);
  mGeometricTest->setCurrentText("Fundamental Matrix");
  mHComputeMethod->setCurrentText("RANSAC");
  mFComputeMethod->setCurrentText("RANSAC");
  mEComputeMethod->setCurrentText("RANSAC");
  mDistance->setValue(0.7);
  mConfidence->setValue(0.999);
  mMaxIters->setValue(2000);
  mCrossMatching->setChecked(true);
  mRotationGMS->setChecked(false);
  mScaleGMS->setChecked(false);
  mThresholdGMS->setValue(6.0);

  update();
}

void DescriptorMatcherWidgetImp::initUI()
{
  this->setWindowTitle("Descriptor Matcher");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(new QLabel(tr("Matching Method:")), 0, 0);
  mMatchingMethod->addItem("Brute-Force");
  mMatchingMethod->addItem("FLANN");
  layout->addWidget(mMatchingMethod, 0, 1);

  layout->addWidget(new QLabel(tr("Matching Strategy:")), 1, 0);
  mMatchingStrategy->addItem("Robust Matching");
  mMatchingStrategy->addItem("GMS");
  layout->addWidget(mMatchingStrategy, 1, 1);

  mGroupBoxBFParameters = new QGroupBox(tr("Brute Force Parameters"), this);
  layout->addWidget(mGroupBoxBFParameters, 2, 0, 1, 2);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBoxBFParameters->setLayout(propertiesLayout);

  mNormTypeLabel = new QLabel(tr("Norm Type:"), this);
  propertiesLayout->addWidget(mNormTypeLabel, 0, 0);
  mNormType->addItem("NORM_L1");
  mNormType->addItem("NORM_L2");
  mNormType->addItem("NORM_HAMMING");
  mNormType->addItem("NORM_HAMMING2");
  propertiesLayout->addWidget(mNormType, 0, 1);

  /// Robust Matching

  mGroupBoxFilteringTest = new QGroupBox(tr("Filtering Test"), this);
  layout->addWidget(mGroupBoxFilteringTest, 3, 0, 1, 2);

  QGridLayout *filteringTestLayout = new QGridLayout();
  mGroupBoxFilteringTest->setLayout(filteringTestLayout);

  filteringTestLayout->addWidget(new QLabel(tr("Ratio:")), 0, 0);
  mRatio->setDecimals(3);
  mRatio->setRange(0.001, 100.);
  mRatio->setSingleStep(0.1);
  filteringTestLayout->addWidget(mRatio, 0, 1);

  mCrossMatching->setText(tr("Cross Matching"));
  filteringTestLayout->addWidget(mCrossMatching, 1, 0);

  filteringTestLayout->addWidget(new QLabel(tr("Geometric Test:")), 2, 0);
  mGeometricTest->addItem("Homography Matrix");
  mGeometricTest->addItem("Fundamental Matrix");
  //mGeometricTest->addItem("Essential Matrix");  /// Desactivada matriz esencial porque se necesitaria calibración de la cámara y no es el objetivo de la herramienta
  filteringTestLayout->addWidget(mGeometricTest, 2, 1);

  mHComputeMethodLabel = new QLabel(tr("Compute method:"));
  filteringTestLayout->addWidget(mHComputeMethodLabel, 3, 0);
  mHComputeMethod->addItem("All Points");
  mHComputeMethod->addItem("RANSAC");
  mHComputeMethod->addItem("LMedS");
  mHComputeMethod->addItem("RHO");
  filteringTestLayout->addWidget(mHComputeMethod, 3, 1);

  mFComputeMethodLabel = new QLabel(tr("Compute method:"));
  filteringTestLayout->addWidget(mFComputeMethodLabel, 4, 0);
  mFComputeMethod->addItem("7-point algorithm");
  mFComputeMethod->addItem("8-point algorithm");
  mFComputeMethod->addItem("RANSAC");
  mFComputeMethod->addItem("LMedS");
  filteringTestLayout->addWidget(mFComputeMethod, 4, 1);

  mEComputeMethodLabel = new QLabel(tr("Compute method:"));
  filteringTestLayout->addWidget(mEComputeMethodLabel, 5, 0);
  mEComputeMethod->addItem("RANSAC");
  mEComputeMethod->addItem("LMedS");
  filteringTestLayout->addWidget(mEComputeMethod, 5, 1);

  mDistanceLabel = new QLabel(tr("Distance:"));
  filteringTestLayout->addWidget(mDistanceLabel, 6, 0);
  mDistance->setRange(0.001, 100.);
  mDistance->setDecimals(3);
  mDistance->setSingleStep(0.1);
  filteringTestLayout->addWidget(mDistance, 6, 1);

  mConfidenceLabel = new QLabel(tr("Confidence:"));
  filteringTestLayout->addWidget(mConfidenceLabel, 7, 0);
  mConfidence->setRange(0., 1.);
  mConfidence->setDecimals(3);
  mConfidence->setSingleStep(0.001);
  filteringTestLayout->addWidget(mConfidence, 7, 1);

  mMaxItersLabel = new QLabel(tr("Maximum RANSAC iterations:"));
  filteringTestLayout->addWidget(mMaxItersLabel, 8, 0);
  mMaxIters->setRange(0, 10000);
  mMaxIters->setSingleStep(1);
  filteringTestLayout->addWidget(mMaxIters, 8, 1);

  mGroupBoxGMS = new QGroupBox(tr("GMS"), this);
  layout->addWidget(mGroupBoxGMS, 3, 0, 1, 2);

  QGridLayout *gmsLayout = new QGridLayout();
  mGroupBoxGMS->setLayout(gmsLayout);

  mRotationGMS->setText(tr("Rotation:"));
  gmsLayout->addWidget(mRotationGMS, 0, 0);

  mScaleGMS->setText(tr("Scale:"));
  gmsLayout->addWidget(mScaleGMS, 1, 0);

  gmsLayout->addWidget(new QLabel(tr("Threshold:")), 2, 0);
  mThresholdGMS->setDecimals(1);
  mThresholdGMS->setRange(0.1, 100.);
  mThresholdGMS->setSingleStep(0.1);
  gmsLayout->addWidget(mThresholdGMS, 2, 1);

  reset(); /// set default values

}

void DescriptorMatcherWidgetImp::initSignalAndSlots()
{
  connect(mMatchingMethod,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(matchingMethodChange(QString)));
  connect(mMatchingStrategy,     SIGNAL(currentTextChanged(QString)),  this, SIGNAL(matchingStrategyChange(QString)));
  connect(mNormType,             SIGNAL(currentTextChanged(QString)),  this, SIGNAL(normTypeChange(QString)));
  connect(mRatio,                SIGNAL(valueChanged(double)),         this, SIGNAL(ratioChange(double)));
  connect(mDistance,             SIGNAL(valueChanged(double)),         this, SIGNAL(distanceChange(double)));
  connect(mConfidence,           SIGNAL(valueChanged(double)),         this, SIGNAL(confidenceChange(double)));
  connect(mCrossMatching,        SIGNAL(clicked(bool)),                this, SIGNAL(crossMatchingChange(bool)));
  connect(mMaxIters,             SIGNAL(valueChanged(int)),            this, SIGNAL(maxItersChange(int)));
  connect(mGeometricTest,        SIGNAL(currentTextChanged(QString)),  this, SIGNAL(geometricTestChange(QString)));
  connect(mHComputeMethod,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(homographyComputeMethodChange(QString)));
  connect(mFComputeMethod,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(fundamentalComputeMethodChange(QString)));
  connect(mEComputeMethod,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(essentialComputeMethodChange(QString)));
  connect(mRotationGMS,          SIGNAL(clicked(bool)),                this, SIGNAL(gmsRotationChange(bool)));
  connect(mScaleGMS,             SIGNAL(clicked(bool)),                this, SIGNAL(gmsScaleChange(bool)));
  connect(mThresholdGMS,         SIGNAL(valueChanged(double)),         this, SIGNAL(gmsThresholdChange(double)));

  connect(this, SIGNAL(matchingMethodChange(QString)),           this,  SLOT(update()));
  connect(this, SIGNAL(matchingStrategyChange(QString)),         this,  SLOT(update()));
  connect(this, SIGNAL(geometricTestChange(QString)),            this,  SLOT(update()));
  connect(this, SIGNAL(homographyComputeMethodChange(QString)),  this,  SLOT(update()));
  connect(this, SIGNAL(fundamentalComputeMethodChange(QString)), this,  SLOT(update()));
  connect(this, SIGNAL(essentialComputeMethodChange(QString)),   this,  SLOT(update()));
}


} // namespace photomatch

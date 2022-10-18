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
#include <QApplication>

namespace photomatch
{

DescriptorMatcherWidgetImp::DescriptorMatcherWidgetImp(QWidget *parent)
  : DescriptorMatcherWidget(parent),
    mLabelMatchingMethod(new QLabel(this)),
    mMatchingMethod(new QComboBox(this)),
    mLabelMatchingStrategy(new QLabel(this)),
    mMatchingStrategy(new QComboBox(this)),
    mNormType(new QComboBox(this)),
    mNormTypeLabel(new QLabel(this)),
    mLabelRatio(new QLabel(this)),
    mRatio(new QDoubleSpinBox(this)),
    mLabelGeometricTest(new QLabel(this)),
    mGeometricTest(new QComboBox(this)),
    mDistance(new QDoubleSpinBox(this)),
    mDistanceLabel(new QLabel(this)),
    mConfidence(new QDoubleSpinBox(this)),
    mConfidenceLabel(new QLabel(this)),
    mMaxIters(new QSpinBox(this)),
    mMaxItersLabel(new QLabel(this)),
    mCheckBoxIsParallel(new QCheckBox(this)),
    mLabelLocalOptimIterations(new QLabel(this)),
    mSpinBoxLocalOptimIterations(new QSpinBox(this)),
    mLabelLocalSampleSize(new QLabel(this)),
    mSpinBoxLocalSampleSize(new QSpinBox(this)),
    mLabelLocalMaxIterations(new QLabel(this)),
    mSpinBoxLocalMaxIterations(new QSpinBox(this)),
    mCrossMatching(new QCheckBox(this)),
    mHComputeMethod(new QComboBox(this)),
    mHComputeMethodLabel(new QLabel(this)),
    mFComputeMethod(new QComboBox(this)),
    mFComputeMethodLabel(new QLabel(this)),
    mEComputeMethod(new QComboBox(this)),
    mEComputeMethodLabel(new QLabel(this)),
    mRotationGMS(new QCheckBox(this)),
    mScaleGMS(new QCheckBox(this)),
    mLabelThresholdGMS(new QLabel(this)),
    mThresholdGMS(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

DescriptorMatcherWidgetImp::~DescriptorMatcherWidgetImp()
{

}


void DescriptorMatcherWidgetImp::initUI()
{
  this->setObjectName("DescriptorMatcherWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mLabelMatchingMethod, 0, 0);
  mMatchingMethod->addItem("Brute-Force");
  mMatchingMethod->addItem("FLANN");
  layout->addWidget(mMatchingMethod, 0, 1);

  layout->addWidget(mLabelMatchingStrategy, 1, 0);
  mMatchingStrategy->addItem("Robust Matching");
  mMatchingStrategy->addItem("GMS");
  layout->addWidget(mMatchingStrategy, 1, 1);

  mGroupBoxBFParameters = new QGroupBox(this);
  layout->addWidget(mGroupBoxBFParameters, 2, 0, 1, 2);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBoxBFParameters->setLayout(propertiesLayout);

  propertiesLayout->addWidget(mNormTypeLabel, 0, 0);
  mNormType->addItem("NORM_L1");
  mNormType->addItem("NORM_L2");
  mNormType->addItem("NORM_HAMMING");
  mNormType->addItem("NORM_HAMMING2");
  propertiesLayout->addWidget(mNormType, 0, 1);

  /// Robust Matching

  mGroupBoxFilteringTest = new QGroupBox(this);
  layout->addWidget(mGroupBoxFilteringTest, 3, 0, 1, 2);

  QGridLayout *filteringTestLayout = new QGridLayout();
  mGroupBoxFilteringTest->setLayout(filteringTestLayout);

  filteringTestLayout->addWidget(mLabelRatio, 0, 0);
  mRatio->setDecimals(3);
  mRatio->setRange(0.001, 100.);
  mRatio->setSingleStep(0.1);
  filteringTestLayout->addWidget(mRatio, 0, 1);

  filteringTestLayout->addWidget(mCrossMatching, 1, 0);

  filteringTestLayout->addWidget(mLabelGeometricTest, 2, 0);
  mGeometricTest->addItem("");
  mGeometricTest->addItem("");
  //mGeometricTest->addItem("");
  filteringTestLayout->addWidget(mGeometricTest, 2, 1);

  filteringTestLayout->addWidget(mHComputeMethodLabel, 3, 0);
  mHComputeMethod->addItem("All Points");
  mHComputeMethod->addItem("RANSAC");
  mHComputeMethod->addItem("LMedS");
  mHComputeMethod->addItem("RHO");
  mHComputeMethod->addItem("USAC"); 
  filteringTestLayout->addWidget(mHComputeMethod, 3, 1);

  filteringTestLayout->addWidget(mFComputeMethodLabel, 4, 0);
  mFComputeMethod->addItem("7-point algorithm");
  mFComputeMethod->addItem("8-point algorithm");
  mFComputeMethod->addItem("RANSAC");
  mFComputeMethod->addItem("LMedS");
  mFComputeMethod->addItem("USAC");
  filteringTestLayout->addWidget(mFComputeMethod, 4, 1);

  filteringTestLayout->addWidget(mEComputeMethodLabel, 5, 0);
  mEComputeMethod->addItem("RANSAC");
  mEComputeMethod->addItem("LMedS");
  filteringTestLayout->addWidget(mEComputeMethod, 5, 1);

  filteringTestLayout->addWidget(mDistanceLabel, 6, 0);
  mDistance->setRange(0.001, 100.);
  mDistance->setDecimals(3);
  mDistance->setSingleStep(0.1);
  filteringTestLayout->addWidget(mDistance, 6, 1);

  filteringTestLayout->addWidget(mConfidenceLabel, 7, 0);
  mConfidence->setRange(0., 1.);
  mConfidence->setDecimals(3);
  mConfidence->setSingleStep(0.001);
  filteringTestLayout->addWidget(mConfidence, 7, 1);

  filteringTestLayout->addWidget(mMaxItersLabel, 8, 0);
  mMaxIters->setRange(0, 10000);
  mMaxIters->setSingleStep(1);
  filteringTestLayout->addWidget(mMaxIters, 8, 1);

  filteringTestLayout->addWidget(mCheckBoxIsParallel, 9, 0);

  filteringTestLayout->addWidget(mLabelLocalOptimIterations, 10, 0);
  //mSpinBoxLocalOptimIterations->setRange(0, 1000);
  //mSpinBoxLocalOptimIterations->setSingleStep(1);
  filteringTestLayout->addWidget(mSpinBoxLocalOptimIterations, 10, 1);

  filteringTestLayout->addWidget(mLabelLocalSampleSize, 11, 0);
  //mSpinBoxLocalSampleSize->setRange(0, 1000);
  //mSpinBoxLocalSampleSize->setSingleStep(1);
  filteringTestLayout->addWidget(mSpinBoxLocalSampleSize, 11, 1);

  filteringTestLayout->addWidget(mLabelLocalMaxIterations, 12, 0);
  //mSpinBoxLocalMaxIterations->setRange(0, 1000);
  //mSpinBoxLocalMaxIterations->setSingleStep(1);
  filteringTestLayout->addWidget(mSpinBoxLocalMaxIterations, 12, 1);


  mGroupBoxGMS = new QGroupBox("GMS", this);
  layout->addWidget(mGroupBoxGMS, 3, 0, 1, 2);

  QGridLayout *gmsLayout = new QGridLayout();
  mGroupBoxGMS->setLayout(gmsLayout);

  gmsLayout->addWidget(mRotationGMS, 0, 0);

  gmsLayout->addWidget(mScaleGMS, 1, 0);

  gmsLayout->addWidget(mLabelThresholdGMS, 2, 0);
  mThresholdGMS->setDecimals(1);
  mThresholdGMS->setRange(0.1, 100.);
  mThresholdGMS->setSingleStep(0.1);
  gmsLayout->addWidget(mThresholdGMS, 2, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void DescriptorMatcherWidgetImp::initSignalAndSlots()
{
  connect(mMatchingMethod,    &QComboBox::currentTextChanged,                       this, &DescriptorMatcherWidget::matchingMethodChange);
  connect(mMatchingStrategy,  &QComboBox::currentTextChanged,                       this, &DescriptorMatcherWidget::matchingStrategyChange);
  connect(mNormType,          &QComboBox::currentTextChanged,                       this, &DescriptorMatcherWidget::normTypeChange);
  connect(mRatio,             QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DescriptorMatcherWidget::ratioChange);
  connect(mDistance,          QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DescriptorMatcherWidget::distanceChange);
  connect(mConfidence,        QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DescriptorMatcherWidget::confidenceChange);
  connect(mCrossMatching,     &QAbstractButton::clicked,                            this, &DescriptorMatcherWidget::crossMatchingChange);
  connect(mMaxIters,          QOverload<int>::of(&QSpinBox::valueChanged),          this, &DescriptorMatcherWidget::maxItersChange);
  connect(mCheckBoxIsParallel, &QAbstractButton::clicked,                           this, &DescriptorMatcherWidget::usacIsParallelChanged);
  connect(mSpinBoxLocalOptimIterations, QOverload<int>::of(&QSpinBox::valueChanged), this, &DescriptorMatcherWidget::usacLocalOptimIterationsChanged);
  connect(mSpinBoxLocalSampleSize, QOverload<int>::of(&QSpinBox::valueChanged), this, &DescriptorMatcherWidget::usacLocalSampleSizeChanged);
  connect(mSpinBoxLocalMaxIterations, QOverload<int>::of(&QSpinBox::valueChanged), this, &DescriptorMatcherWidget::usacMaxItersChanged);
  connect(mGeometricTest,     &QComboBox::currentTextChanged,                       this, &DescriptorMatcherWidget::geometricTestChange);
  connect(mHComputeMethod,    &QComboBox::currentTextChanged,                       this, &DescriptorMatcherWidget::homographyComputeMethodChange);
  connect(mFComputeMethod,    &QComboBox::currentTextChanged,                       this, &DescriptorMatcherWidget::fundamentalComputeMethodChange);
  connect(mEComputeMethod,    &QComboBox::currentTextChanged,                       this, &DescriptorMatcherWidget::essentialComputeMethodChange);
  connect(mRotationGMS,       &QAbstractButton::clicked,                            this, &DescriptorMatcherWidget::gmsRotationChange);
  connect(mScaleGMS,          &QAbstractButton::clicked,                            this, &DescriptorMatcherWidget::gmsScaleChange);
  connect(mThresholdGMS,      QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &DescriptorMatcherWidget::gmsThresholdChange);

  connect(this, SIGNAL(matchingMethodChange(QString)),           this,  SLOT(update()));
  connect(this, SIGNAL(matchingStrategyChange(QString)),         this,  SLOT(update()));
  connect(this, SIGNAL(geometricTestChange(QString)),            this,  SLOT(update()));
  connect(this, SIGNAL(homographyComputeMethodChange(QString)),  this,  SLOT(update()));
  connect(this, SIGNAL(fundamentalComputeMethodChange(QString)), this,  SLOT(update()));
  connect(this, SIGNAL(essentialComputeMethodChange(QString)),   this,  SLOT(update()));
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
  const QSignalBlocker blockerSpinBoxLocalSampleSize(mSpinBoxLocalSampleSize);
  const QSignalBlocker blockerSpinBoxLocalOptimIterations(mSpinBoxLocalOptimIterations);
  const QSignalBlocker blockerSpinBoxLocalMaxIterations(mSpinBoxLocalMaxIterations);

  mMatchingMethod->setCurrentText("Brute-Force");
  mNormType->setCurrentText("NORM_L1");
  mGroupBoxBFParameters->show();
  mMatchingStrategy->setCurrentText(QApplication::translate("DescriptorMatcherWidget", "Robust Matching"));
  mGroupBoxFilteringTest->show();
  mGroupBoxGMS->hide();
  mRatio->setValue(0.8);
  mGeometricTest->setCurrentText(QApplication::translate("DescriptorMatcherWidget", "Fundamental Matrix"));
  mHComputeMethod->setCurrentText("RANSAC");
  mFComputeMethod->setCurrentText("RANSAC");
  mEComputeMethod->setCurrentText("RANSAC");
  mDistance->setValue(0.7);
  mConfidence->setValue(0.999);
  mMaxIters->setValue(2000);
  mCheckBoxIsParallel->setChecked(false);
  mSpinBoxLocalOptimIterations->setValue(5);
  mSpinBoxLocalSampleSize->setValue(14);
  mSpinBoxLocalMaxIterations->setValue(5000);
  mCrossMatching->setChecked(true);
  mRotationGMS->setChecked(false);
  mScaleGMS->setChecked(false);
  mThresholdGMS->setValue(6.0);

  update();
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
  if (geomTest.compare(QApplication::translate("DescriptorMatcherWidget", "Homography Matrix")) == 0){
    mHComputeMethod->show();
    mHComputeMethodLabel->show();
    mFComputeMethod->hide();
    mFComputeMethodLabel->hide();
    mEComputeMethod->hide();
    mEComputeMethodLabel->hide();
    QString computeMethod = mHComputeMethod->currentText();
    mConfidence->show();
    mConfidenceLabel->show();
    mCheckBoxIsParallel->hide();
    mLabelLocalOptimIterations->hide();
    mSpinBoxLocalOptimIterations->hide();
    mLabelLocalSampleSize->hide();
    mSpinBoxLocalSampleSize->hide();
    mLabelLocalMaxIterations->hide();
    mSpinBoxLocalMaxIterations->hide();
    if (computeMethod.compare(QApplication::translate("DescriptorMatcherWidget", "All Points")) == 0){
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
    } else if(computeMethod.compare("USAC") == 0) {
      mCheckBoxIsParallel->show();
      mLabelLocalOptimIterations->show();
      mSpinBoxLocalOptimIterations->show();
      mLabelLocalSampleSize->show();
      mSpinBoxLocalSampleSize->show();
      mLabelLocalMaxIterations->show();
      mSpinBoxLocalMaxIterations->show();
      mDistance->hide();
      mDistanceLabel->hide();
      mMaxIters->hide();
      mMaxItersLabel->hide();
    }
  } else if (geomTest.compare(QApplication::translate("DescriptorMatcherWidget", "Fundamental Matrix")) == 0){
    mHComputeMethod->hide();
    mHComputeMethodLabel->hide();
    mFComputeMethod->show();
    mFComputeMethodLabel->show();
    mEComputeMethod->hide();
    mEComputeMethodLabel->hide();
    QString computeMethod = mFComputeMethod->currentText();
    mMaxIters->hide();
    mMaxItersLabel->hide();
    mCheckBoxIsParallel->hide();
    mLabelLocalOptimIterations->hide();
    mSpinBoxLocalOptimIterations->hide();
    mLabelLocalSampleSize->hide();
    mSpinBoxLocalSampleSize->hide();
    mLabelLocalMaxIterations->hide();
    mSpinBoxLocalMaxIterations->hide();
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
      mMaxIters->hide();
      mMaxItersLabel->hide();
    } else if (computeMethod.compare("LMedS") == 0){
      mDistance->hide();
      mDistanceLabel->hide();
      mConfidence->show();
      mConfidenceLabel->show();
    } else if(computeMethod.compare("USAC") == 0) {
      mCheckBoxIsParallel->show();
      mLabelLocalOptimIterations->show();
      mSpinBoxLocalOptimIterations->show();
      mLabelLocalSampleSize->show();
      mSpinBoxLocalSampleSize->show();
      mLabelLocalMaxIterations->show();
      mSpinBoxLocalMaxIterations->show();
      mDistance->hide();
      mDistanceLabel->hide();
      mMaxIters->hide();
      mMaxItersLabel->hide();
    }
  } else if (geomTest.compare(QApplication::translate("DescriptorMatcherWidget", "Essential Matrix")) == 0) {
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
  this->setWindowTitle(QApplication::translate("DescriptorMatcherWidget", "Descriptor Matcher"));
  mLabelMatchingMethod->setText(QApplication::translate("DescriptorMatcherWidget", "Matching Method:"));
  mLabelMatchingStrategy->setText(QApplication::translate("DescriptorMatcherWidget", "Matching Strategy:"));
  mGroupBoxBFParameters->setTitle(QApplication::translate("DescriptorMatcherWidget", "Brute Force Parameters"));
  mNormTypeLabel->setText(QApplication::translate("DescriptorMatcherWidget", "Norm Type:"));
  mGroupBoxFilteringTest->setTitle(QApplication::translate("DescriptorMatcherWidget", "Filtering Test"));
  mLabelRatio->setText(QApplication::translate("DescriptorMatcherWidget", "Ratio:"));
  mCrossMatching->setText(QApplication::translate("DescriptorMatcherWidget", "Cross Matching"));
  mLabelGeometricTest->setText(QApplication::translate("DescriptorMatcherWidget", "Geometric Test:"));
  mHComputeMethodLabel->setText(QApplication::translate("DescriptorMatcherWidget", "Compute method:"));
  mFComputeMethodLabel->setText(QApplication::translate("DescriptorMatcherWidget", "Compute method:"));
  mEComputeMethodLabel->setText(QApplication::translate("DescriptorMatcherWidget", "Compute method:"));
  mDistanceLabel->setText(QApplication::translate("DescriptorMatcherWidget", "Distance:"));
  mConfidenceLabel->setText(QApplication::translate("DescriptorMatcherWidget", "Confidence:"));
  mMaxItersLabel->setText(QApplication::translate("DescriptorMatcherWidget", "Maximum RANSAC iterations:"));
  mLabelThresholdGMS->setText(QApplication::translate("DescriptorMatcherWidget", "Threshold:"));
  mRotationGMS->setText(QApplication::translate("DescriptorMatcherWidget", "Rotation:"));
  mScaleGMS->setText(QApplication::translate("DescriptorMatcherWidget", "Scale:"));
  mCheckBoxIsParallel->setText(QApplication::translate("DescriptorMatcherWidget", "Parallel"));
  mLabelLocalOptimIterations->setText(QApplication::translate("DescriptorMatcherWidget", "Local Optim Iterations:"));
  mLabelLocalSampleSize->setText(QApplication::translate("DescriptorMatcherWidget", "Local Sample Size:"));
  mLabelLocalMaxIterations->setText(QApplication::translate("DescriptorMatcherWidget", "Local Max Iterations:"));

  mGeometricTest->setItemText(0, QApplication::translate("DescriptorMatcherWidget", "Homography Matrix"));
  mGeometricTest->setItemText(1, QApplication::translate("DescriptorMatcherWidget", "Fundamental Matrix"));
  //mGeometricTest->setItemText(2, QApplication::translate("DescriptorMatcherWidget", "Essential Matrix"));  /// Desactivada matriz esencial porque se necesitaria calibración de la cámara y no es el objetivo de la herramienta

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

bool DescriptorMatcherWidgetImp::usacIsParallel() const
{
  return mCheckBoxIsParallel->isChecked();
}

int DescriptorMatcherWidgetImp::usacLocalOptimIterations() const
{
  return mSpinBoxLocalOptimIterations->value();
}

int DescriptorMatcherWidgetImp::usacLocalSampleSize() const
{
  return mSpinBoxLocalSampleSize->value();
}

int DescriptorMatcherWidgetImp::usacMaxIters() const
{
  return mSpinBoxLocalMaxIterations->value();
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

void DescriptorMatcherWidgetImp::setUsacIsParallel(bool usacIsParallel)
{
  mCheckBoxIsParallel->setChecked(usacIsParallel);
}

void DescriptorMatcherWidgetImp::setUsacLocalOptimIterations(int usacLocalOptimIterations)
{
  mSpinBoxLocalOptimIterations->setValue(usacLocalOptimIterations);
}

void DescriptorMatcherWidgetImp::setUsacLocalSampleSize(int usacLocalSampleSize)
{ 
  mSpinBoxLocalSampleSize->setValue(usacLocalSampleSize);
}

void DescriptorMatcherWidgetImp::setUsacMaxIters(int usacMaxIters)
{
  mSpinBoxLocalMaxIterations->setValue(usacMaxIters);
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

} // namespace photomatch

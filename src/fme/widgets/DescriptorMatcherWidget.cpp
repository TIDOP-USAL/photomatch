#include "DescriptorMatcherWidget.h"

#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QGroupBox>
#include <QStandardItemModel>

namespace fme
{

DescriptorMatcherWidget::DescriptorMatcherWidget(QWidget *parent)
  : IDescriptorMatcherWidget(parent),
    mMatchingMethod(new QComboBox(this)),
    mNormType(new QComboBox(this)),
    mRatio(new QDoubleSpinBox(this)),
    mGeometricTest(new QComboBox(this)),
    mDistance(new QDoubleSpinBox(this)),
    mConfidence(new QDoubleSpinBox(this)),
    mMaxIters(new QSpinBox(this)),
    mCrossMatching(new QCheckBox(this)),
    mHComputeMethod(new QComboBox(this)),
    mFComputeMethod(new QComboBox(this)),
    mEComputeMethod(new QComboBox(this))
{
  init();

  /// Signals and slots
  connect(mMatchingMethod,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(matchingMethodChange(QString)));
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

//  connect(this, SIGNAL(matchingMethodChange(QString)), this, SLOT(onMatchingMethodChanged(QString)));
//  connect(this, SIGNAL(homographyComputeMethodChange(QString)), this, SLOT(onHomographyComputeMethodChange(QString)));
//  connect(this, SIGNAL(fundamentalComputeMethodChange(QString)), this, SLOT(onFundamentalComputeMethodChange(QString)));
//  connect(this, SIGNAL(essentialComputeMethodChange(QString)), this, SLOT(onEssentialComputeMethodChange(QString)));
  connect(this, SIGNAL(matchingMethodChange(QString)),           this,  SLOT(update()));
  connect(this, SIGNAL(geometricTestChange(QString)),            this,  SLOT(update()));
  connect(this, SIGNAL(homographyComputeMethodChange(QString)),  this,  SLOT(update()));
  connect(this, SIGNAL(fundamentalComputeMethodChange(QString)), this,  SLOT(update()));
  connect(this, SIGNAL(essentialComputeMethodChange(QString)),   this,  SLOT(update()));
}

DescriptorMatcherWidget::~DescriptorMatcherWidget()
{

}

QString DescriptorMatcherWidget::matchingMethod() const
{
  return mMatchingMethod->currentText();
}

QString DescriptorMatcherWidget::normType() const
{
  return mNormType->currentText();
}

double DescriptorMatcherWidget::ratio() const
{
  return mRatio->value();
}

QString DescriptorMatcherWidget::geometricTest() const
{
  return mGeometricTest->currentText();
}

QString DescriptorMatcherWidget::homographyComputeMethod() const
{
  return mHComputeMethod->currentText();
}

QString DescriptorMatcherWidget::fundamentalComputeMethod() const
{
  return mFComputeMethod->currentText();
}

QString DescriptorMatcherWidget::essentialComputeMethod() const
{
  return mEComputeMethod->currentText();
}

double DescriptorMatcherWidget::distance() const
{
  return mDistance->value();
}

double DescriptorMatcherWidget::confidence() const
{
  return mConfidence->value();
}

int DescriptorMatcherWidget::maxIters() const
{
  return mMaxIters->value();
}

bool DescriptorMatcherWidget::crossMatching() const
{
  return mCrossMatching->isChecked();
}

void DescriptorMatcherWidget::setMatchingMethod(const QString &matchingMethod)
{
  const QSignalBlocker blockerMatchingMethod(mMatchingMethod);
  mMatchingMethod->setCurrentText(matchingMethod);
  //onMatchingMethodChanged(matchingMethod);
  update();
}

void DescriptorMatcherWidget::setNormType(const QString &normType)
{
  const QSignalBlocker blockerNormType(mNormType);
  mNormType->setCurrentText(normType);
}

void DescriptorMatcherWidget::setRatio(double ratio)
{
  const QSignalBlocker blockerRatio(mRatio);
  mRatio->setValue(ratio);
}

void DescriptorMatcherWidget::setGeometricTest(const QString &geometricTest)
{
  const QSignalBlocker blockerGeometricTest(mGeometricTest);
  mGeometricTest->setCurrentText(geometricTest);
  update();
}

void DescriptorMatcherWidget::setHomographyComputeMethod(const QString &computeMethod)
{
  const QSignalBlocker blockerHomographyComputeMethod(mHComputeMethod);
  mHComputeMethod->setCurrentText(computeMethod);
  update();
}

void DescriptorMatcherWidget::setFundamentalComputeMethod(const QString &computeMethod)
{
  const QSignalBlocker blockerFundamentalComputeMethod(mFComputeMethod);
  mFComputeMethod->setCurrentText(computeMethod);
  update();
}

void DescriptorMatcherWidget::setEssentialComputeMethod(const QString &computeMethod)
{
  const QSignalBlocker blockerEssentialComputeMethod(mEComputeMethod);
  mEComputeMethod->setCurrentText(computeMethod);
  update();
}

void DescriptorMatcherWidget::setDistance(double distance)
{
  const QSignalBlocker blockerDistance(mDistance);
  mDistance->setValue(distance);
}

void DescriptorMatcherWidget::setConfidence(double confidence)
{
  const QSignalBlocker blockerConfidence(mConfidence);
  mConfidence->setValue(confidence);
}

void DescriptorMatcherWidget::setMaxIters(int maxIter)
{
  const QSignalBlocker blockerMaxIters(mMaxIters);
  mMaxIters->setValue(maxIter);
}

void DescriptorMatcherWidget::setCrossMatching(bool crossMatching)
{
  mCrossMatching->setChecked(crossMatching);
}

void DescriptorMatcherWidget::disableBruteForceNorm(const QString &norm)
{
  QStandardItemModel *model = qobject_cast<QStandardItemModel *>(mNormType->model());
  if (model != nullptr) {
    QList<QStandardItem *> items = model->findItems(norm);
    for (auto &item : items){
      item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
  }
}

void DescriptorMatcherWidget::enableBruteForceNorm(const QString &norm)
{
  QStandardItemModel *model = qobject_cast<QStandardItemModel *>(mNormType->model());
  if (model != nullptr) {
    QList<QStandardItem *> items = model->findItems(norm);
    for (auto &item : items){
      item->setFlags(item->flags() | Qt::ItemIsEnabled);
    }
  }
}

void DescriptorMatcherWidget::update()
{
  if (mMatchingMethod->currentText().compare("FLANN") == 0){
    mGroupBoxBFParameters->hide();
  } else {
    mGroupBoxBFParameters->show();
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

void DescriptorMatcherWidget::reset()
{
  const QSignalBlocker blockerMatchingMethod(mMatchingMethod);
  const QSignalBlocker blockerNormType(mNormType);
  const QSignalBlocker blockerRatio(mRatio);
  const QSignalBlocker blockerGeometricTest(mGeometricTest);
  const QSignalBlocker blockerHomographyComputeMethod(mHComputeMethod);
  const QSignalBlocker blockerFundamentalComputeMethod(mFComputeMethod);
  const QSignalBlocker blockerEssentialComputeMethod(mEComputeMethod);
  const QSignalBlocker blockerDistance(mDistance);
  const QSignalBlocker blockerConfidence(mConfidence);
  const QSignalBlocker blockerMaxIters(mMaxIters);

  mMatchingMethod->setCurrentText("Brute-Force");
  mNormType->setCurrentText("NORM_L1");
  mGroupBoxBFParameters->show();
  mRatio->setValue(0.8);
  mGeometricTest->setCurrentText("Homography Matrix");
  mHComputeMethod->setCurrentText("RANSAC");
  mFComputeMethod->setCurrentText("RANSAC");
  mEComputeMethod->setCurrentText("RANSAC");
  mDistance->setValue(0.7);
  mConfidence->setValue(0.999);
  mMaxIters->setValue(2000);
  mCrossMatching->setChecked(true);

  update();
}

void DescriptorMatcherWidget::init()
{
  this->setWindowTitle("Descriptor Matcher");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(new QLabel(tr("Matching Method:")), 0, 0);
  mMatchingMethod->addItem("Brute-Force");
  mMatchingMethod->addItem("FLANN");
  layout->addWidget(mMatchingMethod, 0, 1);

  mGroupBoxBFParameters = new QGroupBox(tr("Brute Force Parameters"), this);
  layout->addWidget(mGroupBoxBFParameters, 1, 0, 1, 2);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBoxBFParameters->setLayout(propertiesLayout);

  mNormTypeLabel = new QLabel(tr("Norm Type:"), this);
  propertiesLayout->addWidget(mNormTypeLabel, 0, 0);
  mNormType->addItem("NORM_L1");
  mNormType->addItem("NORM_L2");
  mNormType->addItem("NORM_HAMMING");
  mNormType->addItem("NORM_HAMMING2");
  propertiesLayout->addWidget(mNormType, 0, 1);

  mGroupBoxFilteringTest = new QGroupBox(tr("Filtering Test"), this);
  layout->addWidget(mGroupBoxFilteringTest, 2, 0, 1, 2);

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
  mGeometricTest->addItem("Essential Matrix");
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

  reset(); /// set default values

}

//void DescriptorMatcherWidget::onMatchingMethodChanged(const QString &matchingMethod)
//{
//  if (matchingMethod.compare("FLANN") == 0){
//    //mNormTypeLabel->hide();
//    //mNormType->hide();
//    mGroupBoxBFParameters->hide();
//  } else {
//    //mNormTypeLabel->show();
//    //mNormType->show();
//    mGroupBoxBFParameters->show();
//  }
//}

//void DescriptorMatcherWidget::onHomographyComputeMethodChange(const QString &homographyComputeMethod)
//{
//  if (homographyComputeMethod.compare("All Points") == 0){

//  } else if (homographyComputeMethod.compare("RANSAC") == 0){

//  } else if (homographyComputeMethod.compare("LMEDS") == 0){

//  } else if (homographyComputeMethod.compare("RHO") == 0){

//  }
//}

//void DescriptorMatcherWidget::onFundamentalComputeMethodChange(const QString &fundamentalComputeMethod)
//{
//  if (fundamentalComputeMethod.compare("7-point algorithm") == 0){

//  } else if (fundamentalComputeMethod.compare("8-point algorithm") == 0){

//  } else if (fundamentalComputeMethod.compare("RANSAC") == 0){

//  } else if (fundamentalComputeMethod.compare("LMedS") == 0){

//  }
//}

//void DescriptorMatcherWidget::onEssentialComputeMethodChange(const QString &essentialComputeMethod)
//{
//  if (essentialComputeMethod.compare("RANSAC") == 0){
//    mDistance->show();
//  } else if (essentialComputeMethod.compare("LMedS") == 0){
//    mDistance->hide();
//  }
//}


} // namespace fme

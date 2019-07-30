#include "FeatureExtractorView.h"

#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QStandardItemModel>

namespace fme
{

FeatureExtractorView::FeatureExtractorView(QWidget *parent)
  : IFeatureExtractorView(parent),
    mButtonBox(new QDialogButtonBox(this))
{
  init();

  connect(mComboBoxKeypointDetector,     SIGNAL(currentTextChanged(QString)), this, SIGNAL(keypointDetectorChange(QString)));
  connect(mComboBoxDescriptorExtractor,  SIGNAL(currentTextChanged(QString)), this, SIGNAL(descriptorExtractorChange(QString)));

  connect(mButtonBox,                                    SIGNAL(rejected()),      this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Apply),   SIGNAL(clicked(bool)),   this, SIGNAL(run()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)),   this, SIGNAL(help()));
}

FeatureExtractorView::~FeatureExtractorView()
{

}

void FeatureExtractorView::addKeypointDetector(QWidget *keypointDetector)
{
  mComboBoxKeypointDetector->addItem(keypointDetector->windowTitle());
  mGridLayoutKeypointDetector->addWidget(keypointDetector, 2, 0, 1, 2);
  keypointDetector->setVisible(false);
}

void FeatureExtractorView::addDescriptorExtractor(QWidget *descriptorExtractor)
{
  mComboBoxDescriptorExtractor->addItem(descriptorExtractor->windowTitle());
  mGridLayoutDescriptorExtractor->addWidget(descriptorExtractor, 4, 0, 1, 2);
  descriptorExtractor->setVisible(false);
}

QString FeatureExtractorView::currentKeypointDetector() const
{
  return mCurrentKeypointDetector;
}

QString FeatureExtractorView::currentDescriptorExtractor() const
{
  return mCurrentDescriptorExtractor;
}

void FeatureExtractorView::setCurrentKeypointDetector(const QString &keypointDetector)
{
  mCurrentKeypointDetector = keypointDetector;

  const QSignalBlocker blocker(mComboBoxKeypointDetector);
  mComboBoxKeypointDetector->setCurrentText(keypointDetector);
  for (int idx = 0; idx < mGridLayoutKeypointDetector->count(); idx++){
    QLayoutItem * const item = mGridLayoutKeypointDetector->itemAt(idx);
    if(dynamic_cast<QWidgetItem *>(item)){
      if (item->widget()->windowTitle().compare(keypointDetector) == 0)
        item->widget()->setVisible(true);
      else
        item->widget()->setVisible(false);
    }
  }
}

void FeatureExtractorView::setCurrentDescriptorExtractor(const QString &descriptorExtractor)
{
  mCurrentDescriptorExtractor = descriptorExtractor;

  const QSignalBlocker blocker(mComboBoxDescriptorExtractor);
  mComboBoxDescriptorExtractor->setCurrentText(descriptorExtractor);
  for (int idx = 0; idx < mGridLayoutDescriptorExtractor->count(); idx++){
    QLayoutItem * const item = mGridLayoutDescriptorExtractor->itemAt(idx);
    if(dynamic_cast<QWidgetItem *>(item)){
      QString feature_title = item->widget()->windowTitle();
      if (feature_title.compare(descriptorExtractor) == 0 &&
          feature_title.compare(mComboBoxKeypointDetector->currentText()) != 0){
        item->widget()->setVisible(true);
      } else {
        item->widget()->setVisible(false);
      }
    }
  }
}

void FeatureExtractorView::disableDescriptorExtractor(const QString &descriptorExtractor)
{
  QStandardItemModel *model = qobject_cast<QStandardItemModel *>(mComboBoxDescriptorExtractor->model());
  if (model != nullptr) {
    QList<QStandardItem *> items = model->findItems(descriptorExtractor);
    for (auto &item : items){
      item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
  }
}

void FeatureExtractorView::enableDescriptorExtractor(const QString &descriptorExtractor)
{
  QStandardItemModel *model = qobject_cast<QStandardItemModel *>(mComboBoxDescriptorExtractor->model());
  if (model != nullptr) {
    QList<QStandardItem *> items = model->findItems(descriptorExtractor);
    for (auto &item : items){
      item->setFlags(item->flags() | Qt::ItemIsEnabled);
    }
  }
}

void FeatureExtractorView::init()
{
  this->setWindowTitle(tr("FeatureExtractor"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(350, 450);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  gridLayout->addWidget(new QLabel("Keypoint Detector:"), 0, 0, 1, 1);
  mComboBoxKeypointDetector = new QComboBox(this);
  gridLayout->addWidget(mComboBoxKeypointDetector, 0, 1, 1, 1);

  gridLayout->addWidget(new QLabel("Descriptor Extractor:"), 1, 0, 1, 1);
  mComboBoxDescriptorExtractor = new QComboBox(this);
  gridLayout->addWidget(mComboBoxDescriptorExtractor, 1, 1, 1, 1);

  QWidget *widgetFeatureExtractor = new QWidget();
  mGridLayoutKeypointDetector = new QGridLayout(widgetFeatureExtractor);
  mGridLayoutKeypointDetector->setContentsMargins(0, 0, 0, 0);
  gridLayout->addWidget(widgetFeatureExtractor, 2, 0, 1, 2);

  QWidget *widgetDescriptorExtractor = new QWidget();
  mGridLayoutDescriptorExtractor = new QGridLayout(widgetDescriptorExtractor);
  mGridLayoutDescriptorExtractor->setContentsMargins(0, 0, 0, 0);
  gridLayout->addWidget(widgetDescriptorExtractor, 3, 0, 1, 2);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  //mButtonBox->button(QDialogButtonBox::Ok)->setText("Ok");
  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Apply)->setText("Run");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  gridLayout->addWidget(mButtonBox, 4, 0, 1, 2);


  update();
}

void FeatureExtractorView::clear()
{
  mCurrentKeypointDetector.clear();
  mCurrentDescriptorExtractor.clear();
}

void FeatureExtractorView::update()
{

}

} // namespace fme

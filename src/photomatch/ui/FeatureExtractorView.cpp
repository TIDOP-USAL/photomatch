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


#include "FeatureExtractorView.h"

#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QStandardItemModel>

namespace photomatch
{

FeatureExtractorViewImp::FeatureExtractorViewImp(QWidget *parent)
  : FeatureExtractorView(parent),
    mButtonBox(new QDialogButtonBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

FeatureExtractorViewImp::~FeatureExtractorViewImp()
{

}

void FeatureExtractorViewImp::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Feature Extractor ").append(name));
}

void FeatureExtractorViewImp::addKeypointDetector(QWidget *keypointDetector)
{
  mComboBoxKeypointDetector->addItem(keypointDetector->windowTitle());
  mGridLayoutKeypointDetector->addWidget(keypointDetector, 0, 0, 1, 2);
  keypointDetector->setVisible(false);
}

void FeatureExtractorViewImp::addDescriptorExtractor(QWidget *descriptorExtractor)
{
  mComboBoxDescriptorExtractor->addItem(descriptorExtractor->windowTitle());
  mGridLayoutDescriptorExtractor->addWidget(descriptorExtractor, 0, 0, 1, 2);
  descriptorExtractor->setVisible(false);
}

QString FeatureExtractorViewImp::currentKeypointDetector() const
{
  return mCurrentKeypointDetector;
}

QString FeatureExtractorViewImp::currentDescriptorExtractor() const
{
  return mCurrentDescriptorExtractor;
}

void FeatureExtractorViewImp::addKeypointsFilter(QWidget *keypointsFilter)
{
  mGridLayoutKeypointsFilter->addWidget(keypointsFilter, 0, 0, 1, 2);
}

void FeatureExtractorViewImp::setCurrentKeypointDetector(const QString &keypointDetector)
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

void FeatureExtractorViewImp::setCurrentDescriptorExtractor(const QString &descriptorExtractor)
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

void FeatureExtractorViewImp::disableDescriptorExtractor(const QString &descriptorExtractor)
{
  QStandardItemModel *model = qobject_cast<QStandardItemModel *>(mComboBoxDescriptorExtractor->model());
  if (model != nullptr) {
    QList<QStandardItem *> items = model->findItems(descriptorExtractor);
    for (auto &item : items){
      item->setFlags(item->flags() & ~Qt::ItemIsEnabled);
    }
  }
}

void FeatureExtractorViewImp::enableDescriptorExtractor(const QString &descriptorExtractor)
{
  QStandardItemModel *model = qobject_cast<QStandardItemModel *>(mComboBoxDescriptorExtractor->model());
  if (model != nullptr) {
    QList<QStandardItem *> items = model->findItems(descriptorExtractor);
    for (auto &item : items){
      item->setFlags(item->flags() | Qt::ItemIsEnabled);
    }
  }
}

void FeatureExtractorViewImp::initUI()
{
  this->setWindowTitle(tr("Feature Extractor"));
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

  QWidget *widgetKeypointsFilter = new QWidget();
  mGridLayoutKeypointsFilter = new QGridLayout(widgetKeypointsFilter);
  mGridLayoutKeypointsFilter->setContentsMargins(0, 0, 0, 0);
  gridLayout->addWidget(widgetKeypointsFilter, 4, 0, 1, 2);

  gridLayout->addItem(new QSpacerItem(1,1, QSizePolicy::Fixed, QSizePolicy::Expanding), 5, 0, 1, 2);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Apply)->setText("Run");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  gridLayout->addWidget(mButtonBox, 6, 0, 1, 2);


  update();
}

void FeatureExtractorViewImp::initSignalAndSlots()
{
  connect(mComboBoxKeypointDetector,     SIGNAL(currentTextChanged(QString)), this, SIGNAL(keypointDetectorChange(QString)));
  connect(mComboBoxDescriptorExtractor,  SIGNAL(currentTextChanged(QString)), this, SIGNAL(descriptorExtractorChange(QString)));

  connect(mButtonBox,                                    SIGNAL(rejected()),      this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Apply),   SIGNAL(clicked(bool)),   this, SIGNAL(run()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)),   this, SIGNAL(help()));
}

void FeatureExtractorViewImp::clear()
{
  mCurrentKeypointDetector.clear();
  mCurrentDescriptorExtractor.clear();
}

void FeatureExtractorViewImp::update()
{

}

void FeatureExtractorViewImp::retranslate()
{

}

} // namespace photomatch

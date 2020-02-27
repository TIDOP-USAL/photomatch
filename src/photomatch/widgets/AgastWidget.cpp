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


#include "AgastWidget.h"

#include <QSpinBox>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

AgastWidgetImp::AgastWidgetImp(QWidget *parent)
  : AgastWidget(parent),
    mThreshold(new QSpinBox(this)),
    mNonmaxSuppression(new QCheckBox(this)),
    mDetectorType(new QComboBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
  this->retranslate();
}

AgastWidgetImp::~AgastWidgetImp()
{

}

int AgastWidgetImp::threshold() const
{
  return mThreshold->value();
}

bool AgastWidgetImp::nonmaxSuppression() const
{
  return mNonmaxSuppression->isChecked();
}

QString AgastWidgetImp::detectorType() const
{
  return mDetectorType->currentText();
}

void AgastWidgetImp::setThreshold(int threshold)
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  mThreshold->setValue(threshold);
}

void AgastWidgetImp::setNonmaxSuppression(bool nonmaxSuppression)
{
  mNonmaxSuppression->setChecked(nonmaxSuppression);
}

void AgastWidgetImp::setDetectorType(const QString &detectorType)
{
  const QSignalBlocker blockerDetectorType(mDetectorType);
  mDetectorType->setCurrentText(detectorType);
}

void AgastWidgetImp::update()
{

}

void AgastWidgetImp::retranslate()
{
#ifndef QT_NO_WHATSTHIS
  mThreshold->setWhatsThis(tr("<html><head/><body><p>The <strong>AST (Accelerated Segment Test)</strong> applies a minimum difference <strong>threshold</strong> when comparing&nbsp;the value of a pixel on the circular pattern with the brightness of the nucleus.&nbsp;This parameter controls the sensitivity of the corner response. A large <strong>threshold</strong>&nbsp;value&nbsp;results in few but therefore only strong corners, while a small <strong>threshold</strong> value yields also&nbsp;corners with smoother gradients.</p></body></html>"));
  mNonmaxSuppression->setWhatsThis(tr("<html><head/><body><p><strong>Non Maximal Suppression</strong> for removing adjacent corners</p></body></html>"));
  mDetectorType->setWhatsThis(tr("<html><head/><body><p>AST (Accelerated Segment Test) decision tree and mask used. Suported types are:</p>"
                                 "<ul>"
                                 "<li><strong>AGAST_5_8</strong>: AGAST-5 decision tree with 8 pixels mask</li>"
                                 "<li><strong>AGAST_7_12d</strong>: AGAST-7 decision tree with Diamond shaped 12 pixels mask</li>"
                                 "<li><strong>AGAST_7_12s</strong>: AGAST-7 decision tree with Squared shaped 12 pixels mask</li>"
                                 "<li><strong>OAST_9_16</strong>: OAST-9 (Optimal AST) decision tree with 16 pixels mask</li>"
                                 "</ul></body></html>"));
#endif // QT_NO_WHATSTHIS
}

void AgastWidgetImp::reset()
{
  const QSignalBlocker blockerFastThreshold(mThreshold);
  const QSignalBlocker blockerDetectorType(mDetectorType);

  mThreshold->setValue(10);
  mNonmaxSuppression->setChecked(true);
  mDetectorType->setCurrentText("OAST_9_16");
}

void AgastWidgetImp::initUI()
{
  this->setWindowTitle("AGAST");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("AGAST Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Threshold:")), 0, 0);
  mThreshold->setRange(0, 100);
  propertiesLayout->addWidget(mThreshold, 0, 1);

  mNonmaxSuppression->setText(tr("Nonmax Suppression"));
  propertiesLayout->addWidget(mNonmaxSuppression, 1, 0);

  propertiesLayout->addWidget(new QLabel(tr("Detector Type:")), 2, 0);
  mDetectorType->addItem("AGAST_5_8");
  mDetectorType->addItem("AGAST_7_12d");
  mDetectorType->addItem("AGAST_7_12s");
  mDetectorType->addItem("OAST_9_16");
  propertiesLayout->addWidget(mDetectorType, 2, 1);

  reset(); /// set default values

  update();
}

void AgastWidgetImp::initSignalAndSlots()
{
  connect(mThreshold,          SIGNAL(valueChanged(int)),            this, SIGNAL(thresholdChange(int)));
  connect(mNonmaxSuppression,  SIGNAL(clicked(bool)),                this, SIGNAL(nonmaxSuppressionChange(bool)));
  connect(mDetectorType,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(detectorTypeChange(QString)));
}

} // namespace photomatch

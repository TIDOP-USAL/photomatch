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


#include "AcebsfWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

AcebsfWidgetImp::AcebsfWidgetImp(QWidget *parent)
  : AcebsfWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this)),
    mGroupBoxBlocksize(new QGroupBox(this)),
    mLabelBlockSizeX(new QLabel(this)),
    mBlockSizeX(new QSpinBox(this)),
    mLabelBlockSizeY(new QLabel(this)),
    mBlockSizeY(new QSpinBox(this)),
    mLabelL(new QLabel(this)),
    mL(new QDoubleSpinBox(this)),
    mLabelK1(new QLabel(this)),
    mK1(new QDoubleSpinBox(this)),
    mLabelK2(new QLabel(this)),
    mK2(new QDoubleSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

AcebsfWidgetImp::~AcebsfWidgetImp()
{

}

void AcebsfWidgetImp::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void AcebsfWidgetImp::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize AcebsfWidgetImp::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

double AcebsfWidgetImp::l() const
{
  return mL->value();
}

double AcebsfWidgetImp::k1() const
{
  return mK1->value();
}

double AcebsfWidgetImp::k2() const
{
  return mK2->value();
}

void AcebsfWidgetImp::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());
}

void AcebsfWidgetImp::setL(double l)
{
  const QSignalBlocker blockerL(mL);
  mL->setValue(l);
}

void AcebsfWidgetImp::setK1(double k1)
{
  const QSignalBlocker blockerK1(mK1);
  mK1->setValue(k1);
}

void AcebsfWidgetImp::setK2(double k2)
{
  const QSignalBlocker blockerK2(mK2);
  mK2->setValue(k2);
}

void AcebsfWidgetImp::update()
{
}

void AcebsfWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("AcebsfWidgetImp", "ACEBSF Parameters", nullptr));
  mLabelDescription->setText(QApplication::translate("AcebsfWidgetImp", "Adaptive Contrast Enhancement Based on modified Sigmoid Function", nullptr));
  mGroupBoxBlocksize->setTitle(QApplication::translate("AcebsfWidgetImp", "Block Size", nullptr));
  mLabelBlockSizeX->setText(QApplication::translate("AcebsfWidgetImp", "Width:", nullptr));
  mLabelBlockSizeY->setText(QApplication::translate("AcebsfWidgetImp", "Height:", nullptr));
  mLabelL->setText(QApplication::translate("AcebsfWidgetImp", "L:", nullptr));
  mLabelK1->setText(QApplication::translate("AcebsfWidgetImp", "K1:", nullptr));
  mLabelK2->setText(QApplication::translate("AcebsfWidgetImp", "K2:", nullptr));

//#ifndef QT_NO_WHATSTHIS
//  mK1->setWhatsThis(tr("<html><head/><body><p><strong>K1</strong> controls the&nbsp;actual contrast of input image. If the value of <strong>K1</strong> is&nbsp;selected <strong>5</strong> then its effect on the input image is little&nbsp;change in the contrast, if the value of <strong>K1</strong> is selected <strong>1&nbsp;</strong>then its reduces contrast to about 20% of original and if&nbsp;the value of <strong>K1</strong> is selected <strong>10</strong> then its increase contrast&nbsp;about to 2.5 times the input image. Therefore a&nbsp;reasonable range of values of K1 is to be selected in the&nbsp;experiments. For effective contrast enhancement of&nbsp;input images <strong>the value of K1 should be lies between 10&nbsp;to 25</strong>.</p></body></html>"));
//  mK2->setWhatsThis(tr("<html><head/><body><p><p><strong>K2</strong>&nbsp;represents the&nbsp;normalized gray value about which contrast is&nbsp;increased or decreased. The initial value of <strong>K2</strong> is&nbsp;selected 0.5 (i.e., the midpoint of the gray scale) but&nbsp;different images may require different points of the&nbsp;gray scale to be enhanced. Therefore a reasonable&nbsp;range of values of K2 is to be selected in the&nbsp;experiments. For effective contrast enhancement of&nbsp;input images the value of K2 should be lies between 0&nbsp;to 1. <strong>The typical value of K2 is 0.5</strong>.</p></p></body></html>"));
//  mL->setWhatsThis(tr("<html><head/><body><p><p>Use to district the range of histogram. Range between 0 and 1.</p></p></body></html>"));
//  mBlockSizeX->setWhatsThis(tr("<html><head/><body><p><p>Block size X.</p></p></body></html>"));
//  mBlockSizeY->setWhatsThis(tr("<html><head/><body><p><p>Block size Y.</p></p></body></html>"));
//#endif // QT_NO_WHATSTHIS
}

void AcebsfWidgetImp::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);
  const QSignalBlocker blockerL(mL);
  const QSignalBlocker blockerK1(mK1);
  const QSignalBlocker blockerK2(mK2);

  mBlockSizeX->setValue(8);
  mBlockSizeY->setValue(8);
  mL->setValue(0.03);
  mK1->setValue(10.);
  mK2->setValue(0.5);
}

void AcebsfWidgetImp::initUI()
{
  this->setWindowTitle("ACEBSF");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  mLabelDescription->setWordWrap(true);
  QFont font;
  font.setBold(true);
  mLabelDescription->setFont(font);
  propertiesLayout->addWidget(mLabelDescription, 0, 0);

  propertiesLayout->addWidget(mGroupBoxBlocksize, 1, 0, 1, 2);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  mGroupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(mLabelBlockSizeX, 0, 0);
  mBlockSizeX->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1);

  propertiesLayoutBlocksize->addWidget(mLabelBlockSizeY, 1, 0);
  mBlockSizeY->setRange(0, 100);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1);

  propertiesLayout->addWidget(mLabelL, 2, 0);
  mL->setRange(0, 1);
  mL->setSingleStep(0.01);
  propertiesLayout->addWidget(mL, 2, 1);

  propertiesLayout->addWidget(mLabelK1, 3, 0);
  mK1->setRange(1, 100);
  propertiesLayout->addWidget(mK1, 3, 1);

  propertiesLayout->addWidget(mLabelK2, 4, 0);
  mK2->setRange(0, 1);
  mK2->setSingleStep(0.01);
  propertiesLayout->addWidget(mK2, 4, 1);

  this->retranslate();
  this->reset(); // Set default values
  this->update();
}

void AcebsfWidgetImp::initSignalAndSlots()
{
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));
  connect(mL,             SIGNAL(valueChanged(double)),     this, SIGNAL(lChange(double)));
  connect(mK1,            SIGNAL(valueChanged(double)),     this, SIGNAL(k1Change(double)));
  connect(mK2,            SIGNAL(valueChanged(double)),     this, SIGNAL(k2Change(double)));
}

///TODO: subir a la interfaz comun
void AcebsfWidgetImp::changeEvent(QEvent *event)
{
  QWidget::changeEvent(event);
  switch (event->type()) {
    case QEvent::LanguageChange:
      this->retranslate();
      break;
    default:
      break;
  }
}

} // namespace photomatch




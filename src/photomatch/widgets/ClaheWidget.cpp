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


#include "ClaheWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>
#include <QApplication>

namespace photomatch
{

ClaheWidgetImp::ClaheWidgetImp(QWidget *parent)
  : ClaheWidget(parent),
    mGroupBox(new QGroupBox(this)),
    mLabelDescription(new QLabel(this)),
    mLabelClipLimit(new QLabel(this)),
    mClipLimit(new QDoubleSpinBox(this)),
    mGroupBoxBlockSize(new QGroupBox(mGroupBox)),
    mLabelTilesGridX(new QLabel(this)),
    mTilesGridX(new QSpinBox(this)),
    mLabelTilesGridY(new QLabel(this)),
    mTilesGridY(new QSpinBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

ClaheWidgetImp::~ClaheWidgetImp()
{

}

void ClaheWidgetImp::initUI()
{
  this->setWindowTitle("CLAHE");
  this->setObjectName("ClaheWidget");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout();
  mGroupBox->setLayout(propertiesLayout);

  mLabelDescription->setWordWrap(true);
  QFont font;
  font.setBold(true);
  font.setWeight(75);
  mLabelDescription->setFont(font);
  mLabelDescription->setWordWrap(true);
  propertiesLayout->addWidget(mLabelDescription, 0, 0, 1, 2);

  propertiesLayout->addWidget(mLabelClipLimit, 1, 0, 1, 1);
  mClipLimit->setRange(0., 100.);
  propertiesLayout->addWidget(mClipLimit, 1, 1, 1, 1);

  QGridLayout *gridLayoutTiles = new QGridLayout(mGroupBoxBlockSize);
  gridLayoutTiles->setSpacing(6);
  gridLayoutTiles->setContentsMargins(11, 11, 11, 11);

  gridLayoutTiles->addWidget(mLabelTilesGridX, 0, 0, 1, 1);
  mTilesGridX->setRange(0, 100);
  gridLayoutTiles->addWidget(mTilesGridX, 0, 1, 1, 1);

  gridLayoutTiles->addWidget(mLabelTilesGridY, 1, 0, 1, 1);
  mTilesGridY->setRange(0, 100);
  gridLayoutTiles->addWidget(mTilesGridY, 1, 1, 1, 1);

  propertiesLayout->addWidget(mGroupBoxBlockSize, 2, 0, 1, 2);

  this->retranslate();
  this->reset();  /// set default values
  this->update();
}

void ClaheWidgetImp::initSignalAndSlots()
{
  connect(mClipLimit,   QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, &ClaheWidget::clipLimitChange);
  connect(mTilesGridX,  QOverload<int>::of(&QSpinBox::valueChanged),          this, &ClaheWidgetImp::onTilesGridXChange);
  connect(mTilesGridY,  QOverload<int>::of(&QSpinBox::valueChanged),          this, &ClaheWidgetImp::onTilesGridYChange);
}

void ClaheWidgetImp::reset()
{
  const QSignalBlocker blockerClipLimit(mClipLimit);
  const QSignalBlocker blockerTilesGridX(mTilesGridX);
  const QSignalBlocker blockerTilesGridY(mTilesGridY);

  mClipLimit->setValue(40.0);
  mTilesGridX->setValue(8);
  mTilesGridY->setValue(8);
}

void ClaheWidgetImp::update()
{
}

void ClaheWidgetImp::retranslate()
{
  mGroupBox->setTitle(QApplication::translate("ClaheWidget", "CLAHE Parameters"));
  mLabelDescription->setText(QApplication::translate("ClaheWidget", "Contrast Limited Adaptive Histogram Equalization", nullptr));
  mLabelClipLimit->setText(QApplication::translate("ClaheWidget", "Clip Limit:"));
  mGroupBoxBlockSize->setTitle(QApplication::translate("ClaheWidget", "Block Size"));
  mLabelTilesGridX->setText(QApplication::translate("ClaheWidget", "Width:"));
  mLabelTilesGridY->setText(QApplication::translate("ClaheWidget", "Height:"));
}

void ClaheWidgetImp::onTilesGridXChange(int gx)
{
  emit tileGridSizeChange(QSize(gx, mTilesGridY->value()));
}

void ClaheWidgetImp::onTilesGridYChange(int gy)
{
  emit tileGridSizeChange(QSize(mTilesGridX->value(), gy));
}

double ClaheWidgetImp::clipLimit() const
{
  return mClipLimit->value();
}

QSize ClaheWidgetImp::tileGridSize() const
{
  return QSize(mTilesGridX->value(), mTilesGridY->value());
}

void ClaheWidgetImp::setClipLimit(double clipLimit)
{
  const QSignalBlocker blockerClipLimit(mClipLimit);
  mClipLimit->setValue(clipLimit);
}

void ClaheWidgetImp::setTilesGridSize(const QSize &tileGridSize)
{
  const QSignalBlocker blockerTilesGridX(mTilesGridX);
  const QSignalBlocker blockerTilesGridY(mTilesGridY);
  mTilesGridX->setValue(tileGridSize.width());
  mTilesGridY->setValue(tileGridSize.height());
}

} // namespace photomatch



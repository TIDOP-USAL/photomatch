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


#include "PoheWidget.h"

#include <QSpinBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace photomatch
{

PoheWidgetImp::PoheWidgetImp(QWidget *parent)
  : PoheWidget(parent),
    mBlockSizeX(new QSpinBox(this)),
    mBlockSizeY(new QSpinBox(this))
{
  init();

  retranslate();

  /// Signals and slots
  connect(mBlockSizeX,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeXChange(int)));
  connect(mBlockSizeY,    SIGNAL(valueChanged(int)),        this, SLOT(onBlockSizeYChange(int)));

}

PoheWidgetImp::~PoheWidgetImp()
{

}

void PoheWidgetImp::onBlockSizeXChange(int blockSizeX)
{
  emit blockSizeChange(QSize(blockSizeX, mBlockSizeY->value()));
}

void PoheWidgetImp::onBlockSizeYChange(int blockSizeY)
{
  emit blockSizeChange(QSize(mBlockSizeX->value(), blockSizeY));
}

QSize PoheWidgetImp::blockSize() const
{
  return QSize(mBlockSizeX->value(), mBlockSizeY->value());
}

void PoheWidgetImp::setBlockSize(const QSize &blockSize)
{
  const QSignalBlocker blockerTilesGridX(mBlockSizeX);
  const QSignalBlocker blockerTilesGridY(mBlockSizeY);
  mBlockSizeX->setValue(blockSize.width());
  mBlockSizeY->setValue(blockSize.height());

}

void PoheWidgetImp::update()
{
}

void PoheWidgetImp::retranslate()
{
#ifndef QT_NO_WHATSTHIS
  mBlockSizeX->setWhatsThis(tr("<html><head/><body><p><p>Block size X.</p></p></body></html>"));
  mBlockSizeY->setWhatsThis(tr("<html><head/><body><p><p>Block size Y.</p></p></body></html>"));
#endif // QT_NO_WHATSTHIS
}

void PoheWidgetImp::reset()
{
  const QSignalBlocker blockerBlockSizeX(mBlockSizeX);
  const QSignalBlocker blockerBlockSizeY(mBlockSizeY);

  mBlockSizeX->setValue(127);
  mBlockSizeY->setValue(127);
}

void PoheWidgetImp::init()
{
  this->setWindowTitle("POHE");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("POHE Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("Parametric-Oriented Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);

  QGroupBox *groupBoxBlocksize = new QGroupBox(tr("Block Size"), this);
  propertiesLayout->addWidget(groupBoxBlocksize, 1, 0);
  QGridLayout *propertiesLayoutBlocksize = new QGridLayout();
  groupBoxBlocksize->setLayout(propertiesLayoutBlocksize);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Width:")), 0, 0);
  mBlockSizeX->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeX, 0, 1);

  propertiesLayoutBlocksize->addWidget(new QLabel(tr("Height:")), 1, 0);
  mBlockSizeY->setRange(0, 1000);
  propertiesLayoutBlocksize->addWidget(mBlockSizeY, 1, 1);


  reset(); /// set default values

  update();
}

} // namespace photomatch

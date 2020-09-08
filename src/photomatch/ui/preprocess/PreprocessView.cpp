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


#include "PreprocessView.h"

#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QApplication>

namespace photomatch
{

PreprocessViewImp::PreprocessViewImp(QWidget *parent)
  : PreprocessView(parent),
    mButtonBox(new QDialogButtonBox(this))
{
  this->initUI();
  this->initSignalAndSlots();
}

PreprocessViewImp::~PreprocessViewImp()
{

}

void PreprocessViewImp::initUI()
{
  this->setObjectName(QStringLiteral("PreprocessView"));
  //this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(350, 450);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mCheckBoxFullImage = new QCheckBox(this);
  mCheckBoxFullImage->setChecked(false);
  gridLayout->addWidget(mCheckBoxFullImage, 0, 0, 1, 1);

  mLabelMaxImageSize = new QLabel(this);
  gridLayout->addWidget(mLabelMaxImageSize, 1, 0, 1, 1);
  mSpinBoxMaxImageSize = new QSpinBox(this);
  mSpinBoxMaxImageSize->setRange(100, 100000);
  mSpinBoxMaxImageSize->setValue(2000);
  gridLayout->addWidget(mSpinBoxMaxImageSize, 1, 1, 1, 1);

  mLabelPreprocess = new QLabel(this);
  gridLayout->addWidget(mLabelPreprocess, 2, 0, 1, 1);
  mComboBoxPreprocess = new QComboBox(this);
  gridLayout->addWidget(mComboBoxPreprocess, 2, 1, 1, 1);

  QWidget *widgetPreprocess = new QWidget();
  mGridLayoutPreprocess = new QGridLayout(widgetPreprocess);
  mGridLayoutPreprocess->setContentsMargins(0, 0, 0, 0);
  gridLayout->addWidget(widgetPreprocess, 3, 0, 1, 2);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 4, 0, 1, 2);

  this->retranslate();
  this->update();
}

void PreprocessViewImp::initSignalAndSlots()
{
  connect(mComboBoxPreprocess,  &QComboBox::currentTextChanged, this, &PreprocessView::preprocessChange);
  connect(mCheckBoxFullImage,   &QAbstractButton::clicked,      this, &PreprocessViewImp::onCheckBoxFullImageChange);

  connect(mButtonBox,                                    &QDialogButtonBox::rejected, this, &QDialog::reject);
  connect(mButtonBox->button(QDialogButtonBox::Apply),   &QAbstractButton::clicked,   this, &ProcessView::run);
  connect(mButtonBox->button(QDialogButtonBox::Help),    &QAbstractButton::clicked,   this, &PhotoMatchDialogView::help);
}

void PreprocessViewImp::clear()
{
  mCurrentPreprocess.clear();
}

void PreprocessViewImp::update()
{

}

void PreprocessViewImp::retranslate()
{
  this->setWindowTitle(QApplication::translate("PreprocessView", "Preprocess"));
  mCheckBoxFullImage->setText(QApplication::translate("PreprocessView", "Full Image Size"));
  mLabelPreprocess->setText(QApplication::translate("PreprocessView", "Preprocess:"));
  mLabelMaxImageSize->setText(QApplication::translate("PreprocessView", "Max Image Size:"));
  mButtonBox->button(QDialogButtonBox::Cancel)->setText(QApplication::translate("PreprocessView", "Cancel"));
  mButtonBox->button(QDialogButtonBox::Apply)->setText(QApplication::translate("PreprocessView", "Run"));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("PreprocessView", "Help"));
}

void PreprocessViewImp::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Preprocess ").append(name));
}

void PreprocessViewImp::addPreprocess(QWidget *preprocess)
{
  mComboBoxPreprocess->addItem(preprocess->windowTitle());
  mGridLayoutPreprocess->addWidget(preprocess, 1, 0, 1, 2);
  preprocess->setVisible(false);
}

QString PreprocessViewImp::currentPreprocess() const
{
  return mCurrentPreprocess;
}

void PreprocessViewImp::setCurrentPreprocess(const QString &preprocess)
{
  mCurrentPreprocess = preprocess;

  const QSignalBlocker blocker(mComboBoxPreprocess);
  mComboBoxPreprocess->setCurrentText(preprocess);

  for (int idx = 0; idx < mGridLayoutPreprocess->count(); idx++){
    QLayoutItem * const item = mGridLayoutPreprocess->itemAt(idx);
    if(dynamic_cast<QWidgetItem *>(item)){
      if (item->widget()->windowTitle().compare(preprocess) == 0)
        item->widget()->setVisible(true);
      else
        item->widget()->setVisible(false);
    }
  }
}

int PreprocessViewImp::maxImageSize() const
{
  return mSpinBoxMaxImageSize->value();
}

void PreprocessViewImp::setMaxImageSize(int imageSize)
{
  mSpinBoxMaxImageSize->setValue(imageSize);
}

void PreprocessViewImp::setFullImageSize(bool fullImageSize)
{
  mCheckBoxFullImage->setChecked(fullImageSize);
}

bool PreprocessViewImp::fullImageSize() const
{
  return mCheckBoxFullImage->isChecked();
}

void PreprocessViewImp::onCheckBoxFullImageChange()
{
  mSpinBoxMaxImageSize->setEnabled(!mCheckBoxFullImage->isChecked());
}

} // namespace photomatch



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


#include "DescriptorMatcherView.h"

#include "photomatch/widgets/DescriptorMatcherWidget.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QStandardItemModel>

namespace photomatch
{

DescriptorMatcherViewImp::DescriptorMatcherViewImp(QWidget *parent)
  : DescriptorMatcherView(parent)
{
  this->initUI();
  this->initSignalAndSlots();
}

DescriptorMatcherViewImp::~DescriptorMatcherViewImp()
{
  if (mDescriptorMatcherWidget){
    delete mDescriptorMatcherWidget;
    mDescriptorMatcherWidget = nullptr;
  }
}

void DescriptorMatcherViewImp::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Descriptor Matcher ").append(name));
}

QString DescriptorMatcherViewImp::matchingMethod() const
{
  return mDescriptorMatcherWidget->matchingMethod();
}

QString DescriptorMatcherViewImp::matchingStrategy() const
{
  return mDescriptorMatcherWidget->matchingStrategy();
}

QString DescriptorMatcherViewImp::normType() const
{
  return mDescriptorMatcherWidget->normType();
}

double DescriptorMatcherViewImp::ratio() const
{
  return mDescriptorMatcherWidget->ratio();
}

QString DescriptorMatcherViewImp::geometricTest() const
{
  return mDescriptorMatcherWidget->geometricTest();
}

QString DescriptorMatcherViewImp::homographyComputeMethod() const
{
  return mDescriptorMatcherWidget->homographyComputeMethod();
}

QString DescriptorMatcherViewImp::fundamentalComputeMethod() const
{
  return mDescriptorMatcherWidget->fundamentalComputeMethod();
}

QString DescriptorMatcherViewImp::essentialComputeMethod() const
{
  return mDescriptorMatcherWidget->essentialComputeMethod();
}

double DescriptorMatcherViewImp::distance() const
{
  return mDescriptorMatcherWidget->distance();
}

double DescriptorMatcherViewImp::confidence() const
{
  return mDescriptorMatcherWidget->confidence();
}

int DescriptorMatcherViewImp::maxIters() const
{
  return mDescriptorMatcherWidget->maxIters();
}

bool DescriptorMatcherViewImp::crossMatching() const
{
  return mDescriptorMatcherWidget->crossMatching();
}

bool DescriptorMatcherViewImp::gmsRotation() const
{
  return mDescriptorMatcherWidget->gmsRotation();
}

bool DescriptorMatcherViewImp::gmsScale() const
{
  return mDescriptorMatcherWidget->gmsScale();
}

double DescriptorMatcherViewImp::gmsThreshold() const
{
  return mDescriptorMatcherWidget->gmsThreshold();
}

void DescriptorMatcherViewImp::setMatchingMethod(const QString &matchingMethod)
{
  mDescriptorMatcherWidget->setMatchingMethod(matchingMethod);
}

void DescriptorMatcherViewImp::setMatchingStrategy(const QString &matchingStrategy)
{
  mDescriptorMatcherWidget->setMatchingStrategy(matchingStrategy);
}

void DescriptorMatcherViewImp::setNormType(const QString &normType)
{
  mDescriptorMatcherWidget->setNormType(normType);
}

void DescriptorMatcherViewImp::setRatio(double ratio)
{
  mDescriptorMatcherWidget->setRatio(ratio);
}

void DescriptorMatcherViewImp::setGeometricTest(const QString &geometricTest)
{
  mDescriptorMatcherWidget->setGeometricTest(geometricTest);
}

void DescriptorMatcherViewImp::setHomographyComputeMethod(const QString &computeMethod)
{
  mDescriptorMatcherWidget->setHomographyComputeMethod(computeMethod);
}

void DescriptorMatcherViewImp::setFundamentalComputeMethod(const QString &computeMethod)
{
  mDescriptorMatcherWidget->setFundamentalComputeMethod(computeMethod);
}

void DescriptorMatcherViewImp::setEssentialComputeMethod(const QString &computeMethod)
{
  mDescriptorMatcherWidget->setEssentialComputeMethod(computeMethod);
}

void DescriptorMatcherViewImp::setDistance(double distance)
{
  mDescriptorMatcherWidget->setDistance(distance);
}

void DescriptorMatcherViewImp::setConfidence(double confidence)
{
  mDescriptorMatcherWidget->setConfidence(confidence);
}

void DescriptorMatcherViewImp::setMaxIters(int maxIter)
{
  mDescriptorMatcherWidget->setMaxIters(maxIter);
}

void DescriptorMatcherViewImp::setCrossMatching(bool crossMatching)
{
  mDescriptorMatcherWidget->setCrossMatching(crossMatching);
}

void DescriptorMatcherViewImp::disableBruteForceNorm(const QString &norm)
{
  mDescriptorMatcherWidget->disableBruteForceNorm(norm);
}

void DescriptorMatcherViewImp::enableBruteForceNorm(const QString &norm)
{
  mDescriptorMatcherWidget->enableBruteForceNorm(norm);
}

void DescriptorMatcherViewImp::setGmsRotation(bool active)
{
  mDescriptorMatcherWidget->setGmsRotation(active);
}

void DescriptorMatcherViewImp::setGmsScale(bool active)
{
  mDescriptorMatcherWidget->setGmsScale(active);
}

void DescriptorMatcherViewImp::setGmsThreshold(double threshold)
{
  mDescriptorMatcherWidget->setGmsThreshold(threshold);
}

void DescriptorMatcherViewImp::initUI()
{
  this->setWindowTitle(tr("Descriptor Matcher"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(350, 400);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mDescriptorMatcherWidget = new DescriptorMatcherWidgetImp(this);
  gridLayout->addWidget(mDescriptorMatcherWidget, 0, 0, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Apply |
                                 QDialogButtonBox::Cancel |
                                 QDialogButtonBox::Help);

  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Apply)->setText("Run");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  gridLayout->addWidget(mButtonBox, 1, 0, 1, 2);


  update();
}

void DescriptorMatcherViewImp::initSignalAndSlots()
{
  connect(mButtonBox,                                    SIGNAL(rejected()),      this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Apply),   SIGNAL(clicked(bool)),   this, SIGNAL(run()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)),   this, SIGNAL(help()));

}

void DescriptorMatcherViewImp::clear()
{
  mDescriptorMatcherWidget->reset();
}

void DescriptorMatcherViewImp::update()
{

}

void DescriptorMatcherViewImp::retranslate()
{

}

} // namespace photomatch

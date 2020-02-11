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

DescriptorMatcherView::DescriptorMatcherView(QWidget *parent)
  : IDescriptorMatcherView(parent)
{
  init();

  connect(mButtonBox,                                    SIGNAL(rejected()),      this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Apply),   SIGNAL(clicked(bool)),   this, SIGNAL(run()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)),   this, SIGNAL(help()));

}

DescriptorMatcherView::~DescriptorMatcherView()
{
  if (mDescriptorMatcherWidget){
    delete mDescriptorMatcherWidget;
    mDescriptorMatcherWidget = nullptr;
  }
}

void DescriptorMatcherView::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Descriptor Matcher ").append(name));
}

QString DescriptorMatcherView::matchingMethod() const
{
  return mDescriptorMatcherWidget->matchingMethod();
}

QString DescriptorMatcherView::matchingStrategy() const
{
  return mDescriptorMatcherWidget->matchingStrategy();
}

QString DescriptorMatcherView::normType() const
{
  return mDescriptorMatcherWidget->normType();
}

double DescriptorMatcherView::ratio() const
{
  return mDescriptorMatcherWidget->ratio();
}

QString DescriptorMatcherView::geometricTest() const
{
  return mDescriptorMatcherWidget->geometricTest();
}

QString DescriptorMatcherView::homographyComputeMethod() const
{
  return mDescriptorMatcherWidget->homographyComputeMethod();
}

QString DescriptorMatcherView::fundamentalComputeMethod() const
{
  return mDescriptorMatcherWidget->fundamentalComputeMethod();
}

QString DescriptorMatcherView::essentialComputeMethod() const
{
  return mDescriptorMatcherWidget->essentialComputeMethod();
}

double DescriptorMatcherView::distance() const
{
  return mDescriptorMatcherWidget->distance();
}

double DescriptorMatcherView::confidence() const
{
  return mDescriptorMatcherWidget->confidence();
}

int DescriptorMatcherView::maxIters() const
{
  return mDescriptorMatcherWidget->maxIters();
}

bool DescriptorMatcherView::crossMatching() const
{
  return mDescriptorMatcherWidget->crossMatching();
}

bool DescriptorMatcherView::gmsRotation() const
{
  return mDescriptorMatcherWidget->gmsRotation();
}

bool DescriptorMatcherView::gmsScale() const
{
  return mDescriptorMatcherWidget->gmsScale();
}

double DescriptorMatcherView::gmsThreshold() const
{
  return mDescriptorMatcherWidget->gmsThreshold();
}

void DescriptorMatcherView::setMatchingMethod(const QString &matchingMethod)
{
  mDescriptorMatcherWidget->setMatchingMethod(matchingMethod);
}

void DescriptorMatcherView::setMatchingStrategy(const QString &matchingStrategy)
{
  mDescriptorMatcherWidget->setMatchingStrategy(matchingStrategy);
}

void DescriptorMatcherView::setNormType(const QString &normType)
{
  mDescriptorMatcherWidget->setNormType(normType);
}

void DescriptorMatcherView::setRatio(double ratio)
{
  mDescriptorMatcherWidget->setRatio(ratio);
}

void DescriptorMatcherView::setGeometricTest(const QString &geometricTest)
{
  mDescriptorMatcherWidget->setGeometricTest(geometricTest);
}

void DescriptorMatcherView::setHomographyComputeMethod(const QString &computeMethod)
{
  mDescriptorMatcherWidget->setHomographyComputeMethod(computeMethod);
}

void DescriptorMatcherView::setFundamentalComputeMethod(const QString &computeMethod)
{
  mDescriptorMatcherWidget->setFundamentalComputeMethod(computeMethod);
}

void DescriptorMatcherView::setEssentialComputeMethod(const QString &computeMethod)
{
  mDescriptorMatcherWidget->setEssentialComputeMethod(computeMethod);
}

void DescriptorMatcherView::setDistance(double distance)
{
  mDescriptorMatcherWidget->setDistance(distance);
}

void DescriptorMatcherView::setConfidence(double confidence)
{
  mDescriptorMatcherWidget->setConfidence(confidence);
}

void DescriptorMatcherView::setMaxIters(int maxIter)
{
  mDescriptorMatcherWidget->setMaxIters(maxIter);
}

void DescriptorMatcherView::setCrossMatching(bool crossMatching)
{
  mDescriptorMatcherWidget->setCrossMatching(crossMatching);
}

void DescriptorMatcherView::disableBruteForceNorm(const QString &norm)
{
  mDescriptorMatcherWidget->disableBruteForceNorm(norm);
}

void DescriptorMatcherView::enableBruteForceNorm(const QString &norm)
{
  mDescriptorMatcherWidget->enableBruteForceNorm(norm);
}

void DescriptorMatcherView::setGmsRotation(bool active)
{
  mDescriptorMatcherWidget->setGmsRotation(active);
}

void DescriptorMatcherView::setGmsScale(bool active)
{
  mDescriptorMatcherWidget->setGmsScale(active);
}

void DescriptorMatcherView::setGmsThreshold(double threshold)
{
  mDescriptorMatcherWidget->setGmsThreshold(threshold);
}

void DescriptorMatcherView::init()
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

void DescriptorMatcherView::clear()
{
  mDescriptorMatcherWidget->reset();
}

void DescriptorMatcherView::update()
{

}

void DescriptorMatcherView::retranslate()
{

}

} // namespace photomatch

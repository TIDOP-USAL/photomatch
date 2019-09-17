#include "DescriptorMatcherView.h"

#include "fme/widgets/DescriptorMatcherWidget.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QStandardItemModel>

namespace fme
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

QString DescriptorMatcherView::matchingMethod() const
{
  return mDescriptorMatcherWidget->matchingMethod();
}

QString DescriptorMatcherView::normType() const
{
  return mDescriptorMatcherWidget->normType();
}

double DescriptorMatcherView::ratio() const
{
  return mDescriptorMatcherWidget->ratio();
}

double DescriptorMatcherView::distance() const
{
  return mDescriptorMatcherWidget->distance();
}

double DescriptorMatcherView::confidence() const
{
  return mDescriptorMatcherWidget->confidence();
}

bool DescriptorMatcherView::crossMatching() const
{
  return mDescriptorMatcherWidget->crossMatching();
}

void DescriptorMatcherView::setMatchingMethod(const QString &matchingMethod)
{
  mDescriptorMatcherWidget->setMatchingMethod(matchingMethod);
}

void DescriptorMatcherView::setNormType(const QString &normType)
{
  mDescriptorMatcherWidget->setNormType(normType);
}

void DescriptorMatcherView::setRatio(double ratio)
{
  mDescriptorMatcherWidget->setRatio(ratio);
}

void DescriptorMatcherView::setDistance(double distance)
{
  mDescriptorMatcherWidget->setDistance(distance);
}

void DescriptorMatcherView::setConfidence(double confidence)
{
  mDescriptorMatcherWidget->setConfidence(confidence);
}

void DescriptorMatcherView::setCrossMatching(bool crossMatching)
{
  mDescriptorMatcherWidget->setCrossMatching(crossMatching);
}

void DescriptorMatcherView::init()
{
  this->setWindowTitle(tr("Descriptor Matcher"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(350, 400);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mDescriptorMatcherWidget = new DescriptorMatcherWidget(this);
  gridLayout->addWidget(mDescriptorMatcherWidget, 0, 0, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  //mButtonBox->button(QDialogButtonBox::Ok)->setText("Ok");
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

} // namespace fme

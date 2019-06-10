#include "RswheWidget.h"

#include <QSpinBox>
#include <QRadioButton>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

RswheWidget::RswheWidget(QWidget *parent)
  : IRswheWidget(parent),
    mHistogramCut(HistogramCut::by_mean),
    mHistogramDivisions(new QSpinBox(this)),
    mHistogramCutByMean(new QRadioButton(this)),
    mHistogramCutByMedian(new QRadioButton(this))
{
  init();

  /// Signals and slots
  connect(mHistogramDivisions,    SIGNAL(valueChanged(int)),        this, SIGNAL(histogramDivisionsChange(int)));
  connect(mHistogramCutByMean,    SIGNAL(clicked()),                this, SLOT(onHistogramCutByMean()));
  connect(mHistogramCutByMedian,  SIGNAL(clicked()),                this, SLOT(onHistogramCutByMedian()));

}

RswheWidget::~RswheWidget()
{

}

void RswheWidget::onHistogramCutByMean()
{
  emit histogramCutChange(HistogramCut::by_mean);
}

void RswheWidget::onHistogramCutByMedian()
{
  emit histogramCutChange(HistogramCut::by_median);
}

int RswheWidget::histogramDivisions() const
{
  return mHistogramDivisions->value();
}

IRswheWidget::HistogramCut RswheWidget::histogramCut() const
{
  return mHistogramCut;
}

void RswheWidget::setHistogramDivisions(int histogramDivisions)
{
  const QSignalBlocker blockerHistogramDivisions(mHistogramDivisions);
  mHistogramDivisions->setValue(histogramDivisions);
}

void RswheWidget::setHistogramCut(IRswheWidget::HistogramCut histogramCut)
{
  mHistogramCut = histogramCut;
  update();
}

void RswheWidget::update()
{
  const QSignalBlocker blockerHistogramCutByMean(mHistogramCutByMean);
  const QSignalBlocker blockerHistogramCutByMedian(mHistogramCutByMedian);
  if (mHistogramCut == HistogramCut::by_mean){
    mHistogramCutByMean->setChecked(true);
  } else {
    mHistogramCutByMedian->setChecked(true);
  }
}

void RswheWidget::reset()
{
  const QSignalBlocker blockerHistogramDivisions(mHistogramDivisions);

  mHistogramDivisions->setValue(2);
  mHistogramCut = HistogramCut::by_mean;
}

void RswheWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("RSWHE Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  groupBox->setLayout(propertiesLayout);

  QLabel *lbl = new QLabel(tr("Recursively Separated and Weighted Histogram Equalization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0);


  propertiesLayout->addWidget(mHistogramCutByMean, 0, 1);
  propertiesLayout->addWidget(mHistogramCutByMedian, 1, 1);

  propertiesLayout->addWidget(new QLabel(tr("Histogram Divisions:")), 2, 0);
  mHistogramDivisions->setRange(1, 256);
  propertiesLayout->addWidget(mHistogramDivisions, 2, 1);

  reset(); /// set default values

  update();
}


} // namespace fme



#include "DecolorWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

DecolorWidget::DecolorWidget(QWidget *parent)
  : IDecolorWidget(parent)
{
  init();
}

DecolorWidget::~DecolorWidget()
{

}

void DecolorWidget::update()
{
}

void DecolorWidget::reset()
{
}

void DecolorWidget::init()
{
  this->setWindowTitle("Decolorization");

  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *groupBox = new QGroupBox(tr("Decolorization Parameters"), this);
  layout->addWidget(groupBox);

  QGridLayout *propertiesLayout = new QGridLayout(groupBox);

  QLabel *lbl = new QLabel(tr("Contrast Preserving Decolorization"), this);
  lbl->setWordWrap(true);
  QFont font;
  font.setBold(true);
  lbl->setFont(font);
  propertiesLayout->addWidget(lbl, 0, 0, 1, 2);

  reset(); /// set default values

  update();
}

} // namespace fme




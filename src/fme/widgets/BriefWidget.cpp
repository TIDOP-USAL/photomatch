#include "BriefWidget.h"

#include <QCheckBox>
#include <QComboBox>
#include <QGridLayout>
#include <QLabel>
#include <QGroupBox>

namespace fme
{

BriefWidget::BriefWidget(QWidget *parent)
  : IBriefWidget(parent),
    mBytes(new QComboBox(this)),
    mUseOrientation(new QCheckBox(this))
{
  init();

  /// Signals and slots
  connect(mBytes,             SIGNAL(currentTextChanged(QString)),   this, SIGNAL(bytesChange(QString)));
  connect(mUseOrientation,    SIGNAL(clicked(bool)),                 this, SIGNAL(useOrientationChange(bool)));
}

BriefWidget::~BriefWidget()
{

}

QString BriefWidget::bytes() const
{
  return mBytes->currentText();
}

bool BriefWidget::useOrientation() const
{
  return mUseOrientation->isChecked();
}

void BriefWidget::setBytes(const QString &bytes)
{
  const QSignalBlocker blockerBytes(mBytes);
  mBytes->setCurrentText(bytes);
}

void BriefWidget::setUseOrientation(bool useOrientation)
{
  mUseOrientation->setChecked(useOrientation);
}

void BriefWidget::update()
{
}

void BriefWidget::reset()
{
  const QSignalBlocker blockerBytes(mBytes);

  mBytes->setCurrentText("32");
  mUseOrientation->setChecked(false);
}

void BriefWidget::init()
{
  QGridLayout *layout = new QGridLayout();
  layout->setContentsMargins(0,0,0,0);
  this->setLayout(layout);

  QGroupBox *mGroupBox = new QGroupBox(tr("BRIEF Parameters"), this);
  layout->addWidget(mGroupBox);

  QGridLayout *propertiesLayout = new QGridLayout(this);
  mGroupBox->setLayout(propertiesLayout);

  propertiesLayout->addWidget(new QLabel(tr("Descriptor Bytes:")), 0, 0);
  mBytes->addItem("16");
  mBytes->addItem("32");
  mBytes->addItem("64");
  propertiesLayout->addWidget(mBytes, 0, 1);

  mUseOrientation->setText(tr("Use Keypoints Orientation"));
  propertiesLayout->addWidget(mUseOrientation, 1, 0);

  reset();

  update();
}

} // namespace fme



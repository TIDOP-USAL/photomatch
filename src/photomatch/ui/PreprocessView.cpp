#include "PreprocessView.h"

#include <QComboBox>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>

namespace photomatch
{

PreprocessView::PreprocessView(QWidget *parent)
  : IPreprocessView(parent),
    mButtonBox(new QDialogButtonBox(this))
{
  init();

  connect(mComboBoxPreprocess,  SIGNAL(currentTextChanged(QString)), this, SIGNAL(preprocessChange(QString)));
  connect(mCheckBoxFullImage,   SIGNAL(clicked(bool)),               this, SLOT(onCheckBoxFullImageChange()));

  connect(mButtonBox,                                    SIGNAL(rejected()),      this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Apply),   SIGNAL(clicked(bool)),   this, SIGNAL(run()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)),   this, SIGNAL(help()));
}

PreprocessView::~PreprocessView()
{

}

void PreprocessView::setSessionName(const QString &name)
{
  this->setWindowTitle(tr("Preprocess ").append(name));
}

void PreprocessView::addPreprocess(QWidget *preprocess)
{
  mComboBoxPreprocess->addItem(preprocess->windowTitle());
  mGridLayoutPreprocess->addWidget(preprocess, 1, 0, 1, 2);
  preprocess->setVisible(false);
}

QString PreprocessView::currentPreprocess() const
{
  return mCurrentPreprocess;
}

void PreprocessView::setCurrentPreprocess(const QString &preprocess)
{
  mCurrentPreprocess = preprocess;

  const QSignalBlocker blocker(mComboBoxPreprocess);
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

int PreprocessView::maxImageSize()
{
  return mSpinBoxMaxImageSize->value();
}

void PreprocessView::setMaxImageSize(int imageSize)
{
  mSpinBoxMaxImageSize->setValue(imageSize);
}

void PreprocessView::setFullImageSize(bool fullImageSize)
{
  mCheckBoxFullImage->setChecked(fullImageSize);
}

bool PreprocessView::fullImageSize()
{
  return mCheckBoxFullImage->isChecked();
}

void PreprocessView::onCheckBoxFullImageChange()
{
  mSpinBoxMaxImageSize->setEnabled(!mCheckBoxFullImage->isChecked());
}

void PreprocessView::init()
{
  this->setWindowTitle(tr("Preprocess"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(350, 450);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mCheckBoxFullImage = new QCheckBox(this);
  mCheckBoxFullImage->setText(tr("Full Image Size"));
  mCheckBoxFullImage->setChecked(false);
  gridLayout->addWidget(mCheckBoxFullImage, 0, 0, 1, 1);

  gridLayout->addWidget(new QLabel("Max Image Size:"), 1, 0, 1, 1);
  mSpinBoxMaxImageSize = new QSpinBox(this);
  mSpinBoxMaxImageSize->setRange(100, 100000);
  mSpinBoxMaxImageSize->setValue(2000);
  gridLayout->addWidget(mSpinBoxMaxImageSize, 1, 1, 1, 1);

  gridLayout->addWidget(new QLabel("Preprocess:"), 2, 0, 1, 1);
  mComboBoxPreprocess = new QComboBox(this);
  gridLayout->addWidget(mComboBoxPreprocess, 2, 1, 1, 1);

  QWidget *widgetPreprocess = new QWidget();
  mGridLayoutPreprocess = new QGridLayout(widgetPreprocess);
  mGridLayoutPreprocess->setContentsMargins(0, 0, 0, 0);
  gridLayout->addWidget(widgetPreprocess, 3, 0, 1, 2);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Help);

  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Apply)->setText("Run");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  gridLayout->addWidget(mButtonBox, 4, 0, 1, 2);


  update();
}

void PreprocessView::clear()
{
  mCurrentPreprocess.clear();
}

void PreprocessView::update()
{

}

} // namespace photomatch

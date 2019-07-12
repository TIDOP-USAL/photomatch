#include "PreprocessView.h"

#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>

namespace fme
{

PreprocessView::PreprocessView(QWidget *parent)
  : IPreprocessView(parent),
    mButtonBox(new QDialogButtonBox(this))
{
  init();

  connect(mComboBoxPreprocess, SIGNAL(currentTextChanged(QString)), this, SIGNAL(preprocessChange(QString)));

  connect(mButtonBox,                                    SIGNAL(rejected()),      this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Apply),   SIGNAL(clicked(bool)),   this, SIGNAL(run()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)),   this, SIGNAL(help()));
}

PreprocessView::~PreprocessView()
{

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
  for (int idx = 1; idx < mGridLayoutPreprocess->count(); idx++){
    QLayoutItem * const item = mGridLayoutPreprocess->itemAt(idx);
    if(dynamic_cast<QWidgetItem *>(item)){
      if (item->widget()->windowTitle().compare(preprocess) == 0)
        item->widget()->setVisible(true);
      else
        item->widget()->setVisible(false);
    }
  }
}

void PreprocessView::init()
{
  this->setWindowTitle(tr("Preprocess"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(750, 450);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  gridLayout->addWidget(new QLabel("Preprocess:"), 0, 0, 1, 1);
  mComboBoxPreprocess = new QComboBox(this);
  gridLayout->addWidget(mComboBoxPreprocess, 0, 1, 1, 1);

  QWidget *widgetPreprocess = new QWidget();
  mGridLayoutPreprocess = new QGridLayout(widgetPreprocess);
  mGridLayoutPreprocess->setContentsMargins(0, 0, 0, 0);
  gridLayout->addWidget(widgetPreprocess, 1, 0, 1, 2);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Apply | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  //mButtonBox->button(QDialogButtonBox::Ok)->setText("Ok");
  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Apply)->setText("Run");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  gridLayout->addWidget(mButtonBox, 2, 0, 1, 2);

  update();
}

void PreprocessView::clear()
{
  mCurrentPreprocess.clear();
}

void PreprocessView::update()
{

}

} // namespace fme

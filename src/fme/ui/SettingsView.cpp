#include "SettingsView.h"

#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QLabel>
#include <QGridLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QTabWidget>
#include <QScrollArea>



namespace fme
{

SettingsView::SettingsView(QWidget *parent)
  : ISettingsView(parent),
    mListWidget(new QListWidget(this)),
    mStackedWidget(new QStackedWidget(this)),
    mLanguages(new QComboBox(this)),
    mTabWidgetTools(nullptr),
    mListWidgetPreprocess(nullptr),
    mListWidgetFeatures(nullptr),
    mListWidgetMatching(nullptr),
    mButtonBox(new QDialogButtonBox(this)),
    bUnsaveChanges(false)
{
  init();

  connect(mListWidget, SIGNAL(currentRowChanged(int)), mStackedWidget, SLOT(setCurrentIndex(int)));

  connect(mLanguages,  SIGNAL(currentTextChanged(QString)),  this, SIGNAL(languageChange(QString)));

  connect(mListWidgetPreprocess, SIGNAL(currentTextChanged(QString)), this, SLOT(onPreprocessChange(QString)));
  connect(mListWidgetFeatures,   SIGNAL(currentTextChanged(QString)), this, SLOT(onFeatureDetectorDescriptorChange(QString)));

  connect(mButtonBox,                                    SIGNAL(accepted()),      this, SLOT(accept()));
  connect(mButtonBox,                                    SIGNAL(rejected()),      this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Apply),   SIGNAL(clicked(bool)),   this, SIGNAL(applyChanges()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)),   this, SIGNAL(help()));

}

SettingsView::~SettingsView()
{

}

void SettingsView::onPreprocessChange(const QString &method)
{
  for (int idx = 1; idx < mGridLayoutPreprocess->count(); idx++){
    QLayoutItem * const item = mGridLayoutPreprocess->itemAt(idx);
    if(dynamic_cast<QWidgetItem *>(item)){
      if (item->widget()->windowTitle().compare(method) == 0)
        item->widget()->setVisible(true);
      else
        item->widget()->setVisible(false);
    }
  }
}

void SettingsView::onFeatureDetectorDescriptorChange(const QString &method)
{
  for (int idx = 1; idx < mGridLayoutFeatures->count(); idx++){
    QLayoutItem * const item = mGridLayoutFeatures->itemAt(idx);
    if(dynamic_cast<QWidgetItem *>(item)){
      if (item->widget()->windowTitle().compare(method) == 0)
        item->widget()->setVisible(true);
      else
        item->widget()->setVisible(false);
    }
  }

}

void SettingsView::init()
{
  this->setWindowTitle(tr("Settings"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(750, 450);

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  mListWidget->setMaximumSize(QSize(250, 16777215));
  mListWidget->addItem(tr("General"));
  mListWidget->addItem(tr("Viewer"));
  mListWidget->addItem(tr("Tools"));
  layout->addWidget(mListWidget, 0, 0, 1, 1);

  layout->addWidget(mStackedWidget, 0, 1, 1, 3);

  /* General */
  QWidget *pageGeneral = new QWidget(this);
  QGridLayout *gridLayoutGeneral = new QGridLayout(pageGeneral);

  gridLayoutGeneral->addWidget(new QLabel(tr("Language")), 0, 0, 1, 1);

  gridLayoutGeneral->addWidget(mLanguages, 0, 1, 1, 1);

  QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

  gridLayoutGeneral->addItem(verticalSpacer, 1, 0, 1, 1);

  mStackedWidget->addWidget(pageGeneral);

  /* Viewer */
  QWidget *pageViewer = new QWidget(this);
  QGridLayout *gridLayoutViewer = new QGridLayout(pageViewer);

  mStackedWidget->addWidget(pageViewer);

  /* Tools */
  QWidget *pageTools = new QWidget();
  QGridLayout *gridLayoutTools = new QGridLayout(pageTools);
  gridLayoutTools->setContentsMargins(0, 0, 0, 0);

  mTabWidgetTools = new QTabWidget(pageTools);

  QWidget *tabPreprocess = new QWidget();
  QGridLayout *gridLayoutTabPreprocess = new QGridLayout(tabPreprocess);
  gridLayoutTabPreprocess->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollAreaPreprocess = new QScrollArea(tabPreprocess);
  scrollAreaPreprocess->setWidgetResizable(true);
  scrollAreaPreprocess->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetContents = new QWidget();
  scrollAreaWidgetContents->setGeometry(QRect(0, 0, 439, 358));
  mGridLayoutPreprocess = new QGridLayout(scrollAreaWidgetContents);
  mListWidgetPreprocess = new QListWidget(scrollAreaWidgetContents);
  mGridLayoutPreprocess->addWidget(mListWidgetPreprocess, 0, 0, 1, 1);
  scrollAreaPreprocess->setWidget(scrollAreaWidgetContents);
  gridLayoutTabPreprocess->addWidget(scrollAreaPreprocess, 0, 0, 1, 1);
  mTabWidgetTools->addTab(tabPreprocess, QString("Preprocess"));

  QWidget *tabFeatures = new QWidget();
  QGridLayout *gridLayoutFeatures = new QGridLayout(tabFeatures);
  gridLayoutFeatures->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollAreaFeatures = new QScrollArea(tabFeatures);
  scrollAreaFeatures->setWidgetResizable(true);
  scrollAreaFeatures->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetFeatures = new QWidget();
  scrollAreaWidgetFeatures->setGeometry(QRect(0, 0, 439, 358));
  mGridLayoutFeatures = new QGridLayout(scrollAreaWidgetFeatures);
  mListWidgetFeatures = new QListWidget(scrollAreaWidgetFeatures);
  mGridLayoutFeatures->addWidget(mListWidgetFeatures, 0, 0, 1, 1);
  scrollAreaFeatures->setWidget(scrollAreaWidgetFeatures);
  gridLayoutFeatures->addWidget(scrollAreaFeatures, 0, 0, 1, 1);
  mTabWidgetTools->addTab(tabFeatures, QString("Feature Detector / Extractor"));

  QWidget *tabMatching = new QWidget();
  QGridLayout *gridLayoutMatching = new QGridLayout(tabMatching);
  gridLayoutMatching->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollAreaMatching = new QScrollArea(tabMatching);
  scrollAreaMatching->setWidgetResizable(true);
  scrollAreaMatching->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetMatching = new QWidget();
  scrollAreaWidgetMatching->setGeometry(QRect(0, 0, 439, 358));
  QGridLayout *gridLayoutMatching2 = new QGridLayout(scrollAreaWidgetMatching);
  mListWidgetMatching = new QListWidget(scrollAreaWidgetMatching);
  gridLayoutMatching2->addWidget(mListWidgetMatching, 0, 0, 1, 1);
  scrollAreaMatching->setWidget(scrollAreaWidgetMatching);
  gridLayoutMatching->addWidget(scrollAreaMatching, 0, 0, 1, 1);
  mTabWidgetTools->addTab(tabMatching, QString("Matching"));

  gridLayoutTools->addWidget(mTabWidgetTools, 0, 0, 1, 1);
  mStackedWidget->addWidget(pageTools);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel |
                                 QDialogButtonBox::Apply | QDialogButtonBox::Help);
  mButtonBox->button(QDialogButtonBox::Ok)->setText("Ok");
  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Apply)->setText("Apply");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  layout->addWidget(mButtonBox, 1, 0, 1, 4);

  update();
}

void SettingsView::clear()
{
  mLanguages->clear();
}

void SettingsView::update()
{
  mButtonBox->button(QDialogButtonBox::Apply)->setEnabled(bUnsaveChanges);
}

void SettingsView::setLanguages(const QStringList &languages)
{
  const QSignalBlocker blocker(mLanguages);

  mLanguages->clear();
  mLanguages->insertItems(0, languages);
}

void SettingsView::setActiveLanguage(const QString &language)
{
  const QSignalBlocker blocker(mLanguages);
  mLanguages->setCurrentText(language);
}

void SettingsView::addPreprocess(QWidget *preprocess)
{
  mListWidgetPreprocess->addItem(preprocess->windowTitle());
  mGridLayoutPreprocess->addWidget(preprocess, 1, 0, 1, 1);
  preprocess->setVisible(false);
}

void SettingsView::addFeatureDetectorMethod(QWidget *detector)
{
  mListWidgetFeatures->addItem(detector->windowTitle());
  mGridLayoutFeatures->addWidget(detector, 1, 0, 1, 1);
  detector->setVisible(false);
}

void SettingsView::setUnsavedChanges(bool unsaveChanges)
{
  bUnsaveChanges = unsaveChanges;
  update();
}

} // namespace fme

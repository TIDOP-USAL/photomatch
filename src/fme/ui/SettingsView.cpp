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
#include <QSpacerItem>
#include <QSpinBox>
#include <QLineEdit>

namespace fme
{

SettingsView::SettingsView(QWidget *parent)
  : ISettingsView(parent),
    mListWidget(new QListWidget(this)),
    mStackedWidget(new QStackedWidget(this)),
    mLanguages(new QComboBox(this)),
    mHistoryMaxSize(new QSpinBox(this)),
    mTabWidgetTools(nullptr),
    mKeypointsFormat(new QComboBox(this)),
    mMatchesFormat(new QComboBox(this)),
    mListWidgetPreprocess(nullptr),
    mListWidgetFeatures(nullptr),
    //mListWidgetMatching(nullptr),
    mButtonBox(new QDialogButtonBox(this)),
    bUnsaveChanges(false)
{
  init();

  connect(mListWidget, SIGNAL(currentRowChanged(int)), mStackedWidget, SLOT(setCurrentIndex(int)));

  connect(mLanguages,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(languageChange(QString)));
  connect(mKeypointsFormat, SIGNAL(currentTextChanged(QString)),  this, SIGNAL(keypointsFormatChange(QString)));
  connect(mMatchesFormat,   SIGNAL(currentTextChanged(QString)),  this, SIGNAL(matchesFormatChange(QString)));

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
  mListWidget->addItem(tr("Image Viewer"));
  mListWidget->addItem(tr("Tools"));
  layout->addWidget(mListWidget, 0, 0, 1, 1);

  layout->addWidget(mStackedWidget, 0, 1, 1, 3);

  /* General */
  QWidget *pageGeneral = new QWidget(this);
  QGridLayout *gridLayoutGeneral = new QGridLayout(pageGeneral);

  gridLayoutGeneral->addWidget(new QLabel(tr("Language")), 0, 0, 1, 1);
  gridLayoutGeneral->addWidget(mLanguages, 0, 1, 1, 1);

  gridLayoutGeneral->addWidget(new QLabel(tr("History Max Size")), 1, 0, 1, 1);
  mHistoryMaxSize->setRange(0, 50);
  mHistoryMaxSize->setValue(10);
  gridLayoutGeneral->addWidget(mHistoryMaxSize, 1, 1, 1, 1);

  QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

  gridLayoutGeneral->addItem(verticalSpacer, 2, 0, 1, 1);

  mStackedWidget->addWidget(pageGeneral);

  /* Viewer */
  QWidget *pageImageViewer = new QWidget(this);
  QGridLayout *gridLayoutViewer = new QGridLayout(pageImageViewer);
  gridLayoutViewer->setContentsMargins(0, 0, 0, 0);

  QTabWidget *tabWidgetImageViewer = new QTabWidget(pageImageViewer);

  QWidget *tabImageViewerGeneral = new QWidget(this);
  QGridLayout *gridLayoutTabImageViewerGeneral = new QGridLayout(tabImageViewerGeneral);
  gridLayoutTabImageViewerGeneral->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollAreaImageViewerGeneral = new QScrollArea(tabImageViewerGeneral);
  scrollAreaImageViewerGeneral->setWidgetResizable(true);
  scrollAreaImageViewerGeneral->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetContentsImageViewerGeneral = new QWidget(this);
  QGridLayout *gridLayoutContentsImageViewerGeneral = new QGridLayout(scrollAreaWidgetContentsImageViewerGeneral);
  gridLayoutContentsImageViewerGeneral->addWidget(new QLabel(tr("Background Color:")), 0, 0, 1, 1);
  mLineEditImageViewerBGcolor = new QLineEdit(tabImageViewerGeneral);
  gridLayoutContentsImageViewerGeneral->addWidget(mLineEditImageViewerBGcolor, 0, 1, 1, 1);
  mPushButtonImageViewerBGcolor = new QPushButton(tr("..."), tabImageViewerGeneral);
  mPushButtonImageViewerBGcolor->setMaximumSize(QSize(23, 23));
  gridLayoutContentsImageViewerGeneral->addWidget(mPushButtonImageViewerBGcolor, 0, 2, 1, 1);

  scrollAreaImageViewerGeneral->setWidget(scrollAreaWidgetContentsImageViewerGeneral);
  gridLayoutTabImageViewerGeneral->addWidget(scrollAreaImageViewerGeneral);

  gridLayoutViewer->addWidget(tabWidgetImageViewer, 0, 0, 1, 1);
  tabWidgetImageViewer->addTab(tabImageViewerGeneral, QString(tr("General")));

  QWidget *tabImageViewerKeypoints = new QWidget(this);
  QGridLayout *gridLayoutTabImageViewerKeypoints = new QGridLayout(tabImageViewerKeypoints);
  gridLayoutTabImageViewerKeypoints->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollAreaImageViewerKeypoints = new QScrollArea(tabImageViewerKeypoints);
  scrollAreaImageViewerKeypoints->setWidgetResizable(true);
  scrollAreaImageViewerKeypoints->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetContentsImageViewerKeypoints = new QWidget(this);
  QGridLayout *gridLayoutContentsImageViewerKeypoints = new QGridLayout(scrollAreaWidgetContentsImageViewerKeypoints);
  gridLayoutContentsImageViewerKeypoints->addWidget(new QLabel(tr("Symbol Size:")), 0, 0, 1, 1);
  mSpinBoxKeypointSymbolSize = new QSpinBox(tabImageViewerKeypoints);
  gridLayoutContentsImageViewerKeypoints->addWidget(mSpinBoxKeypointSymbolSize, 0, 1, 1, 1);
  gridLayoutContentsImageViewerKeypoints->addWidget(new QLabel(tr("Symbol Color:")), 1, 0, 1, 1);
  mLineEditMatchesKeypointSimbolColor = new QLineEdit(tabImageViewerKeypoints);
  gridLayoutContentsImageViewerKeypoints->addWidget(mLineEditMatchesKeypointSimbolColor, 1, 1, 1, 1);
  mPushButtonKeypointSimbolColor = new QPushButton(tr("..."), tabImageViewerKeypoints);
  mPushButtonKeypointSimbolColor->setMaximumSize(QSize(23, 23));
  gridLayoutContentsImageViewerKeypoints->addWidget(mPushButtonKeypointSimbolColor, 1, 2, 1, 1);
  scrollAreaImageViewerKeypoints->setWidget(scrollAreaWidgetContentsImageViewerKeypoints);
  gridLayoutTabImageViewerKeypoints->addWidget(scrollAreaImageViewerKeypoints);

  gridLayoutViewer->addWidget(tabWidgetImageViewer, 0, 0, 1, 1);
  tabWidgetImageViewer->addTab(tabImageViewerKeypoints, QString(tr("Keypoints")));

  mStackedWidget->addWidget(pageImageViewer);

  /* Tools */
  QWidget *pageTools = new QWidget(this);
  QGridLayout *gridLayoutTools = new QGridLayout(pageTools);
  gridLayoutTools->setContentsMargins(0, 0, 0, 0);

  mTabWidgetTools = new QTabWidget(pageTools);

  QWidget *tabToolsGeneral = new QWidget(this);
  QGridLayout *gridLayoutTabToolsGeneral = new QGridLayout(tabToolsGeneral);
  gridLayoutTabToolsGeneral->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollAreaToolsGeneral = new QScrollArea(tabToolsGeneral);
  scrollAreaToolsGeneral->setWidgetResizable(true);
  scrollAreaToolsGeneral->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetContentsToolsGeneral = new QWidget(this);
  QGridLayout *gridLayoutContentsToolsGeneral = new QGridLayout(scrollAreaWidgetContentsToolsGeneral);
  gridLayoutContentsToolsGeneral->addWidget(new QLabel(tr("Keypoints Format")), 0, 0, 1, 1);
  mKeypointsFormat->addItem("Binary");
  mKeypointsFormat->addItem("XML");
  mKeypointsFormat->addItem("YML");
  gridLayoutContentsToolsGeneral->addWidget(mKeypointsFormat, 0, 1, 1, 1);
  gridLayoutContentsToolsGeneral->addWidget(new QLabel(tr("Matches Format")), 1, 0, 1, 1);
  mMatchesFormat->addItem("Binary");
  mMatchesFormat->addItem("XML");
  mMatchesFormat->addItem("YML");
  gridLayoutContentsToolsGeneral->addWidget(mMatchesFormat, 1, 1, 1, 1);
  gridLayoutContentsToolsGeneral->addItem(new QSpacerItem(1,1, QSizePolicy::Fixed, QSizePolicy::Expanding), 2, 1, 1, 2);
  scrollAreaToolsGeneral->setWidget(scrollAreaWidgetContentsToolsGeneral);
  gridLayoutTabToolsGeneral->addWidget(scrollAreaToolsGeneral, 0, 0, 1, 1);
  mTabWidgetTools->addTab(tabToolsGeneral, QString(tr("General")));

  QWidget *tabPreprocess = new QWidget(this);
  QGridLayout *gridLayoutTabPreprocess = new QGridLayout(tabPreprocess);
  gridLayoutTabPreprocess->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollAreaPreprocess = new QScrollArea(tabPreprocess);
  scrollAreaPreprocess->setWidgetResizable(true);
  scrollAreaPreprocess->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetContents = new QWidget(this);
  scrollAreaWidgetContents->setGeometry(QRect(0, 0, 439, 358));
  mGridLayoutPreprocess = new QGridLayout(scrollAreaWidgetContents);
  mListWidgetPreprocess = new QListWidget(scrollAreaWidgetContents);
  mGridLayoutPreprocess->addWidget(mListWidgetPreprocess, 0, 0, 1, 1);
  scrollAreaPreprocess->setWidget(scrollAreaWidgetContents);
  gridLayoutTabPreprocess->addWidget(scrollAreaPreprocess, 0, 0, 1, 1);
  mTabWidgetTools->addTab(tabPreprocess, QString(tr("Preprocess")));

  QWidget *tabFeatures = new QWidget(this);
  QGridLayout *gridLayoutFeatures = new QGridLayout(tabFeatures);
  gridLayoutFeatures->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollAreaFeatures = new QScrollArea(tabFeatures);
  scrollAreaFeatures->setWidgetResizable(true);
  scrollAreaFeatures->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetFeatures = new QWidget(this);
  scrollAreaWidgetFeatures->setGeometry(QRect(0, 0, 439, 358));
  mGridLayoutFeatures = new QGridLayout(scrollAreaWidgetFeatures);
  mListWidgetFeatures = new QListWidget(scrollAreaWidgetFeatures);
  mGridLayoutFeatures->addWidget(mListWidgetFeatures, 0, 0, 1, 1);
  scrollAreaFeatures->setWidget(scrollAreaWidgetFeatures);
  gridLayoutFeatures->addWidget(scrollAreaFeatures, 0, 0, 1, 1);
  mTabWidgetTools->addTab(tabFeatures, QString(tr("Feature Detector / Extractor")));

  QWidget *tabMatching = new QWidget(this);
  //QGridLayout *gridLayoutMatching = new QGridLayout(tabMatching);
  //gridLayoutMatching->setContentsMargins(0, 0, 0, 0);
  //QScrollArea *scrollAreaMatching = new QScrollArea(tabMatching);
  //scrollAreaMatching->setWidgetResizable(true);
  //scrollAreaMatching->setFrameShape(QFrame::Shape::NoFrame);
  //QWidget *scrollAreaWidgetMatching = new QWidget();
  //scrollAreaWidgetMatching->setGeometry(QRect(0, 0, 439, 358));
  mGridLayoutMatcher = new QGridLayout(tabMatching);
  //mListWidgetMatching = new QListWidget(scrollAreaWidgetMatching);
  //gridLayoutMatching2->addWidget(mListWidgetMatching, 0, 0, 1, 1);
  //scrollAreaMatching->setWidget(scrollAreaWidgetMatching);
  //gridLayoutMatching->addWidget(scrollAreaMatching, 0, 0, 1, 1);
  mTabWidgetTools->addTab(tabMatching, QString(tr("Matching")));

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
  const QSignalBlocker blocker1(mLanguages);
  mLanguages->clear();
}

void SettingsView::update()
{
  mButtonBox->button(QDialogButtonBox::Apply)->setEnabled(bUnsaveChanges);
}

void SettingsView::setPage(int page)
{
  mListWidget->setCurrentRow(page);
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

void SettingsView::setHistoryMaxSize(int size)
{
  mHistoryMaxSize->setValue(size);
}

void SettingsView::setKeypointsFormat(const QString &format)
{
  mKeypointsFormat->setCurrentText(format);
}

void SettingsView::setMatchesFormat(const QString &format)
{
  mMatchesFormat->setCurrentText(format);
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

void SettingsView::addDescriptorMatcher(QWidget *detector)
{
  mGridLayoutMatcher->addWidget(detector, 0, 0, 1, 1);
}

void SettingsView::setUnsavedChanges(bool unsaveChanges)
{
  bUnsaveChanges = unsaveChanges;
  update();
}

} // namespace fme

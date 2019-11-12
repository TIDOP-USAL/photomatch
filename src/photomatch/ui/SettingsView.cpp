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
#include <QColorDialog>
#include <QGroupBox>

namespace photomatch
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
    mButtonBox(new QDialogButtonBox(this)),
    bUnsaveChanges(false)
{
  init();

  connect(mListWidget, SIGNAL(currentRowChanged(int)), mStackedWidget, SLOT(setCurrentIndex(int)));

  connect(mLanguages,       SIGNAL(currentTextChanged(QString)),  this, SIGNAL(languageChange(QString)));
  connect(mHistoryMaxSize,  SIGNAL(valueChanged(int)),            this, SIGNAL(historyMaxSizeChange(int)));

  connect(mLineEditImageViewerBGcolor,    SIGNAL(textChanged(QString)), this, SIGNAL(imageViewerBGColorChange(QString)));
  connect(mPushButtonImageViewerBGcolor,  SIGNAL(clicked(bool)),        this, SLOT(onPushButtonImageViewerBGColorClicked()));

  connect(mKeypointsFormat, SIGNAL(currentTextChanged(QString)),  this, SIGNAL(keypointsFormatChange(QString)));
  connect(mMatchesFormat,   SIGNAL(currentTextChanged(QString)),  this, SIGNAL(matchesFormatChange(QString)));

  connect(mLineEditKeypointViewerBGColor,       SIGNAL(textChanged(QString)), this,  SIGNAL(keypointsViewerBGColorChange(QString)));
  connect(mPushButtonKeypointViewerBGColor,     SIGNAL(clicked(bool)),        this,  SLOT(onPushButtonKeypointViewerBGColorClicked()));
  connect(mSpinBoxKeypointViewerMarkerSize,     SIGNAL(valueChanged(int)),    this,  SIGNAL(keypointsViewerMarkerSizeChange(int)));
  connect(mSpinBoxKeypointViewerMarkerWidth,    SIGNAL(valueChanged(int)),    this,  SIGNAL(keypointsViewerMarkerWidthChange(int)));
  connect(mLineEditKeypointViewerMarkerColor,   SIGNAL(textChanged(QString)), this,  SIGNAL(keypointsViewerMarkerColorChange(QString)));
  connect(mPushButtonKeypointViewerMarkerColor, SIGNAL(clicked(bool)),        this,  SLOT(onPushButtonKeypointViewerMarkerColorClicked()));
  connect(mListWidgetKeypointsViewerMarkerType, SIGNAL(currentRowChanged(int)),       this, SIGNAL(keypointsViewerMarkerTypeChange(int)));
  connect(mListWidgetKeypointsViewerMarkerType, SIGNAL(currentTextChanged(QString)),  this, SLOT(update()));

  connect(mLineEditMatchesViewerBGColor,       SIGNAL(textChanged(QString)),   this, SIGNAL(matchesViewerBGColorChange(QString)));
  connect(mPushButtonMatchesViewerBGColor,     SIGNAL(clicked(bool)),          this, SLOT(onPushButtonMatchViewerBGColorClicked()));
  connect(mSpinBoxMatchesViewerMarkerSize,     SIGNAL(valueChanged(int)),      this, SIGNAL(matchesViewerMarkerSizeChange(int)));
  connect(mSpinBoxMatchesViewerLineWidth,      SIGNAL(valueChanged(int)),      this, SIGNAL(matchesViewerLineWidthChange(int)));
  connect(mSpinBoxMatchesViewerMarkerWidth,    SIGNAL(valueChanged(int)),      this, SIGNAL(matchesViewerMarkerWidthChange(int)));
  connect(mLineEditMatchesViewerMarkerColor,   SIGNAL(textChanged(QString)),   this, SIGNAL(matchesViewerMarkerColorChange(QString)));
  connect(mPushButtonMatchesViewerMarkerColor, SIGNAL(clicked(bool)),          this, SLOT(onPushButtonMatchViewerMarkerColorClicked()));
  connect(mLineEditMatchesViewerLineColor,     SIGNAL(textChanged(QString)),   this, SIGNAL(matchesViewerLineColorChange(QString)));
  connect(mPushButtonMatchesViewerLineColor,   SIGNAL(clicked(bool)),          this, SLOT(onPushButtonMatchViewerLineColorClicked()));
  connect(mListWidgetMatchesViewerMarkerType,  SIGNAL(currentRowChanged(int)), this, SIGNAL(matchesViewerMarkerTypeChange(int)));


  connect(mLineEditGroundTruthEditorBGColor,       SIGNAL(textChanged(QString)),   this, SIGNAL(groundTruthEditorBGColorChange(QString)));
  connect(mPushButtonGroundTruthEditorBGColor,     SIGNAL(clicked(bool)),          this, SLOT(onPushButtonGroundTruthEditorBGColorClicked()));
  connect(mSpinBoxGroundTruthEditorMarkerSize,     SIGNAL(valueChanged(int)),      this, SIGNAL(groundTruthEditorMarkerSizeChange(int)));
  connect(mSpinBoxGroundTruthEditorMarkerWidth,    SIGNAL(valueChanged(int)),      this, SIGNAL(groundTruthEditorMarkerWidthChange(int)));
  connect(mLineEditGroundTruthEditorMarkerColor,   SIGNAL(textChanged(QString)),   this, SIGNAL(groundTruthEditorMarkerColorChange(QString)));
  connect(mPushButtonGroundTruthEditorMarkerColor, SIGNAL(clicked(bool)),          this, SLOT(onPushButtonGroundTruthEditorMarkerColorClicked()));

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

void SettingsView::onPushButtonImageViewerBGColorClicked()
{
  QColor color = QColorDialog::getColor(QColor(mLineEditImageViewerBGcolor->text()), this, "Pick a color",  QColorDialog::DontUseNativeDialog);
  emit imageViewerBGColorChange(color.name());
}

void SettingsView::onPushButtonKeypointViewerBGColorClicked()
{
  QColor color = QColorDialog::getColor(QColor(mLineEditKeypointViewerBGColor->text()), this, "Pick a color",  QColorDialog::DontUseNativeDialog);
  mLineEditKeypointViewerBGColor->setText(color.name());
  //emit keypointsViewerBGColorChange(color.name());
}

void SettingsView::onPushButtonKeypointViewerMarkerColorClicked()
{
  QColor color = QColorDialog::getColor(QColor(mLineEditKeypointViewerMarkerColor->text()), this, "Pick a color",  QColorDialog::DontUseNativeDialog);
  mLineEditKeypointViewerMarkerColor->setText(color.name());
  //emit keypointsViewerMarkerColorChange(color.name());
}

void SettingsView::onPushButtonMatchViewerBGColorClicked()
{
  QColor color = QColorDialog::getColor(QColor(mLineEditMatchesViewerBGColor->text()), this, "Pick a color",  QColorDialog::DontUseNativeDialog);
  mLineEditMatchesViewerBGColor->setText(color.name());
  //emit matchesViewerBGColorChange(color.name());
}

void SettingsView::onPushButtonMatchViewerMarkerColorClicked()
{
  QColor color = QColorDialog::getColor(QColor(mLineEditMatchesViewerMarkerColor->text()), this, "Pick a color",  QColorDialog::DontUseNativeDialog);
  mLineEditMatchesViewerMarkerColor->setText(color.name());
  //emit matchesViewerMarkerColorChange(color.name());
}

void SettingsView::onPushButtonMatchViewerLineColorClicked()
{
  QColor color = QColorDialog::getColor(QColor(mLineEditMatchesViewerLineColor->text()), this, "Pick a color",  QColorDialog::DontUseNativeDialog);
  mLineEditMatchesViewerLineColor->setText(color.name());
  //emit matchesViewerLineColorChange(color.name());
}

void SettingsView::onPushButtonGroundTruthEditorBGColorClicked()
{
  QColor color = QColorDialog::getColor(QColor(mLineEditGroundTruthEditorBGColor->text()), this, "Pick a color",  QColorDialog::DontUseNativeDialog);
  mLineEditGroundTruthEditorBGColor->setText(color.name());
  //emit groundTruthEditorBGColorChange(color.name());
}

void SettingsView::onPushButtonGroundTruthEditorMarkerColorClicked()
{
  QColor color = QColorDialog::getColor(QColor(mLineEditGroundTruthEditorMarkerColor->text()), this, "Pick a color",  QColorDialog::DontUseNativeDialog);
  mLineEditGroundTruthEditorMarkerColor->setText(color.name());
  //emit groundTruthEditorMarkerColorChange(color.name());
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
  mListWidget->addItem(tr("Quality Control"));
  layout->addWidget(mListWidget, 0, 0, 1, 1);

  layout->addWidget(mStackedWidget, 0, 1, 1, 3);

  /* General */
  QWidget *pageGeneral = new QWidget(this);
  QGridLayout *gridLayoutGeneral = new QGridLayout(pageGeneral);

  gridLayoutGeneral->addWidget(new QLabel(tr("Language")), 0, 0, 1, 1);
  gridLayoutGeneral->addWidget(mLanguages, 0, 1, 1, 1);

  gridLayoutGeneral->addWidget(new QLabel(tr("History Max Size")), 1, 0, 1, 1);
  mHistoryMaxSize->setRange(1, 50);
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
  mLineEditImageViewerBGcolor->setText("#dcdcdc");
  gridLayoutContentsImageViewerGeneral->addWidget(mLineEditImageViewerBGcolor, 0, 1, 1, 1);
  mPushButtonImageViewerBGcolor = new QPushButton(tr("..."), tabImageViewerGeneral);
  mPushButtonImageViewerBGcolor->setMaximumSize(QSize(23, 23));
  gridLayoutContentsImageViewerGeneral->addWidget(mPushButtonImageViewerBGcolor, 0, 2, 1, 1);

  scrollAreaImageViewerGeneral->setWidget(scrollAreaWidgetContentsImageViewerGeneral);
  gridLayoutTabImageViewerGeneral->addWidget(scrollAreaImageViewerGeneral);

  tabWidgetImageViewer->addTab(tabImageViewerGeneral, QString(tr("General")));

  gridLayoutViewer->addWidget(tabWidgetImageViewer, 0, 0, 1, 1);

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
  mKeypointsFormat->setCurrentText("XML");
  gridLayoutContentsToolsGeneral->addWidget(mKeypointsFormat, 0, 1, 1, 1);
  gridLayoutContentsToolsGeneral->addWidget(new QLabel(tr("Matches Format")), 1, 0, 1, 1);
  mMatchesFormat->addItem("Binary");
  mMatchesFormat->addItem("XML");
  mMatchesFormat->addItem("YML");
  mMatchesFormat->setCurrentText("XML");
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
  mGridLayoutMatcher = new QGridLayout(tabMatching);
  mTabWidgetTools->addTab(tabMatching, QString(tr("Matching")));

  gridLayoutTools->addWidget(mTabWidgetTools, 0, 0, 1, 1);
  mStackedWidget->addWidget(pageTools);

  /* Quality Control */
  QWidget *pageQualityControl = new QWidget(this);
  QGridLayout *gridLayoutQualityControl = new QGridLayout(pageQualityControl);
  gridLayoutQualityControl->setContentsMargins(0, 0, 0, 0);

  mTabQualityControl = new QTabWidget(pageQualityControl);

  /* Keypoints Viewer */

  QWidget *tabKeypointsViewer = new QWidget(this);
  QGridLayout *gridLayoutTabKeypointsViewer = new QGridLayout(tabKeypointsViewer);
  gridLayoutTabKeypointsViewer->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollKeypointsViewer = new QScrollArea(tabKeypointsViewer);
  scrollKeypointsViewer->setWidgetResizable(true);
  scrollKeypointsViewer->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetContentsViewerKeypoints = new QWidget(this);

  QGridLayout *gridLayoutContentsFeaturesViewer = new QGridLayout(scrollAreaWidgetContentsViewerKeypoints);

  QGroupBox *groupBoxKPVGeneral = new QGroupBox(tr("General"), this);
  gridLayoutContentsFeaturesViewer->addWidget(groupBoxKPVGeneral);
  QGridLayout *layoutKPVGeneral = new QGridLayout();
  groupBoxKPVGeneral->setLayout(layoutKPVGeneral);
  layoutKPVGeneral->addWidget(new QLabel(tr("Background Color:")), 0, 0, 1, 1);
  mLineEditKeypointViewerBGColor = new QLineEdit(tabKeypointsViewer);
  mLineEditKeypointViewerBGColor->setText("#dcdcdc");
  layoutKPVGeneral->addWidget(mLineEditKeypointViewerBGColor, 0, 1, 1, 1);
  mPushButtonKeypointViewerBGColor = new QPushButton(tr("..."), tabKeypointsViewer);
  mPushButtonKeypointViewerBGColor->setMaximumSize(QSize(23, 23));
  layoutKPVGeneral->addWidget(mPushButtonKeypointViewerBGColor, 0, 2, 1, 1);

  QGroupBox *groupBoxKPVMarker = new QGroupBox(tr("Marker"), this);
  gridLayoutContentsFeaturesViewer->addWidget(groupBoxKPVMarker);
  QGridLayout *layoutKPVMarker = new QGridLayout();
  groupBoxKPVMarker->setLayout(layoutKPVMarker);
  layoutKPVMarker->addWidget(new QLabel(tr("Type:")), 0, 0, 1, 1);
  mListWidgetKeypointsViewerMarkerType = new QListWidget(this);
  mListWidgetKeypointsViewerMarkerType->setIconSize(QSize(30, 30));
  mListWidgetKeypointsViewerMarkerType->setViewMode(QListWidget::ListMode);
  mListWidgetKeypointsViewerMarkerType->setResizeMode(QListWidget::Fixed);
  mListWidgetKeypointsViewerMarkerType->addItem(new QListWidgetItem(QIcon(":/ico/96/img/material/96/keypoint.png"), "Scale/Distance", mListWidgetKeypointsViewerMarkerType));
  mListWidgetKeypointsViewerMarkerType->addItem(new QListWidgetItem(QIcon(":/ico/96/img/material/96/icons8_circled_96px.png"), "Circle", mListWidgetKeypointsViewerMarkerType));
  mListWidgetKeypointsViewerMarkerType->addItem(new QListWidgetItem(QIcon(":/ico/96/img/material/96/icons8_plus_math_96px.png"), "Cross", mListWidgetKeypointsViewerMarkerType));
  mListWidgetKeypointsViewerMarkerType->addItem(new QListWidgetItem(QIcon(":/ico/96/img/material/96/icons8_delete_sign_96px.png"), "Diagonal cross", mListWidgetKeypointsViewerMarkerType));
  mListWidgetKeypointsViewerMarkerType->setCurrentRow(0);
  layoutKPVMarker->addWidget(mListWidgetKeypointsViewerMarkerType, 0, 1, 1, 1);
  layoutKPVMarker->addWidget(new QLabel(tr("Size:")), 1, 0, 1, 1);
  mSpinBoxKeypointViewerMarkerSize = new QSpinBox(tabKeypointsViewer);
  mSpinBoxKeypointViewerMarkerSize->setRange(0, 100);
  mSpinBoxKeypointViewerMarkerSize->setValue(20);
  layoutKPVMarker->addWidget(mSpinBoxKeypointViewerMarkerSize, 1, 1, 1, 1);
  layoutKPVMarker->addWidget(new QLabel(tr("Width:")), 2, 0, 1, 1);
  mSpinBoxKeypointViewerMarkerWidth = new QSpinBox(tabKeypointsViewer);
  mSpinBoxKeypointViewerMarkerWidth->setRange(0, 50);
  mSpinBoxKeypointViewerMarkerWidth->setValue(2);
  layoutKPVMarker->addWidget(mSpinBoxKeypointViewerMarkerWidth, 2, 1, 1, 1);
  layoutKPVMarker->addWidget(new QLabel(tr("Color:")), 3, 0, 1, 1);
  mLineEditKeypointViewerMarkerColor = new QLineEdit(tabKeypointsViewer);
  mLineEditKeypointViewerMarkerColor->setText("#e5097e");
  layoutKPVMarker->addWidget(mLineEditKeypointViewerMarkerColor, 3, 1, 1, 1);
  mPushButtonKeypointViewerMarkerColor = new QPushButton(tr("..."), tabKeypointsViewer);
  mPushButtonKeypointViewerMarkerColor->setMaximumSize(QSize(23, 23));
  layoutKPVMarker->addWidget(mPushButtonKeypointViewerMarkerColor, 3, 2, 1, 1);

  gridLayoutContentsFeaturesViewer->addItem(new QSpacerItem(1,1, QSizePolicy::Fixed, QSizePolicy::Expanding), 2, 1, 1, 1);

  scrollKeypointsViewer->setWidget(scrollAreaWidgetContentsViewerKeypoints);
  gridLayoutTabKeypointsViewer->addWidget(scrollKeypointsViewer);

  mTabQualityControl->addTab(tabKeypointsViewer, QString(tr("Keypoints Viewer")));

  /* Matches Viewer */

  QWidget *tabMatchesViewer = new QWidget(this);
  QGridLayout *gridLayoutTabMatchesViewer = new QGridLayout(tabMatchesViewer);
  gridLayoutTabMatchesViewer->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollMatchesViewer = new QScrollArea(tabMatchesViewer);
  scrollMatchesViewer->setWidgetResizable(true);
  scrollMatchesViewer->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetContentsViewerMatches = new QWidget(this);

  QGridLayout *gridLayoutContentsMatchesViewer = new QGridLayout(scrollAreaWidgetContentsViewerMatches);

  QGroupBox *groupBoxMVGeneral = new QGroupBox(tr("General"), this);
  gridLayoutContentsMatchesViewer->addWidget(groupBoxMVGeneral);
  QGridLayout *layoutMVGeneral = new QGridLayout();
  groupBoxMVGeneral->setLayout(layoutMVGeneral);
  layoutMVGeneral->addWidget(new QLabel(tr("Background Color:")), 0, 0, 1, 1);
  mLineEditMatchesViewerBGColor = new QLineEdit(tabMatchesViewer);
  mLineEditMatchesViewerBGColor->setText("#dcdcdc");
  layoutMVGeneral->addWidget(mLineEditMatchesViewerBGColor, 0, 1, 1, 1);
  mPushButtonMatchesViewerBGColor = new QPushButton(tr("..."), tabMatchesViewer);
  mPushButtonMatchesViewerBGColor->setMaximumSize(QSize(23, 23));
  layoutMVGeneral->addWidget(mPushButtonMatchesViewerBGColor, 0, 2, 1, 1);

  QGroupBox *groupBoxMVMarker = new QGroupBox(tr("Marker"), this);
  gridLayoutContentsMatchesViewer->addWidget(groupBoxMVMarker);
  QGridLayout *layoutMVMarker = new QGridLayout();
  groupBoxMVMarker->setLayout(layoutMVMarker);

  layoutMVMarker->addWidget(new QLabel(tr("Type:")), 0, 0, 1, 1);
  mListWidgetMatchesViewerMarkerType = new QListWidget(this);
  mListWidgetMatchesViewerMarkerType->setIconSize(QSize(30, 30));
  mListWidgetMatchesViewerMarkerType->setViewMode(QListWidget::ListMode);
  mListWidgetMatchesViewerMarkerType->setResizeMode(QListWidget::Fixed);
  mListWidgetMatchesViewerMarkerType->addItem(new QListWidgetItem(QIcon(":/ico/96/img/material/96/icons8_circled_96px.png"), "Circle", mListWidgetMatchesViewerMarkerType));
  mListWidgetMatchesViewerMarkerType->addItem(new QListWidgetItem(QIcon(":/ico/96/img/material/96/icons8_plus_math_96px.png"), "Cross", mListWidgetMatchesViewerMarkerType));
  mListWidgetMatchesViewerMarkerType->addItem(new QListWidgetItem(QIcon(":/ico/96/img/material/96/icons8_delete_sign_96px.png"), "Diagonal cross", mListWidgetMatchesViewerMarkerType));
  mListWidgetMatchesViewerMarkerType->setCurrentRow(0);
  layoutMVMarker->addWidget(mListWidgetMatchesViewerMarkerType, 0, 1, 1, 1);
  layoutMVMarker->addWidget(new QLabel(tr("Size:")), 1, 0, 1, 1);
  mSpinBoxMatchesViewerMarkerSize = new QSpinBox(tabMatchesViewer);
  mSpinBoxMatchesViewerMarkerSize->setRange(0, 100);
  mSpinBoxMatchesViewerMarkerSize->setValue(20);
  layoutMVMarker->addWidget(mSpinBoxMatchesViewerMarkerSize, 1, 1, 1, 1);
  layoutKPVMarker->addWidget(new QLabel(tr("Width:")), 2, 0, 1, 1);
  mSpinBoxMatchesViewerMarkerWidth = new QSpinBox(tabKeypointsViewer);
  mSpinBoxMatchesViewerMarkerWidth->setRange(0, 50);
  mSpinBoxMatchesViewerMarkerWidth->setValue(2);
  layoutKPVMarker->addWidget(mSpinBoxMatchesViewerMarkerWidth, 2, 1, 1, 1);
  layoutMVMarker->addWidget(new QLabel(tr("Color:")), 3, 0, 1, 1);
  mLineEditMatchesViewerMarkerColor = new QLineEdit(tabMatchesViewer);
  mLineEditMatchesViewerMarkerColor->setText("#e5097e");
  layoutMVMarker->addWidget(mLineEditMatchesViewerMarkerColor, 3, 1, 1, 1);
  mPushButtonMatchesViewerMarkerColor = new QPushButton(tr("..."), tabMatchesViewer);
  mPushButtonMatchesViewerMarkerColor->setMaximumSize(QSize(23, 23));
  layoutMVMarker->addWidget(mPushButtonMatchesViewerMarkerColor, 3, 2, 1, 1);

  QGroupBox *groupBoxMVLine = new QGroupBox(tr("Line"), this);
  gridLayoutContentsMatchesViewer->addWidget(groupBoxMVLine);
  QGridLayout *layoutMVLine = new QGridLayout();
  groupBoxMVLine->setLayout(layoutMVLine);
  layoutMVLine->addWidget(new QLabel(tr("Width:")), 0, 0, 1, 1);
  mSpinBoxMatchesViewerLineWidth = new QSpinBox(tabMatchesViewer);
  mSpinBoxMatchesViewerLineWidth->setRange(0, 50);
  mSpinBoxMatchesViewerLineWidth->setValue(2);
  layoutMVLine->addWidget(mSpinBoxMatchesViewerLineWidth, 0, 1, 1, 1);
  layoutMVLine->addWidget(new QLabel(tr("Color:")), 1, 0, 1, 1);
  mLineEditMatchesViewerLineColor = new QLineEdit(tabMatchesViewer);
  mLineEditMatchesViewerLineColor->setText("#e5097e");
  layoutMVLine->addWidget(mLineEditMatchesViewerLineColor, 1, 1, 1, 1);
  mPushButtonMatchesViewerLineColor = new QPushButton(tr("..."), tabMatchesViewer);
  mPushButtonMatchesViewerLineColor->setMaximumSize(QSize(23, 23));
  layoutMVLine->addWidget(mPushButtonMatchesViewerLineColor, 1, 2, 1, 1);

  gridLayoutContentsMatchesViewer->addItem(new QSpacerItem(1,1, QSizePolicy::Fixed, QSizePolicy::Expanding), 3, 1, 1, 1);

  scrollMatchesViewer->setWidget(scrollAreaWidgetContentsViewerMatches);
  gridLayoutTabMatchesViewer->addWidget(scrollMatchesViewer);

  mTabQualityControl->addTab(tabMatchesViewer, QString(tr("Matches Viewer")));


  /* Ground Truth Editor */

  QWidget *tabGroundTruthEditor = new QWidget(this);
  QGridLayout *gridLayoutTabGroundTruthEditor = new QGridLayout(tabGroundTruthEditor);
  gridLayoutTabGroundTruthEditor->setContentsMargins(0, 0, 0, 0);
  QScrollArea *scrollGroundTruthEditor = new QScrollArea(tabGroundTruthEditor);
  scrollGroundTruthEditor->setWidgetResizable(true);
  scrollGroundTruthEditor->setFrameShape(QFrame::Shape::NoFrame);
  QWidget *scrollAreaWidgetContentsGroundTruthEditor = new QWidget(this);

  QGridLayout *gridLayoutContentsGroundTruthEditor = new QGridLayout(scrollAreaWidgetContentsGroundTruthEditor);

  QGroupBox *groupBoxGTEGeneral = new QGroupBox(tr("General"), this);
  gridLayoutContentsGroundTruthEditor->addWidget(groupBoxGTEGeneral);
  QGridLayout *layoutGTEGeneral = new QGridLayout();
  groupBoxGTEGeneral->setLayout(layoutGTEGeneral);
  layoutGTEGeneral->addWidget(new QLabel(tr("Background Color:")), 0, 0, 1, 1);
  mLineEditGroundTruthEditorBGColor = new QLineEdit(tabGroundTruthEditor);
  mLineEditGroundTruthEditorBGColor->setText("#dcdcdc");
  layoutGTEGeneral->addWidget(mLineEditGroundTruthEditorBGColor, 0, 1, 1, 1);
  mPushButtonGroundTruthEditorBGColor = new QPushButton(tr("..."), tabGroundTruthEditor);
  mPushButtonGroundTruthEditorBGColor->setMaximumSize(QSize(23, 23));
  layoutGTEGeneral->addWidget(mPushButtonGroundTruthEditorBGColor, 0, 2, 1, 1);

  QGroupBox *groupBoxGTEMarker = new QGroupBox(tr("Marker"), this);
  gridLayoutContentsGroundTruthEditor->addWidget(groupBoxGTEMarker);
  QGridLayout *layoutGTEMarker = new QGridLayout();
  groupBoxGTEMarker->setLayout(layoutGTEMarker);
  layoutGTEMarker->addWidget(new QLabel(tr("Size:")), 0, 0, 1, 1);
  mSpinBoxGroundTruthEditorMarkerSize = new QSpinBox(tabGroundTruthEditor);
  mSpinBoxGroundTruthEditorMarkerSize->setRange(0, 100);
  mSpinBoxGroundTruthEditorMarkerSize->setValue(20);
  layoutGTEMarker->addWidget(mSpinBoxGroundTruthEditorMarkerSize, 0, 1, 1, 1);
  layoutGTEMarker->addWidget(new QLabel(tr("Width:")), 1, 0, 1, 1);
  mSpinBoxGroundTruthEditorMarkerWidth = new QSpinBox(tabKeypointsViewer);
  mSpinBoxGroundTruthEditorMarkerWidth->setRange(0, 50);
  mSpinBoxGroundTruthEditorMarkerWidth->setValue(2);
  layoutGTEMarker->addWidget(mSpinBoxGroundTruthEditorMarkerWidth, 1, 1, 1, 1);
  layoutGTEMarker->addWidget(new QLabel(tr("Color:")), 2, 0, 1, 1);
  mLineEditGroundTruthEditorMarkerColor = new QLineEdit(tabGroundTruthEditor);
  mLineEditGroundTruthEditorMarkerColor->setText("#e5097e");
  layoutGTEMarker->addWidget(mLineEditGroundTruthEditorMarkerColor, 2, 1, 1, 1);
  mPushButtonGroundTruthEditorMarkerColor = new QPushButton(tr("..."), tabGroundTruthEditor);
  mPushButtonGroundTruthEditorMarkerColor->setMaximumSize(QSize(23, 23));
  layoutGTEMarker->addWidget(mPushButtonGroundTruthEditorMarkerColor, 2, 2, 1, 1);

  gridLayoutContentsGroundTruthEditor->addItem(new QSpacerItem(1,1, QSizePolicy::Fixed, QSizePolicy::Expanding), 2, 1, 1, 1);

  scrollGroundTruthEditor->setWidget(scrollAreaWidgetContentsGroundTruthEditor);
  gridLayoutTabGroundTruthEditor->addWidget(scrollGroundTruthEditor);

  mTabQualityControl->addTab(tabGroundTruthEditor, QString(tr("Ground Truth Editor")));

  gridLayoutQualityControl->addWidget(mTabQualityControl, 0, 0, 1, 1);
  mStackedWidget->addWidget(pageQualityControl);


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
  const QSignalBlocker blockerKeypointsFormat(mKeypointsFormat);
  const QSignalBlocker blockerMatchesFormat(mMatchesFormat);
  const QSignalBlocker blockerKeypointMarkerSize(mSpinBoxKeypointViewerMarkerSize);
  const QSignalBlocker blockerKeypointMarkerColor(mLineEditKeypointViewerMarkerColor);
  const QSignalBlocker blockerMatchesViewerMarkerSize(mSpinBoxMatchesViewerMarkerSize);
  const QSignalBlocker blockerMatchesMarkerColor(mLineEditMatchesViewerMarkerColor);
  const QSignalBlocker blockerMatchesViewerLineColor(mLineEditMatchesViewerLineColor);
  const QSignalBlocker blocker(mSpinBoxMatchesViewerLineWidth);
  const QSignalBlocker blockerKeypointViewerWidth(mSpinBoxKeypointViewerMarkerWidth);
  const QSignalBlocker blockerKeypointViewerBGColor(mLineEditKeypointViewerBGColor);
  const QSignalBlocker blockerMatchesViewerBGColo(mLineEditMatchesViewerBGColor);
  const QSignalBlocker blockerKeypointsMarker(mListWidgetKeypointsViewerMarkerType);
  const QSignalBlocker blockerMatchesMarker(mListWidgetMatchesViewerMarkerType);
  const QSignalBlocker blockerMatchesViewerMarkerWidth(mSpinBoxMatchesViewerMarkerWidth);
  const QSignalBlocker blockerGroundTruthEditorBGColor(mLineEditGroundTruthEditorBGColor);
  const QSignalBlocker blockerGroundTruthEditorMarkerSize(mSpinBoxGroundTruthEditorMarkerSize);
  const QSignalBlocker blockerGroundTruthEditorMarkerWidth(mSpinBoxGroundTruthEditorMarkerWidth);
  const QSignalBlocker blockerGroundTruthEditorMarkerColor(mLineEditGroundTruthEditorMarkerColor);
  const QSignalBlocker blockerImageViewerBGcolor(mLineEditImageViewerBGcolor);

  mLanguages->clear();

  mHistoryMaxSize->setValue(10);

  mLineEditImageViewerBGcolor->setText("#dcdcdc");

  mKeypointsFormat->setCurrentText("XML");
  mMatchesFormat->setCurrentText("XML");

  mLineEditKeypointViewerBGColor->setText("#dcdcdc");
  mListWidgetKeypointsViewerMarkerType->setCurrentRow(0);
  mSpinBoxKeypointViewerMarkerSize->setValue(20);
  mSpinBoxKeypointViewerMarkerWidth->setValue(2);
  mLineEditKeypointViewerMarkerColor->setText("#e5097e");

  mLineEditMatchesViewerBGColor->setText("#dcdcdc");
  mListWidgetMatchesViewerMarkerType->setCurrentRow(0);
  mSpinBoxMatchesViewerMarkerSize->setValue(20);
  mSpinBoxMatchesViewerMarkerWidth->setValue(2);
  mLineEditMatchesViewerMarkerColor->setText("#e5097e");
  mLineEditMatchesViewerLineColor->setText("#e5097e");
  mSpinBoxMatchesViewerLineWidth->setValue(2);

  mLineEditGroundTruthEditorBGColor->setText("#dcdcdc");
  mSpinBoxGroundTruthEditorMarkerSize->setValue(20);
  mSpinBoxGroundTruthEditorMarkerWidth->setValue(2);
  mLineEditGroundTruthEditorMarkerColor->setText("#e5097e");
}

void SettingsView::update()
{
  mButtonBox->button(QDialogButtonBox::Apply)->setEnabled(bUnsaveChanges);

  mSpinBoxKeypointViewerMarkerSize->setDisabled(mListWidgetKeypointsViewerMarkerType->currentRow() == 0);
}

QString SettingsView::activeLanguage() const
{
  return mLanguages->currentText();
}

int SettingsView::historyMaxSize() const
{
  return mHistoryMaxSize->value();
}

QString SettingsView::imageViewerBGColor() const
{
  return mLineEditImageViewerBGcolor->text();
}

QString SettingsView::keypointsFormat() const
{
  return mKeypointsFormat->currentText();
}

QString SettingsView::matchesFormat() const
{
  return mMatchesFormat->currentText();
}

QString SettingsView::keypointsViewerBGColor() const
{
  return mLineEditKeypointViewerBGColor->text();
}

int SettingsView::keypointsViewerMarkerType() const
{
  return mListWidgetKeypointsViewerMarkerType->currentRow();
}

int SettingsView::keypointsViewerMarkerSize() const
{
  return mSpinBoxKeypointViewerMarkerSize->value();
}

int SettingsView::keypointsViewerMarkerWidth() const
{
  return mSpinBoxKeypointViewerMarkerWidth->value();
}

QString SettingsView::keypointsViewerMarkerColor() const
{
  return mLineEditKeypointViewerMarkerColor->text();
}

QString SettingsView::matchesViewerBGColor() const
{
  return mLineEditMatchesViewerBGColor->text();
}

int SettingsView::matchesViewerMarkerType() const
{
  return mListWidgetMatchesViewerMarkerType->currentRow();
}

int SettingsView::matchesViewerMarkerSize() const
{
  return mSpinBoxMatchesViewerMarkerSize->value();
}

int SettingsView::matchesViewerMarkerWidth() const
{
  return mSpinBoxMatchesViewerMarkerWidth->value();
}

QString SettingsView::matchesViewerMarkerColor() const
{
  return mLineEditMatchesViewerMarkerColor->text();
}

QString SettingsView::matchesViewerLineColor() const
{
  return mLineEditMatchesViewerLineColor->text();
}

int SettingsView::matchesViewerLineWidth() const
{
  return mSpinBoxMatchesViewerLineWidth->value();
}

QString SettingsView::groundTruthEditorBGColor() const
{
  return mLineEditGroundTruthEditorBGColor->text();
}

int SettingsView::groundTruthEditorMarkerSize() const
{
  return mSpinBoxGroundTruthEditorMarkerSize->value();
}

int SettingsView::groundTruthEditorMarkerWidth() const
{
  return mSpinBoxGroundTruthEditorMarkerWidth->value();
}

QString SettingsView::groundTruthEditorMarkerColor() const
{
  return mLineEditGroundTruthEditorMarkerColor->text();
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
  const QSignalBlocker blocker(mHistoryMaxSize);
  mHistoryMaxSize->setValue(size);
}

void SettingsView::setImageViewerBGcolor(const QString &color)
{
  const QSignalBlocker blockerImageViewerBGcolor(mLineEditImageViewerBGcolor);
  mLineEditImageViewerBGcolor->setText(color);
}

void SettingsView::setKeypointsFormat(const QString &format)
{
  const QSignalBlocker blocker(mKeypointsFormat);
  mKeypointsFormat->setCurrentText(format);
}

void SettingsView::setMatchesFormat(const QString &format)
{
  const QSignalBlocker blocker(mMatchesFormat);
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

void SettingsView::setKeypointsViewerBGColor(const QString &color)
{
  const QSignalBlocker blockerKeypointViewerBGColor(mLineEditKeypointViewerBGColor);
  mLineEditKeypointViewerBGColor->setText(color);
}

void SettingsView::setKeypointsViewerMarkerType(int type)
{
  const QSignalBlocker blockerKeypointsMarker(mListWidgetKeypointsViewerMarkerType);
  mListWidgetKeypointsViewerMarkerType->setCurrentRow(type);
}

void SettingsView::setKeypointsViewerMarkerSize(int size)
{
  const QSignalBlocker blocker(mSpinBoxKeypointViewerMarkerSize);
  mSpinBoxKeypointViewerMarkerSize->setValue(size);
}

void SettingsView::setKeypointsViewerMarkerWidth(int width)
{
  const QSignalBlocker blockerKeypointViewerWidth(mSpinBoxKeypointViewerMarkerWidth);
  mSpinBoxKeypointViewerMarkerWidth->setValue(width);
}

void SettingsView::setKeypointsViewerMarkerColor(const QString &color)
{
  const QSignalBlocker blockerKeypointMarkerColor(mLineEditKeypointViewerMarkerColor);
  mLineEditKeypointViewerMarkerColor->setText(color);
}

void SettingsView::setMatchesViewerBGColor(const QString &color)
{
  const QSignalBlocker blockerMatchesViewerBGColo(mLineEditMatchesViewerBGColor);
  mLineEditMatchesViewerBGColor->setText(color);
}

void SettingsView::setMatchesViewerMarkerType(int type)
{
  const QSignalBlocker blockerMatchesMarker(mListWidgetMatchesViewerMarkerType);
  mListWidgetMatchesViewerMarkerType->setCurrentRow(type);
}

void SettingsView::setMatchesViewerMarkerSize(int size)
{
  const QSignalBlocker blocker(mSpinBoxMatchesViewerMarkerSize);
  mSpinBoxMatchesViewerMarkerSize->setValue(size);
}

void SettingsView::setMatchesViewerMarkerWidth(int width)
{
  const QSignalBlocker blockerMatchesViewerMarkerWidth(mSpinBoxMatchesViewerMarkerWidth);
  mSpinBoxMatchesViewerMarkerWidth->setValue(width);
}

void SettingsView::setMatchesViewerMarkerColor(const QString &color)
{
  const QSignalBlocker blockerMatchesMarkerColor(mLineEditMatchesViewerMarkerColor);
  mLineEditMatchesViewerMarkerColor->setText(color);
}

void SettingsView::setMatchesViewerLineColor(const QString &color)
{
  const QSignalBlocker blockerMatchesViewerLineColor(mLineEditMatchesViewerLineColor);
  mLineEditMatchesViewerLineColor->setText(color);
}

void SettingsView::setMatchesViewerLineWidth(int width)
{
  const QSignalBlocker blocker(mSpinBoxMatchesViewerLineWidth);
  mSpinBoxMatchesViewerLineWidth->setValue(width);
}

void SettingsView::setGroundTruthEditorBGColor(const QString &bgColor)
{
  const QSignalBlocker blockerGroundTruthEditorBGColor(mLineEditGroundTruthEditorBGColor);
  mLineEditGroundTruthEditorBGColor->setText(bgColor);
}

void SettingsView::setGroundTruthEditorMarkerSize(int size)
{
  const QSignalBlocker blockerGroundTruthEditorMarkerSize(mSpinBoxGroundTruthEditorMarkerSize);
  mSpinBoxGroundTruthEditorMarkerSize->setValue(size);
}

void SettingsView::setGroundTruthEditorMarkerWidth(int width)
{
  const QSignalBlocker blockerGroundTruthEditorMarkerWidth(mSpinBoxGroundTruthEditorMarkerWidth);
  mSpinBoxGroundTruthEditorMarkerWidth->setValue(width);
}

void SettingsView::setGroundTruthEditorMarkerColor(const QString &color)
{
  const QSignalBlocker blockerGroundTruthEditorMarkerColor(mLineEditGroundTruthEditorMarkerColor);
  mLineEditGroundTruthEditorMarkerColor->setText(color);
}

void SettingsView::setUnsavedChanges(bool unsaveChanges)
{
  bUnsaveChanges = unsaveChanges;
  update();
}

} // namespace photomatch

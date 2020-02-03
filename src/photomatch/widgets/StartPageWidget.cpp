#include "StartPageWidget.h"

#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QSplitter>
#include <QCommandLinkButton>
#include <QListWidget>

namespace photomatch
{

StartPageWidget::StartPageWidget(QWidget *parent)
  : PhotoMatchWidget(parent)
{
  init();

  retranslate();

  connect(mCommandLinkButtonNewProject,   SIGNAL(clicked()),  this, SIGNAL(openNew()));
  connect(mCommandLinkButtonOpenProject,  SIGNAL(clicked()),  this, SIGNAL(openProject()));
  connect(mCommandLinkButtonSettings,     SIGNAL(clicked()),  this, SIGNAL(openSettings()));
  connect(mCommandLinkButtonGitHub,       SIGNAL(clicked()),  this, SIGNAL(openGitHub()));
  connect(mCommandLinkButtonClearHistory, SIGNAL(clicked()),  this, SIGNAL(clearHistory()));

  connect(mListWidgetRecentProjects,       SIGNAL(currentTextChanged(QString)), this, SIGNAL(openProjectFromHistory(QString)));
}

void StartPageWidget::setHistory(const QStringList &history)
{
  const QSignalBlocker blocker(mListWidgetRecentProjects);
  mListWidgetRecentProjects->clear();
  mListWidgetRecentProjects->addItems(history);
}

void StartPageWidget::update()
{
}

void StartPageWidget::retranslate()
{
  this->setWindowTitle(QApplication::translate("StartPage", "Start Page", nullptr));
  mLabelPhotoMatch->setText(QApplication::translate("StartPage", "PhotoMatch", nullptr));
  mCommandLinkButtonNewProject->setText(QApplication::translate("StartPage", "New Project", nullptr));
  mCommandLinkButtonOpenProject->setText(QApplication::translate("StartPage", "Open Project", nullptr));
  mCommandLinkButtonSettings->setText(QApplication::translate("StartPage", "Settings", nullptr));
  mCommandLinkButtonGitHub->setText(QApplication::translate("StartPage", "GitHub", nullptr));
  mLabelRecentProjects->setText(QApplication::translate("StartPage", "Recent Projects", nullptr));
  mCommandLinkButtonClearHistory->setText(QApplication::translate("StartPage", "Clear History", nullptr));
}

void StartPageWidget::reset()
{
}

void StartPageWidget::init()
{

  QGridLayout *layout = new QGridLayout(this);
  layout->setSpacing(6);
  layout->setContentsMargins(11, 11, 11, 11);

  mLabelPhotoMatch = new QLabel(this);
  mLabelPhotoMatch->setMaximumSize(QSize(16777215, 79));
  QFont font;
  font.setFamily(QStringLiteral("Arial Black"));
  font.setPointSize(28);
  font.setBold(true);
  font.setWeight(75);
  mLabelPhotoMatch->setFont(font);
  mLabelPhotoMatch->setStyleSheet(QStringLiteral("color: rgb(26, 188, 156);"));

  layout->addWidget(mLabelPhotoMatch, 0, 0, 1, 1);

  mSplitter = new QSplitter(this);
  mSplitter->setOrientation(Qt::Horizontal);
  QWidget *layoutWidgetButtons = new QWidget(mSplitter);
  QVBoxLayout *verticalLayout = new QVBoxLayout(layoutWidgetButtons);
  verticalLayout->setSpacing(6);
  verticalLayout->setContentsMargins(11, 11, 11, 11);
  verticalLayout->setContentsMargins(9, 9, 9, 9);
  mCommandLinkButtonNewProject = new QCommandLinkButton(layoutWidgetButtons);
  QIcon icon;
  icon.addFile(QStringLiteral(":/ico/48/img/material/48/icons8_file_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mCommandLinkButtonNewProject->setIcon(icon);
  mCommandLinkButtonNewProject->setIconSize(QSize(48, 48));

  verticalLayout->addWidget(mCommandLinkButtonNewProject);

  mCommandLinkButtonOpenProject = new QCommandLinkButton(layoutWidgetButtons);
  QIcon icon1;
  icon1.addFile(QStringLiteral(":/ico/48/img/material/48/icons8_opened_folder_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mCommandLinkButtonOpenProject->setIcon(icon1);
  mCommandLinkButtonOpenProject->setIconSize(QSize(48, 48));

  verticalLayout->addWidget(mCommandLinkButtonOpenProject);

  QFrame *line = new QFrame(layoutWidgetButtons);
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);

  verticalLayout->addWidget(line);

  mCommandLinkButtonSettings = new QCommandLinkButton(layoutWidgetButtons);
  QIcon icon2;
  icon2.addFile(QStringLiteral(":/ico/48/img/material/48/icons8_automatic_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mCommandLinkButtonSettings->setIcon(icon2);
  mCommandLinkButtonSettings->setIconSize(QSize(48, 48));

  verticalLayout->addWidget(mCommandLinkButtonSettings);

  QSpacerItem *verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

  verticalLayout->addItem(verticalSpacer);

  mCommandLinkButtonGitHub = new QCommandLinkButton(layoutWidgetButtons);
  QIcon icon3;
  icon3.addFile(QStringLiteral(":/ico/48/img/material/48/icons8_github_48px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mCommandLinkButtonGitHub->setIcon(icon3);
  mCommandLinkButtonGitHub->setIconSize(QSize(48, 48));

  verticalLayout->addWidget(mCommandLinkButtonGitHub);

  mSplitter->addWidget(layoutWidgetButtons);

  QWidget *layoutWidget2 = new QWidget(mSplitter);
  QVBoxLayout *verticalLayout2 = new QVBoxLayout(layoutWidget2);
  verticalLayout2->setSpacing(6);
  verticalLayout2->setContentsMargins(11, 11, 11, 11);
  verticalLayout2->setContentsMargins(9, 9, 9, 9);
  mLabelRecentProjects = new QLabel(layoutWidget2);
  mLabelRecentProjects->setMinimumSize(QSize(0, 68));
  mLabelRecentProjects->setMaximumSize(QSize(16777215, 68));
  QFont font1;
  font1.setFamily(QStringLiteral("Segoe UI"));
  font1.setPointSize(12);
  mLabelRecentProjects->setFont(font1);
  mLabelRecentProjects->setStyleSheet(QStringLiteral("color: rgb(0, 0, 127);"));

  verticalLayout2->addWidget(mLabelRecentProjects);

  mListWidgetRecentProjects = new QListWidget(layoutWidget2);
  QFont font2;
  font2.setPointSize(11);
  mListWidgetRecentProjects->setFont(font2);
  mListWidgetRecentProjects->setFrameShape(QFrame::NoFrame);
  mListWidgetRecentProjects->setFrameShadow(QFrame::Sunken);
  mListWidgetRecentProjects->setViewMode(QListView::ListMode);

  verticalLayout2->addWidget(mListWidgetRecentProjects);

  mCommandLinkButtonClearHistory = new QCommandLinkButton(layoutWidget2);
  QIcon icon4;
  icon4.addFile(QStringLiteral(":/ico/24/img/material/24/icons8_delete_trash_24px.png"), QSize(), QIcon::Normal, QIcon::Off);
  mCommandLinkButtonClearHistory->setIcon(icon4);
  mCommandLinkButtonClearHistory->setIconSize(QSize(24, 24));

  verticalLayout2->addWidget(mCommandLinkButtonClearHistory);

  mSplitter->addWidget(layoutWidget2);

  layout->addWidget(mSplitter, 1, 0, 1, 1);
}

} // namespace photomatch


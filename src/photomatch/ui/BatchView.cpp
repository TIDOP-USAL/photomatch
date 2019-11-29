#include "BatchView.h"

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QListWidget>
#include <QTreeWidget>
#include <QScrollArea>
#include <QComboBox>
#include <QTextEdit>
#include <QApplication>

namespace photomatch
{

BatchView::BatchView(QWidget *parent)
  : IBatchView(parent)
{
  init();
}


void BatchView::init()
{
  this->setObjectName(QStringLiteral("BatchDialog"));
  this->resize(1023, 746);

  QGridLayout *gridLayout = new QGridLayout();
  gridLayout->setContentsMargins(0, 0, 0, 0);
  this->setLayout(gridLayout);
  QScrollArea *scrollArea = new QScrollArea(this);
  scrollArea->setWidgetResizable(true);
  QWidget *scrollAreaWidgetContents = new QWidget();
  scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1021, 744));
  QGridLayout *gridLayout_3 = new QGridLayout(scrollAreaWidgetContents);

  mLabelSession = new QLabel(scrollAreaWidgetContents);
  gridLayout_3->addWidget(mLabelSession, 0, 0, 1, 1);

  mWidgetProcessContainer = new QWidget(scrollAreaWidgetContents);
  gridLayout_3->addWidget(mWidgetProcessContainer, 0, 2, 6, 1);

  mComboBoxSession = new QComboBox(scrollAreaWidgetContents);
  gridLayout_3->addWidget(mComboBoxSession, 1, 0, 1, 1);

  mLabelProcess = new QLabel(scrollAreaWidgetContents);
  gridLayout_3->addWidget(mLabelProcess, 3, 0, 1, 1);

  mPushButtonAddProcess = new QPushButton(scrollAreaWidgetContents);
  mPushButtonAddProcess->setMaximumSize(QSize(75, 23));
  gridLayout_3->addWidget(mPushButtonAddProcess, 0, 3, 1, 1);

  mListWidgetProcess = new QListWidget(scrollAreaWidgetContents);
  mListWidgetProcess->setMinimumSize(QSize(256, 101));
  mListWidgetProcess->setMaximumSize(QSize(256, 16777215));
  gridLayout_3->addWidget(mListWidgetProcess, 4, 0, 2, 1);

  mTabWidget = new QTabWidget(scrollAreaWidgetContents);
  mTabProcess = new QWidget();
  QGridLayout *gridLayout_4 = new QGridLayout(mTabProcess);
  mTreeWidget = new QTreeWidget(mTabProcess);
  mTreeWidget->setObjectName(QStringLiteral("treeWidget"));
  gridLayout_4->addWidget(mTreeWidget, 0, 0, 6, 1);

  mPushButtonDown = new QPushButton(mTabProcess);
  gridLayout_4->addWidget(mPushButtonDown, 1, 1, 1, 1);

  mPushButtonUp = new QPushButton(mTabProcess);
  gridLayout_4->addWidget(mPushButtonUp, 0, 1, 1, 1);

  mPushButtonDeleteProcess = new QPushButton(mTabProcess);
  gridLayout_4->addWidget(mPushButtonDeleteProcess, 2, 1, 1, 1);

  pushButton = new QPushButton(mTabProcess);
  gridLayout_4->addWidget(pushButton, 3, 1, 1, 1);

  mTabWidget->addTab(mTabProcess, QString());

  tabProcessTextView = new QWidget();
  QGridLayout *gridLayout_2 = new QGridLayout(tabProcessTextView);
  mTextEditBatch = new QTextEdit(tabProcessTextView);

  gridLayout_2->addWidget(mTextEditBatch, 0, 0, 1, 1);

  mTabWidget->addTab(tabProcessTextView, QString());

  gridLayout_3->addWidget(mTabWidget, 6, 0, 1, 4);

  scrollArea->setWidget(scrollAreaWidgetContents);

  gridLayout->addWidget(scrollArea, 0, 0, 1, 1);

  retranslate();
}

void BatchView::clear()
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);

  mComboBoxSession->clear();

  update();
}

void BatchView::update()
{

}

void BatchView::retranslate()
{
  mLabelProcess->setText(QApplication::translate("BatchDialog", "Process:", nullptr));
  mPushButtonAddProcess->setText(QApplication::translate("BatchDialog", "Add Process", nullptr));
  QTreeWidgetItem *header = mTreeWidget->headerItem();
  header->setText(3, QApplication::translate("BatchDialog", "Progress", nullptr));
  header->setText(2, QApplication::translate("BatchDialog", "Session", nullptr));
  header->setText(1, QApplication::translate("BatchDialog", "Process", nullptr));
  header->setText(0, QApplication::translate("BatchDialog", "ID", nullptr));
  mPushButtonDown->setText(QApplication::translate("BatchDialog", "Down", nullptr));
  mPushButtonUp->setText(QApplication::translate("BatchDialog", "Up", nullptr));
  mPushButtonDeleteProcess->setText(QApplication::translate("BatchDialog", "Delete", nullptr));
  pushButton->setText(QApplication::translate("BatchDialog", "Clean Batch", nullptr));
  mTabWidget->setTabText(mTabWidget->indexOf(mTabProcess), QApplication::translate("BatchDialog", "Process", nullptr));
  mTabWidget->setTabText(mTabWidget->indexOf(tabProcessTextView), QApplication::translate("BatchDialog", "Text view", nullptr));
  mLabelSession->setText(QApplication::translate("BatchDialog", "Session", nullptr));
}

void BatchView::open()
{
  this->show();
}

void BatchView::setSessions(const QStringList &sessions)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->addItems(sessions);
}

void BatchView::setActiveSession(const QString &session)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->setCurrentText(session);
}

} // namespace photomatch

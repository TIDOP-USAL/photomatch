#include "ExportMatchesView.h"

#include <QIcon>
#include <QGridLayout>
#include <QLabel>
#include <QApplication>
#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QCheckBox>
#include <QListWidget>
#include <QLineEdit>

namespace photomatch
{

ExportMatchesView::ExportMatchesView(QWidget *parent)
  : IExportMatchesView(parent)
{
  init();

  connect(mComboBoxSession,        SIGNAL(currentTextChanged(QString)), this, SIGNAL(sessionChange(QString)));

  connect(mButtonBox,  SIGNAL(accepted()), this, SLOT(accept()));
  connect(mButtonBox,  SIGNAL(rejected()), this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)),   this, SIGNAL(help()));
}

ExportMatchesView::~ExportMatchesView()
{

}

void ExportMatchesView::setSessions(const QStringList &sessions)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->clear();
  mComboBoxSession->addItems(sessions);
}

void ExportMatchesView::setActiveSession(const QString &session)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->setCurrentText(session);
}

void ExportMatchesView::init()
{
  this->setObjectName(QStringLiteral("ExportMatchesView"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(440, 140);

  QGridLayout *gridLayout = new QGridLayout();
  this->setLayout(gridLayout);

  mLabelSession = new QLabel(this);
  mLabelSession->setMaximumSize(QSize(71, 16777215));
  gridLayout->addWidget(mLabelSession, 0, 0, 1, 1);

  mComboBoxSession = new QComboBox(this);
  gridLayout->addWidget(mComboBoxSession, 0, 1, 1, 2);

  mButtonBox = new QDialogButtonBox(this);
  mButtonBox->setOrientation(Qt::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok|QDialogButtonBox::Help);
  gridLayout->addWidget(mButtonBox, 3, 0, 1, 3);

  retranslate();

  update();
}

void ExportMatchesView::clear()
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);

  mComboBoxSession->clear();

  update();
}

void ExportMatchesView::update()
{

}

void ExportMatchesView::retranslate()
{
  this->setWindowTitle(QApplication::translate("ExportMatchesView", "Export Keypoints", nullptr));
  mLabelSession->setText(QApplication::translate("ExportMatchesView", "Session:", nullptr));

  mButtonBox->button(QDialogButtonBox::Cancel)->setText(QApplication::translate("ExportMatchesView", "Cancel", nullptr));
  mButtonBox->button(QDialogButtonBox::Ok)->setText(QApplication::translate("ExportMatchesView", "Export", nullptr));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("ExportMatchesView", "Help", nullptr));
}

} // namespace photomatch





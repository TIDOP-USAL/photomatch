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
  //connect(mComboBoxFormat,         SIGNAL(currentTextChanged(QString)), this, SIGNAL(formatChange(QString)));
  //connect(mLineEditExportPath,     SIGNAL(textChanged(QString)),        this, SLOT(update()));

  connect(mButtonBox,  SIGNAL(accepted()), this, SLOT(accept()));
  connect(mButtonBox,  SIGNAL(rejected()), this, SLOT(reject()));
  //connect(mButtonBox->button(QDialogButtonBox::Save),   SIGNAL(clicked(bool)),   this, SIGNAL(exportMatches()));
  connect(mButtonBox->button(QDialogButtonBox::Help),   SIGNAL(clicked(bool)),   this, SIGNAL(help()));
}

ExportMatchesView::~ExportMatchesView()
{

}

//void ExportMatchesView::onPushButtonExportFormat()
//{
//  QString pathName = QFileDialog::getExistingDirectory(this,
//    tr("Export folder"),
//    "",
//    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

//  if (!pathName.isEmpty()) {
//    mLineEditExportPath->setText(pathName);
//  }

//  update();
//}

//QString ExportMatchesView::format() const
//{
//  return mComboBoxFormat->currentText();
//}

//QString ExportMatchesView::exportPath() const
//{
//  return mLineEditExportPath->text();
//}

void ExportMatchesView::setSessions(const QStringList &sessions)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->addItems(sessions);
}

void ExportMatchesView::setActiveSession(const QString &session)
{
  const QSignalBlocker blockerComboBoxSession(mComboBoxSession);
  mComboBoxSession->setCurrentText(session);
}

//void ExportMatchesView::setFormats(const QStringList &formats)
//{
//  const QSignalBlocker blockerComboBoxFormat(mComboBoxFormat);
//  mComboBoxFormat->addItems(formats);
//}

//void ExportMatchesView::setCurrentFormat(const QString &format)
//{
//  const QSignalBlocker blockerComboBoxFormat(mComboBoxFormat);
//  mComboBoxFormat->setCurrentText(format);
//}

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

//  mLabelFormat = new QLabel(this);
//  mLabelFormat->setMaximumSize(QSize(71, 16777215));
//  gridLayout->addWidget(mLabelFormat, 1, 0, 1, 1);

//  mComboBoxFormat = new QComboBox(this);
//  gridLayout->addWidget(mComboBoxFormat, 1, 1, 1, 2);

//  mLabelExportPath = new QLabel(this);
//  gridLayout->addWidget(mLabelExportPath, 2, 0, 1, 1);

//  mLineEditExportPath = new QLineEdit(this);
//  gridLayout->addWidget(mLineEditExportPath, 2, 1, 1, 1);

//  mPushButtonExportFormat = new QPushButton(this);
//  mPushButtonExportFormat->setMaximumSize(QSize(23, 16777215));
//  mPushButtonExportFormat->setText("...");
//  gridLayout->addWidget(mPushButtonExportFormat, 2, 2, 1, 1);

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
//  const QSignalBlocker blockerComboBoxFormat(mComboBoxFormat);
//  const QSignalBlocker blockerLineEditExportPath(mLineEditExportPath);

  mComboBoxSession->clear();
//  mComboBoxFormat->clear();
//  mLineEditExportPath->clear();

  update();
}

void ExportMatchesView::update()
{
//  bool bSave = !mLineEditExportPath->text().isEmpty();
//  mButtonBox->button(QDialogButtonBox::Save)->setEnabled(bSave);
}

void ExportMatchesView::retranslate()
{
  this->setWindowTitle(QApplication::translate("ExportMatchesView", "Export Keypoints", nullptr));
  mLabelSession->setText(QApplication::translate("ExportMatchesView", "Session:", nullptr));
  //mLabelFormat->setText(QApplication::translate("ExportMatchesView", "Format:", nullptr));
  //mLabelExportPath->setText(QApplication::translate("ExportMatchesView", "Export path:", nullptr));

  mButtonBox->button(QDialogButtonBox::Cancel)->setText(QApplication::translate("ExportMatchesView", "Cancel", nullptr));
  mButtonBox->button(QDialogButtonBox::Ok)->setText(QApplication::translate("ExportMatchesView", "Export", nullptr));
  mButtonBox->button(QDialogButtonBox::Help)->setText(QApplication::translate("ExportMatchesView", "Help", nullptr));
}

} // namespace photomatch





#include "NewSessionView.h"

#include <QLineEdit>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>
#include <QIcon>

namespace fme
{

NewSessionView::NewSessionView(QWidget *parent)
  : INewSessionView(parent),
    mLineEditSessionName(new QLineEdit(this)),
    mTextEditSessionDescription(new QTextEdit(this)),
    mButtonBox(new QDialogButtonBox(this))
{
  init();

  connect(mLineEditSessionName,        SIGNAL(textChanged(QString)), this, SLOT(update()));
  connect(mTextEditSessionDescription, SIGNAL(stateChanged(int)),    this, SLOT(update()));

  connect(mButtonBox,  SIGNAL(accepted()), this, SLOT(accept()));
  connect(mButtonBox,  SIGNAL(rejected()), this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)), this, SIGNAL(help()));

}

NewSessionView::~NewSessionView()
{

}

void NewSessionView::init()
{
  this->setWindowTitle(tr("New Session"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(450,250);

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  layout->addWidget(new QLabel(tr("Session Name")), 0, 0);
  layout->addWidget(mLineEditSessionName, 0, 1, 1, 2);

  layout->addWidget(new QLabel(tr("Description")), 1, 0);
  layout->addWidget(mTextEditSessionDescription, 2, 0, 1, 3);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  mButtonBox->button(QDialogButtonBox::Save)->setText("Save");
  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  layout->addWidget(mButtonBox, 4, 0, 1, 3);

  update();
}

void NewSessionView::clear()
{
  mLineEditSessionName->clear();
  mTextEditSessionDescription->clear();
}

void NewSessionView::update()
{
  bool bSave = !mLineEditSessionName->text().isEmpty();
  mButtonBox->button(QDialogButtonBox::Save)->setEnabled(bSave);
}

QString NewSessionView::sessionName() const
{
  return mLineEditSessionName->text();
}

QString NewSessionView::sessionDescription() const
{
  return mTextEditSessionDescription->toPlainText();
}

} // namespace fme

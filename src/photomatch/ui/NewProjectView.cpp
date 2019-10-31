#include "NewProjectView.h"

#include <QFileDialog>
#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>
#include <QGridLayout>
#include <QLabel>

namespace photomatch
{

NewProjectView::NewProjectView(QWidget *parent)
  : INewProjectView(parent),
    mLineEditProjectName(new QLineEdit(this)),
    mLineEditProjectPath(new QLineEdit(this)),
    mLineEditProjectFile(new QLineEdit(this)),
    mTextEditDescription(new QTextEdit(this)),
    mCheckBoxProjectFolder(new QCheckBox(this)),
    mPushButtonProjectPath(new QPushButton(this)),
    mButtonBox(new QDialogButtonBox(this))
{

  init();

  connect(mLineEditProjectName,   SIGNAL(textChanged(QString)), this, SLOT(update()));
  connect(mLineEditProjectPath,   SIGNAL(textChanged(QString)), this, SLOT(update()));
  connect(mCheckBoxProjectFolder, SIGNAL(stateChanged(int)),    this, SLOT(update()));

  connect(mButtonBox,  SIGNAL(accepted()), this, SLOT(accept()));
  connect(mButtonBox,  SIGNAL(rejected()), this, SLOT(reject()));
  connect(mButtonBox->button(QDialogButtonBox::Help),    SIGNAL(clicked(bool)), this, SIGNAL(help()));

  connect(mPushButtonProjectPath, SIGNAL(clicked(bool)), this, SLOT(onClickButtonSelectPath()));

}

NewProjectView::~NewProjectView()
{
}


// INewProjectView interface

// public:

QString NewProjectView::projectName() const
{
  return mLineEditProjectName->text();
}

QString NewProjectView::projectPath() const
{
  return mLineEditProjectPath->text();
}

void NewProjectView::setProjectPath(const QString &path)
{
  mLineEditProjectPath->setText(path);
}

QString NewProjectView::projectDescription() const
{
  return mTextEditDescription->toPlainText();
}

bool NewProjectView::createProjectFolder() const
{
  return mCheckBoxProjectFolder->isChecked();
}

// protected slots:

void NewProjectView::onClickButtonSelectPath()
{
  QString pathName = QFileDialog::getExistingDirectory(this,
    tr("Project path"),
    mLineEditProjectPath->text(),
    QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

  if (!pathName.isEmpty()) {
    mLineEditProjectPath->setText(pathName);
  }
}

// IDialogView interface

// private:

void NewProjectView::init()
{
  this->setWindowTitle(tr("New Project"));
  this->setWindowIcon(QIcon(":/ico/app/img/FMELogo.ico"));
  this->resize(450,300);

  QGridLayout *layout = new QGridLayout();
  this->setLayout(layout);

  layout->addWidget(new QLabel(tr("Project Name")), 0, 0);
  layout->addWidget(mLineEditProjectName, 0, 1, 1, 2);

  layout->addWidget(new QLabel(tr("Project Path")), 1, 0);
  layout->addWidget(mLineEditProjectPath, 1, 1);
  mPushButtonProjectPath->setMaximumSize(QSize(31,28));
  mPushButtonProjectPath->setText("...");
  layout->addWidget(mPushButtonProjectPath, 1, 2);

  layout->addWidget(new QLabel(tr("Project File")), 2, 0);
  mLineEditProjectFile->setEnabled(false);
  layout->addWidget(mLineEditProjectFile, 2, 1, 1, 2);

  mCheckBoxProjectFolder->setText(tr("Create folder with project name"));
  mCheckBoxProjectFolder->setChecked(true);
  layout->addWidget(mCheckBoxProjectFolder, 3, 0, 1, 3);

  layout->addWidget(new QLabel(tr("Description")), 4, 0);

  layout->addWidget(mTextEditDescription, 5, 0, 1, 3);

  mButtonBox->setOrientation(Qt::Orientation::Horizontal);
  mButtonBox->setStandardButtons(QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::Help);
  mButtonBox->button(QDialogButtonBox::Save)->setText("Save");
  mButtonBox->button(QDialogButtonBox::Cancel)->setText("Cancel");
  mButtonBox->button(QDialogButtonBox::Help)->setText("Help");
  layout->addWidget(mButtonBox, 7, 0, 1, 3);

  update();
}

// public slots:

void NewProjectView::clear()
{
  mLineEditProjectName->clear();
  mLineEditProjectPath->clear();
  mLineEditProjectFile->clear();
  mTextEditDescription->clear();
  mCheckBoxProjectFolder->setChecked(true);
}

// private slots:

void NewProjectView::update()
{
  bool bSave = !mLineEditProjectName->text().isEmpty() &&
    !mLineEditProjectPath->text().isEmpty();
  mButtonBox->button(QDialogButtonBox::Save)->setEnabled(bSave);

  if (bSave){
    QString file(mLineEditProjectPath->text());
    if (mCheckBoxProjectFolder->isChecked()){
      file.append(QDir::separator()).append(mLineEditProjectName->text());
    }
    file.append(QDir::separator()).append(mLineEditProjectName->text()).append(".xml");
    mLineEditProjectFile->setText(QDir::cleanPath(file));
  } else 
	  mLineEditProjectFile->setText("");
}

} // namespace photomatch

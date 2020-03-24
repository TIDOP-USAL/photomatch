#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/NewProjectView.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>

using namespace photomatch;

class TestNewProjectView : public NewProjectViewImp
{
  Q_OBJECT

public:

  TestNewProjectView();
  ~TestNewProjectView();

private slots:

  void test_constructor();
  void test_projectName();
  void test_projectPath_data();
  void test_projectPath();
  void test_projectPath_signals();
  void test_lineEditProjectFile();
  void test_projectDescription();
  void test_createProjectFolder();
  void test_pushButtonProjectPath();
  void test_dialogButtonBox();
  void test_clear();
};

TestNewProjectView::TestNewProjectView()
  : NewProjectViewImp()
{
  QApplication::setActiveWindow(this);
}

TestNewProjectView::~TestNewProjectView()
{
}

void TestNewProjectView::test_constructor()
{
  NewProjectViewImp newProjectView;
  QCOMPARE("", newProjectView.projectName());
  QCOMPARE("", newProjectView.projectPath());
  QCOMPARE("", newProjectView.projectDescription());
  QCOMPARE(true, newProjectView.createProjectFolder());
}

void TestNewProjectView::test_projectName()
{

  /// Simulación de entrada por teclado

  this->mLineEditProjectName->clear();
  QTest::keyClicks(this->mLineEditProjectName, "project");

  QCOMPARE(this->projectName(), QString("project"));
}

void TestNewProjectView::test_projectPath_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("C:/Users/Tido/Documents/photomatch/Projects") << "C:/Users/Tido/Documents/photomatch/Projects" << "C:/Users/Tido/Documents/photomatch/Projects";
  QTest::newRow("C:/Users/user1/Documents/photomatch/Projects") << "C:/Users/user1/Documents/photomatch/Projects" << "C:/Users/user1/Documents/photomatch/Projects";
}

void TestNewProjectView::test_projectPath()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setProjectPath(value);
  QCOMPARE(result, this->projectPath());
}

void TestNewProjectView::test_projectPath_signals()
{
  /// Simulación de entrada por teclado

  QString project_path = this->projectPath();

  QTest::keyClick(this->mLineEditProjectPath, '_');
  QCOMPARE(this->projectPath(), project_path.append("_"));

  this->mLineEditProjectPath->clear();
  QTest::keyClicks(this->mLineEditProjectPath, "C:/Users/user1/Documents/photomatch/Projects");
  QCOMPARE(this->projectPath(), QString("C:/Users/user1/Documents/photomatch/Projects"));
}

void TestNewProjectView::test_lineEditProjectFile()
{
  /// Desactivado
  QCOMPARE(this->mLineEditProjectFile->isEnabled(), false);


  this->mLineEditProjectPath->clear();
  QTest::keyClicks(this->mLineEditProjectPath, "C:/Users/user1/Documents/photomatch/Projects");

  this->mLineEditProjectName->clear();
  QTest::keyClicks(this->mLineEditProjectName, "project_name");

  QTest::mouseClick(this->mCheckBoxProjectFolder, Qt::MouseButton::LeftButton);
  QString file(this->projectPath());
  if (createProjectFolder())
    file.append(QDir::separator()).append(this->projectName());
  file.append(QDir::separator()).append(this->projectName()).append(".xml");
  QCOMPARE(this->mLineEditProjectFile->text(), QDir::cleanPath(file));


  QTest::mouseClick(this->mCheckBoxProjectFolder, Qt::MouseButton::LeftButton);
  file = this->projectPath();
  if (createProjectFolder())
    file.append(QDir::separator()).append(this->projectName());
  file.append(QDir::separator()).append(this->projectName()).append(".xml");
  QCOMPARE(this->mLineEditProjectFile->text(), QDir::cleanPath(file));

  this->mLineEditProjectName->clear();
  QCOMPARE(this->mLineEditProjectFile->text(), "");
}

void TestNewProjectView::test_projectDescription()
{
  /// Simulación de entrada por teclado

  QString project_description = this->projectDescription();

  QTest::keyClick(this->mTextEditDescription, '_');
  QCOMPARE(project_description.append("_"), this->projectDescription());

  this->mTextEditDescription->clear();

  QTest::keyClicks(this->mTextEditDescription, "description");
  QCOMPARE(QString("description"), this->projectDescription());
}

void TestNewProjectView::test_createProjectFolder()
{
  mCheckBoxProjectFolder->setChecked(true);
  QCOMPARE(true, this->createProjectFolder());

  mCheckBoxProjectFolder->setChecked(false);
  QCOMPARE(false, this->createProjectFolder());
}

void TestNewProjectView::test_pushButtonProjectPath()
{

}

void TestNewProjectView::test_dialogButtonBox()
{

  QSignalSpy spy_rejected(this, &NewProjectViewImp::rejected);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Cancel), Qt::LeftButton);
  QCOMPARE(spy_rejected.count(), 1);

  mButtonBox->button(QDialogButtonBox::Save)->setEnabled(true);
  QSignalSpy spy_accepted(this, &NewProjectViewImp::accepted);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Save), Qt::LeftButton);
  QCOMPARE(spy_accepted.count(), 1);

  QSignalSpy spy_help(this, &NewProjectViewImp::help);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Help), Qt::LeftButton);
  QCOMPARE(spy_help.count(), 1);
}

void TestNewProjectView::test_clear()
{
  this->clear();

  QCOMPARE(this->projectName(), QString(""));
  QCOMPARE(this->projectPath(), QString(""));
  QCOMPARE(this->mLineEditProjectFile->text(), QString(""));
  QCOMPARE(this->projectDescription(), QString(""));
  QCOMPARE(true, this->createProjectFolder());
}

QTEST_MAIN(TestNewProjectView)

#include "tst_newprojectview.moc"

#include <QtTest>
#include <QCoreApplication>

#include "fme/ui/NewProjectView.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>

using namespace fme;

class TestNewProjectView : public NewProjectView
{
  Q_OBJECT

public:

  TestNewProjectView();
  ~TestNewProjectView();

private slots:

  void testDefaultConstructor();
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
  : NewProjectView()
{
  QApplication::setActiveWindow(this);
}

TestNewProjectView::~TestNewProjectView()
{
}

void TestNewProjectView::testDefaultConstructor()
{

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

  QTest::newRow("C:/Users/Tido/Documents/fme/Projects") << "C:/Users/Tido/Documents/fme/Projects" << "C:/Users/Tido/Documents/fme/Projects";
  QTest::newRow("C:/Users/user1/Documents/fme/Projects") << "C:/Users/user1/Documents/fme/Projects" << "C:/Users/user1/Documents/fme/Projects";
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

  //this->mLineEditProjectPath->setFocus();
  QTest::keyClick(this->mLineEditProjectPath, '_');
  QCOMPARE(this->projectPath(), project_path.append("_"));

  this->mLineEditProjectPath->clear();
  QTest::keyClicks(this->mLineEditProjectPath, "C:/Users/user1/Documents/fme/Projects");
  QCOMPARE(this->projectPath(), QString("C:/Users/user1/Documents/fme/Projects"));
}

void TestNewProjectView::test_lineEditProjectFile()
{
  /// Desactivado
  QCOMPARE(this->mLineEditProjectFile->isEnabled(), false);


  this->mLineEditProjectPath->clear();
  QTest::keyClicks(this->mLineEditProjectPath, "C:/Users/user1/Documents/fme/Projects");

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

  //QTest::keyClicks(this->mTextEditDescription, "Descripción del proyecto");

//  QCOMPARE(this->projectDescription(), QString("Descripción del proyecto"));
}

void TestNewProjectView::test_createProjectFolder()
{

}

void TestNewProjectView::test_pushButtonProjectPath()
{

}

void TestNewProjectView::test_dialogButtonBox()
{

  QSignalSpy spy_rejected(this, &NewProjectView::rejected);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Cancel), Qt::LeftButton);
  QCOMPARE(spy_rejected.count(), 1);

  mButtonBox->button(QDialogButtonBox::Save)->setEnabled(true);
  QSignalSpy spy_accepted(this, &NewProjectView::accepted);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Save), Qt::LeftButton);
  QCOMPARE(spy_accepted.count(), 1);

  QSignalSpy spy_help(this, &NewProjectView::help);
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
}

QTEST_MAIN(TestNewProjectView)

#include "tst_newprojectview.moc"

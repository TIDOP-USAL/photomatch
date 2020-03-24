#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/NewSessionView.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>

using namespace photomatch;

class TestNewSessionView
  : public NewSessionViewImp
{
  Q_OBJECT

public:

  TestNewSessionView();
  ~TestNewSessionView();

private slots:

  void testDefaultConstructor();
  void test_sessionName();
  void test_sessionDescription();
  void test_dialogButtonBox();
  void test_clear();
};

TestNewSessionView::TestNewSessionView()
  : NewSessionViewImp()
{
  QApplication::setActiveWindow(this);
}

TestNewSessionView::~TestNewSessionView()
{
}

void TestNewSessionView::testDefaultConstructor()
{
  NewSessionViewImp newSessionView;
  QCOMPARE("", newSessionView.sessionName());
  QCOMPARE("", newSessionView.sessionDescription());
}

void TestNewSessionView::test_sessionName()
{

  /// Simulación de entrada por teclado

  this->mLineEditSessionName->clear();
  QTest::keyClicks(this->mLineEditSessionName, "session01");

  QCOMPARE(this->sessionName(), QString("session01"));
}

void TestNewSessionView::test_sessionDescription()
{
  /// Simulación de entrada por teclado

  QString session_description = this->sessionDescription();

  QTest::keyClick(this->mTextEditSessionDescription, '_');
  QCOMPARE(session_description.append("_"), this->sessionDescription());

  this->mTextEditSessionDescription->clear();

  QTest::keyClicks(this->mTextEditSessionDescription, "description");
  QCOMPARE(QString("description"), this->sessionDescription());
}

void TestNewSessionView::test_dialogButtonBox()
{

  QSignalSpy spy_rejected(this, &NewSessionViewImp::rejected);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Cancel), Qt::LeftButton);
  QCOMPARE(spy_rejected.count(), 1);

  QSignalSpy spy_help(this, &NewSessionViewImp::help);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Help), Qt::LeftButton);
  QCOMPARE(spy_help.count(), 1);
}

void TestNewSessionView::test_clear()
{
  this->mLineEditSessionName->setText("session1");
  this->mTextEditSessionDescription->setText("description");

  this->clear();

  QCOMPARE(this->sessionName(), QString(""));
  QCOMPARE(this->sessionDescription(), QString(""));
}

QTEST_MAIN(TestNewSessionView)

#include "tst_newsessionview.moc"

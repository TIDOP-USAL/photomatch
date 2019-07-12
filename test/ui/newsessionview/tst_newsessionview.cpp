#include <QtTest>
#include <QCoreApplication>

#include "fme/ui/NewSessionView.h"

#include <QLineEdit>
#include <QCheckBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QTextEdit>

using namespace fme;

class TestNewSessionView
  : public NewSessionView
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
  : NewSessionView()
{
  QApplication::setActiveWindow(this);
}

TestNewSessionView::~TestNewSessionView()
{
}

void TestNewSessionView::testDefaultConstructor()
{

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

  //QTest::keyClicks(this->mTextEditDescription, "Descripción del proyecto");

//  QCOMPARE(this->projectDescription(), QString("Descripción del proyecto"));
}

void TestNewSessionView::test_dialogButtonBox()
{

  QSignalSpy spy_rejected(this, &NewSessionView::rejected);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Cancel), Qt::LeftButton);
  QCOMPARE(spy_rejected.count(), 1);

//  QSignalSpy spy_accepted(this, &NewSessionView::accepted);
//  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Save), Qt::LeftButton);
//  QCOMPARE(spy_accepted.count(), 1);

  QSignalSpy spy_help(this, &NewSessionView::help);
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

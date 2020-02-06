#include <QtTest>

#include "photomatch/widgets/BriefWidget.h"

#include <QCheckBox>
#include <QComboBox>

using namespace photomatch;

class TestBriefWidgetsSignals : public BriefWidgetImp
{
  Q_OBJECT

public:

  TestBriefWidgetsSignals();
  ~TestBriefWidgetsSignals();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_bytesChange();
  void test_useOrientationChange();


};

TestBriefWidgetsSignals::TestBriefWidgetsSignals()
  : BriefWidgetImp()
{

}

TestBriefWidgetsSignals::~TestBriefWidgetsSignals()
{

}

void TestBriefWidgetsSignals::initTestCase()
{

}

void TestBriefWidgetsSignals::cleanupTestCase()
{
  QSignalSpy spy_useOrientationChange(this, &BriefWidgetImp::useOrientationChange);

  this->setUseOrientation(true);

  this->reset();

  QCOMPARE(spy_useOrientationChange.count(), 0);
}

void TestBriefWidgetsSignals::test_bytesChange()
{
  QSignalSpy spy_bytesChange(this, &BriefWidgetImp::bytesChange);

  this->mBytes->setCurrentText("64");

  QCOMPARE(spy_bytesChange.count(), 1);

  QList<QVariant> args = spy_bytesChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "64");

  this->mBytes->setCurrentText("64");
  QCOMPARE(spy_bytesChange.count(), 0);

  this->setBytes("16");
  QCOMPARE(spy_bytesChange.count(), 0);
}

void TestBriefWidgetsSignals::test_useOrientationChange()
{
  QSignalSpy spy_useOrientationChange(this, &BriefWidgetImp::useOrientationChange);

  QTest::mouseClick(mUseOrientation, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_useOrientationChange.count(), 1);

  QList<QVariant> args = spy_useOrientationChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setUseOrientation(true);
  QCOMPARE(spy_useOrientationChange.count(), 0);
}



QTEST_MAIN(TestBriefWidgetsSignals)

#include "tst_briefwidgetssignals.moc"

#include <QtTest>

#include "fme/widgets/BriefWidget.h"

#include <QCheckBox>
#include <QComboBox>

using namespace fme;

class TestBriefWidgetsSignals : public BriefWidget
{
  Q_OBJECT

public:

  TestBriefWidgetsSignals();
  ~TestBriefWidgetsSignals();

private slots:

  void test_bytesChange();
  void test_useOrientationChange();
  void test_reset();

};

TestBriefWidgetsSignals::TestBriefWidgetsSignals()
  : BriefWidget()
{

}

TestBriefWidgetsSignals::~TestBriefWidgetsSignals()
{

}

void TestBriefWidgetsSignals::test_bytesChange()
{
  QSignalSpy spy_bytesChange(this, &BriefWidget::bytesChange);

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
  QSignalSpy spy_useOrientationChange(this, &BriefWidget::useOrientationChange);

  QTest::mouseClick(mUseOrientation, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_useOrientationChange.count(), 1);

  QList<QVariant> args = spy_useOrientationChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setUseOrientation(true);
  QCOMPARE(spy_useOrientationChange.count(), 0);
}

void TestBriefWidgetsSignals::test_reset()
{
  QSignalSpy spy_useOrientationChange(this, &BriefWidget::useOrientationChange);

  this->setUseOrientation(true);

  this->reset();

  QCOMPARE(spy_useOrientationChange.count(), 0);
}

QTEST_MAIN(TestBriefWidgetsSignals)

#include "tst_briefwidgetssignals.moc"

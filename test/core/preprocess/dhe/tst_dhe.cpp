#include <QtTest>
#include <QCoreApplication>

#include "photomatch/photomatch_global.h"
#include "photomatch/core/preprocess/dhe.h"

using namespace photomatch;

class TestDhe 
  : public QObject
{
  Q_OBJECT

public:

  TestDhe();
  ~TestDhe();

private slots:

  void test_constructors();
  void test_type();
  void test_name();
  void test_x_data();
  void test_x();
  void test_reset();

private:

  DhePreprocess *mDhePreprocess;
};

TestDhe::TestDhe()
  : mDhePreprocess(new DhePreprocess)
{

}

TestDhe::~TestDhe()
{
  if (mDhePreprocess){
    delete mDhePreprocess;
    mDhePreprocess = nullptr;
  }
}

void TestDhe::test_constructors()
{
  DhePreprocess dhePreprocess;
  QCOMPARE(1, dhePreprocess.x());

  /// Copy constructor
  DhePreprocess copy(dhePreprocess);
  QCOMPARE(1, copy.x());

  /// Move contructor
  DhePreprocess move(DhePreprocess(1));
  QCOMPARE(1, move.x());
}

void TestDhe::test_type()
{
  QCOMPARE(Preprocess::Type::dhe, mDhePreprocess->type());
}

void TestDhe::test_name()
{
  QCOMPARE(QString("DHE"), mDhePreprocess->name());
}

void TestDhe::test_x_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
}

void TestDhe::test_x()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mDhePreprocess->setX(value);
  QCOMPARE(result, mDhePreprocess->x());
}

void TestDhe::test_reset()
{
  mDhePreprocess->setX(3);

  mDhePreprocess->reset();

  QCOMPARE(1, mDhePreprocess->x());
}


QTEST_MAIN(TestDhe)

#include "tst_dhe.moc"

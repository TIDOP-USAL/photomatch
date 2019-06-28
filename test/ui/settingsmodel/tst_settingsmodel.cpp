#include <QtTest>

#include "fme/ui/SettingsModel.h"

class TestSettingsModel : public QObject
{
  Q_OBJECT

public:
  TestSettingsModel();
  ~TestSettingsModel();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_case1();

};

TestSettingsModel::TestSettingsModel()
{

}

TestSettingsModel::~TestSettingsModel()
{

}

void TestSettingsModel::initTestCase()
{

}

void TestSettingsModel::cleanupTestCase()
{

}

void TestSettingsModel::test_case1()
{

}

QTEST_MAIN(TestSettingsModel)

#include "tst_settingsmodel.moc"

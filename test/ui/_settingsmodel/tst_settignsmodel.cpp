#include <QtTest>

//#include "fme/core/project.h"
#include "fme/ui/SettingsModel.h"

using namespace fme;


class TestSettingsModel : public QObject
{
  Q_OBJECT

public:

  TestSettingsModel();
  ~TestSettingsModel();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void testConstructor();

protected:

  ISettingsModel *mSettingsModel;
};

TestSettingsModel::TestSettingsModel()
  : mSettingsModel()
{

}

TestSettingsModel::~TestSettingsModel()
{
  if (mSettingsModel) {
    delete mSettingsModel;
    mSettingsModel = nullptr;
  }
}

void TestSettingsModel::initTestCase()
{
}

void TestSettingsModel::cleanupTestCase()
{

}

void TestSettingsModel::testConstructor()
{

}

QTEST_APPLESS_MAIN(TestSettingsModel)

#include "tst_settingsmodel.moc"

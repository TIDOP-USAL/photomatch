#include <QtTest>

#include "fme/ui/SettingsModel.h"

using namespace fme;


class SettingsRWFake
  : public ISettingsRW
{

protected:

  struct Data{
    QString lang = "en";
  };

public:

  SettingsRWFake()
    : ISettingsRW()
  {}

  ~SettingsRWFake() override {}

// ISettingsRW interface

public:

  void read(ISettings &settings) override
  {
    settings.setLanguage(this->data.lang);
  }

  void write(const ISettings &settings) override
  {
    this->data.lang = settings.language();
  }

protected:

  Data data;


};



class TestSettingsModel : public QObject
{
  Q_OBJECT

public:
  TestSettingsModel();
  ~TestSettingsModel();

private slots:
  void initTestCase();
  void cleanupTestCase();
  void test_defaultValues();
  void test_language();
  void test_reset();

protected:

  ISettings *mSettings;
  ISettingsRW *mSettingsRWFake;
  ISettingsModel *mSettingsModel;

};

TestSettingsModel::TestSettingsModel()
  : mSettings(new Settings),
    mSettingsRWFake(new SettingsRWFake)
{
  mSettingsModel = new SettingsModel(mSettings, mSettingsRWFake);
}

TestSettingsModel::~TestSettingsModel()
{
  if (mSettings){
    delete mSettings;
    mSettings = nullptr;
  }

  if (mSettingsRWFake){
    delete mSettingsRWFake;
    mSettingsRWFake = nullptr;
  }

  if (mSettingsModel){
    delete mSettingsModel;
    mSettingsModel = nullptr;
  }
}

void TestSettingsModel::initTestCase()
{
  mSettingsModel->read();
}

void TestSettingsModel::cleanupTestCase()
{

}

void TestSettingsModel::test_defaultValues()
{
  Settings settings;
  SettingsRWFake rw;
  SettingsModel settingsModel(&settings, &rw);

  QCOMPARE("en", settingsModel.language());
  QCOMPARE(false, settingsModel.checkUnsavedChanges());
}

void TestSettingsModel::test_language()
{
  QCOMPARE(false, mSettingsModel->checkUnsavedChanges());
  QCOMPARE("en", mSettingsModel->language());

  mSettingsModel->setLanguage("es");
  QCOMPARE("es", mSettingsModel->language());
  QCOMPARE(true, mSettingsModel->checkUnsavedChanges());
}

void TestSettingsModel::test_reset()
{
  mSettingsModel->reset();
  QCOMPARE("en", mSettingsModel->language());
  QCOMPARE(false, mSettingsModel->checkUnsavedChanges());
}

QTEST_MAIN(TestSettingsModel)

#include "tst_settingsmodel.moc"

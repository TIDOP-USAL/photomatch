#include <QtTest>

#include "fme/ui/SettingsModel.h"

using namespace fme;

class SettingsModelFake
  : public ISettingsModel
{
  Q_OBJECT

  struct Data{
    QString lang = "en";
  };

public:

  explicit SettingsModelFake(ISettings *settings, QObject *parent = nullptr)
    : ISettingsModel(parent),
      mSettings(settings),
      bUnsavedChanges(false)
  {
    init();
  }

  ~SettingsModelFake() override
  {

  }

  // ISettings interface

public:

  QString language() const override
  {
    return mSettings->language();
  }

  void setLanguage(const QString &language) override
  {
    mSettings->setLanguage(language);
    bUnsavedChanges = true;
  }

// IModel interface

private:

  void init() override
  {
    read();
  }

// ISettingsModel interface

public:

  void read() override
  {
    mSettings->setLanguage(this->data.lang);
  }

  void write() override
  {
    this->data.lang = mSettings->language();

    bUnsavedChanges = false;
  }

  bool checkUnsavedChanges() const override
  {
    return bUnsavedChanges;
  }

protected:

  ISettings *mSettings;
  bool bUnsavedChanges;
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
  void test_language();
  void test_checkUnsavedChanges();

protected:

  ISettings *mSettings;
  ISettingsModel *mSettingsModel;

};

TestSettingsModel::TestSettingsModel()
  : mSettings(new Settings),
    mSettingsModel(new SettingsModelFake(mSettings))
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

void TestSettingsModel::test_language()
{

}

void TestSettingsModel::test_checkUnsavedChanges()
{

}


QTEST_MAIN(TestSettingsModel)

#include "tst_settingsmodel.moc"

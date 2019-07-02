#include <QtTest>

#include "fme/core/settings.h"

using namespace fme;

class TestSettings : public QObject
{
  Q_OBJECT

public:
  TestSettings();
  ~TestSettings();

private slots:

  void test_defaultValues();
  void test_language_data();
  void test_language();
  void test_reset();
protected:

  ISettings *mSettings;
};

TestSettings::TestSettings()
  : mSettings(new Settings)
{

}

TestSettings::~TestSettings()
{

}

void TestSettings::test_defaultValues()
{
  Settings settings;
  QCOMPARE("en", settings.language());
}

void TestSettings::test_language_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("en") << "en" << "en";
  QTest::newRow("es") << "es" << "es";
}

void TestSettings::test_language()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setLanguage(value);
  QCOMPARE(result, mSettings->language());
}

void TestSettings::test_reset()
{
  mSettings->setLanguage("es");
  mSettings->reset();
  QCOMPARE("en", mSettings->language());
}

QTEST_APPLESS_MAIN(TestSettings)

#include "tst_settings.moc"

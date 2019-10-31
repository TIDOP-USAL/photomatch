#include <QtTest>

#include "photomatch/core/settings.h"

using namespace photomatch;

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
  void test_history();
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
  QCOMPARE(10, settings.historyMaxSize());
  QCOMPARE(QStringList(), settings.history());
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

void TestSettings::test_history()
{
  mSettings->setHistoryMaxSize(8);
  QCOMPARE(8, mSettings->historyMaxSize());

  /// Se añaden proyectos al historial

  mSettings->addToHistory("c://projects/prj01.xml");
  mSettings->addToHistory("c://projects/prj02.xml");
  mSettings->addToHistory("c://projects/prj03.xml");
  mSettings->addToHistory("c://projects/prj04.xml");
  mSettings->addToHistory("c://projects/prj05.xml");
  mSettings->addToHistory("c://projects/prj06.xml");
  mSettings->addToHistory("c://projects/prj07.xml");
  mSettings->addToHistory("c://projects/prj08.xml");
  mSettings->addToHistory("c://projects/prj09.xml");
  mSettings->addToHistory("c://projects/prj10.xml");
  mSettings->addToHistory("c://projects/prj11.xml");

  /// Se recupera el historial
  QStringList h = mSettings->history();
  QCOMPARE(8, h.size());
  QCOMPARE("c://projects/prj11.xml", h[0]);

  /// Se borra el historial
  mSettings->clearHistory();
  h = mSettings->history();
  QCOMPARE(0, h.size());
}

void TestSettings::test_reset()
{
  mSettings->setLanguage("es");
  mSettings->reset();
  QCOMPARE("en", mSettings->language());
  QCOMPARE(10, mSettings->historyMaxSize());
  QCOMPARE(QStringList(), mSettings->history());
}

QTEST_APPLESS_MAIN(TestSettings)

#include "tst_settings.moc"

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

  void test_historyMaxSize_data();
  void test_historyMaxSize();

  void test_keypointsFormat_data();
  void test_keypointsFormat();

  void test_matchesFormat_data();
  void test_matchesFormat();

  void test_keypointsViewerBGColor_data();
  void test_keypointsViewerBGColor();
  void test_keypointsViewerMarkerSize_data();
  void test_keypointsViewerMarkerSize();
  void test_keypointsViewerMarkerWidth_data();
  void test_keypointsViewerMarkerWidth();
  void test_keypointsViewerMarkerColor_data();
  void test_keypointsViewerMarkerColor();

  void test_matchesViewerBGColor_data();
  void test_matchesViewerBGColor();
  void test_matchesViewerMarkerSize_data();
  void test_matchesViewerMarkerSize();
  void test_matchesViewerMarkerColor_data();
  void test_matchesViewerMarkerColor();
  void test_matchesViewerLineColor_data();
  void test_matchesViewerLineColor();
  void test_matchesViewerLineWidth_data();
  void test_matchesViewerLineWidth();

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

void TestSettings::test_historyMaxSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("10") << 10 << 10;
}

void TestSettings::test_historyMaxSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setHistoryMaxSize(value);
  QCOMPARE(result, mSettings->historyMaxSize());
}

void TestSettings::test_keypointsFormat_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("XML") << "XML" << "XML";
  QTest::newRow("YML") << "YML" << "YML";
  QTest::newRow("Binary") << "Binary" << "Binary";
}

void TestSettings::test_keypointsFormat()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setKeypointsFormat(value);
  QCOMPARE(result, mSettings->keypointsFormat());
}

void TestSettings::test_matchesFormat_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("XML") << "XML" << "XML";
  QTest::newRow("YML") << "YML" << "YML";
  QTest::newRow("Binary") << "Binary" << "Binary";
}

void TestSettings::test_matchesFormat()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesFormat(value);
  QCOMPARE(result, mSettings->matchesFormat());
}

void TestSettings::test_keypointsViewerBGColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_keypointsViewerBGColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setKeypointsViewerBGColor(value);
  QCOMPARE(result, mSettings->keypointsViewerBGColor());
}

void TestSettings::test_keypointsViewerMarkerSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_keypointsViewerMarkerSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setKeypointsViewerMarkerSize(value);
  QCOMPARE(result, mSettings->keypointsViewerMarkerSize());
}

void TestSettings::test_keypointsViewerMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_keypointsViewerMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setKeypointsViewerMarkerWidth(value);
  QCOMPARE(result, mSettings->keypointsViewerMarkerWidth());
}

void TestSettings::test_keypointsViewerMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_keypointsViewerMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setKeypointsViewerMarkerColor(value);
  QCOMPARE(result, mSettings->keypointsViewerMarkerColor());
}

void TestSettings::test_matchesViewerBGColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_matchesViewerBGColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesViewerBGColor(value);
  QCOMPARE(result, mSettings->matchesViewerBGColor());
}

void TestSettings::test_matchesViewerMarkerSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_matchesViewerMarkerSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setMatchesViewerMarkerSize(value);
  QCOMPARE(result, mSettings->matchesViewerMarkerSize());
}

void TestSettings::test_matchesViewerMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_matchesViewerMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesViewerMarkerColor(value);
  QCOMPARE(result, mSettings->matchesViewerMarkerColor());
}

void TestSettings::test_matchesViewerLineColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettings::test_matchesViewerLineColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  mSettings->setMatchesViewerLineColor(value);
  QCOMPARE(result, mSettings->matchesViewerLineColor());
}

void TestSettings::test_matchesViewerLineWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
}

void TestSettings::test_matchesViewerLineWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  mSettings->setMatchesViewerLineWidth(value);
  QCOMPARE(result, mSettings->matchesViewerLineWidth());
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

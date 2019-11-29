#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/SettingsView.h"

#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QLineEdit>
#include <QListWidget>
#include <QCheckBox>

using namespace photomatch;

class TestSettingsView : public SettingsView
{
  Q_OBJECT

public:

  TestSettingsView();
  ~TestSettingsView();

private slots:

  void initTestCase();
  void cleanupTestCase();

  void test_setLanguages();
  void test_setActiveLanguage();
  void test_languageChange();

  void test_historyMaxSize_data();
  void test_historyMaxSize();
  void test_historyMaxSizeChange();

  void test_keypointsFormat_data();
  void test_keypointsFormat();
  void test_keypointsFormatChange();

  void test_matchesFormat_data();
  void test_matchesFormat();
  void test_matchesFormatChange();

  void test_useCuda();
  void test_useCudaChange();

  void test_keypointsViewerBGColor_data();
  void test_keypointsViewerBGColor();
  void test_keypointsViewerBGColorChange();
  void test_keypointsViewerMarkerType_data();
  void test_keypointsViewerMarkerType();
  void test_keypointsViewerMarkerTypeChange();
  void test_keypointsViewerMarkerSize_data();
  void test_keypointsViewerMarkerSize();
  void test_keypointsViewerMarkerSizeChange();
  void test_keypointsViewerMarkerWidth_data();
  void test_keypointsViewerMarkerWidth();
  void test_keypointsViewerMarkerWidthChange();
  void test_keypointsViewerMarkerColor_data();
  void test_keypointsViewerMarkerColor();
  void test_keypointsViewerMarkerColorChange();

  void test_matchesViewerBGColor_data();
  void test_matchesViewerBGColor();
  void test_matchesViewerBGColorChange();
  void test_matchesViewerMarkerType_data();
  void test_matchesViewerMarkerType();
  void test_matchesViewerMarkerTypeChange();
  void test_matchesViewerMarkerSize_data();
  void test_matchesViewerMarkerSize();
  void test_matchesViewerMarkerSizeChange();
  void test_matchesViewerMarkerWidth_data();
  void test_matchesViewerMarkerWidth();
  void test_matchesViewerMarkerWidthChange();
  void test_matchesViewerMarkerColor_data();
  void test_matchesViewerMarkerColor();
  void test_matchesViewerMarkerColorChange();
  void test_matchesViewerLineColor_data();
  void test_matchesViewerLineColor();
  void test_matchesViewerLineColorChange();
  void test_matchesViewerLineWidth_data();
  void test_matchesViewerLineWidth();
  void test_matchesViewerLineWidthChange();

  void test_groundTruthEditorBGColor_data();
  void test_groundTruthEditorBGColor();
  void test_groundTruthEditorBGColorChange();
  void test_groundTruthEditorMarkerSize_data();
  void test_groundTruthEditorMarkerSize();
  void test_groundTruthEditorMarkerSizeChange();
  void test_groundTruthEditorMarkerWidth_data();
  void test_groundTruthEditorMarkerWidth();
  void test_groundTruthEditorMarkerWidthChange();
  void test_groundTruthEditorMarkerColor_data();
  void test_groundTruthEditorMarkerColor();
  void test_groundTruthEditorMarkerColorChange();

  void test_dialogButtonBox();
  void test_setUnsavedChanges();
  void test_onFeatureDetectorDescriptorChange();
  void test_addFeatureDetectorMethod();
  void test_onPreprocessChange();
  void test_addPreprocess();

private:

  QStringList list;

};

TestSettingsView::TestSettingsView()
  : SettingsView()
{
  QApplication::setActiveWindow(this);
}

TestSettingsView::~TestSettingsView()
{

}

void TestSettingsView::initTestCase()
{
  list.push_back("English");
  list.push_back("Spanish");
  this->setLanguages(list);


}

void TestSettingsView::cleanupTestCase()
{

}

void TestSettingsView::test_setLanguages()
{
  QSignalSpy spy_languageChange(this, &SettingsView::languageChange);
  this->setLanguages(list);
  QCOMPARE(spy_languageChange.count(), 0);
  QCOMPARE(2, mLanguages->count());
  QCOMPARE("English", mLanguages->itemText(0));
  QCOMPARE("Spanish", mLanguages->itemText(1));
}

void TestSettingsView::test_setActiveLanguage()
{
  this->setActiveLanguage("English");
  QCOMPARE("English", mLanguages->currentText());
}

void TestSettingsView::test_languageChange()
{
  QSignalSpy spy_languageChange(this, &SettingsView::languageChange);

  this->mLanguages->setCurrentText("Spanish");
  QCOMPARE(spy_languageChange.count(), 1);
  QList<QVariant> args = spy_languageChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "Spanish");

  this->mLanguages->setCurrentText("Spanish");
  QCOMPARE(spy_languageChange.count(), 0);

  this->setActiveLanguage("English");
  QCOMPARE(spy_languageChange.count(), 0);
}

void TestSettingsView::test_historyMaxSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("10") << 10 << 10;
  QTest::newRow("Out of range value") << 0 << 1;
  QTest::newRow("Out of range value") << 51 << 50;
}

void TestSettingsView::test_historyMaxSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setHistoryMaxSize(value);
  QCOMPARE(result, this->historyMaxSize());
}

void TestSettingsView::test_historyMaxSizeChange()
{
  QSignalSpy spy_historyMaxSizeChange(this, &SettingsView::historyMaxSizeChange);

  this->mHistoryMaxSize->setValue(5);

  QCOMPARE(spy_historyMaxSizeChange.count(), 1);

  QList<QVariant> args = spy_historyMaxSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5);

  this->setHistoryMaxSize(20);
  QCOMPARE(spy_historyMaxSizeChange.count(), 0);
}

void TestSettingsView::test_keypointsFormat_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("XML") << "XML" << "XML";
  QTest::newRow("YML") << "YML" << "YML";
  QTest::newRow("Binary") << "Binary" << "Binary";
}

void TestSettingsView::test_keypointsFormat()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setKeypointsFormat(value);
  QCOMPARE(result, this->keypointsFormat());
}

void TestSettingsView::test_keypointsFormatChange()
{
  QSignalSpy spy_keypointsFormatChange(this, &SettingsView::keypointsFormatChange);

  this->mKeypointsFormat->setCurrentText("YML");

  QCOMPARE(spy_keypointsFormatChange.count(), 1);

  QList<QVariant> args = spy_keypointsFormatChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "YML");

  this->setKeypointsFormat("Binary");
  QCOMPARE(spy_keypointsFormatChange.count(), 0);
}

void TestSettingsView::test_matchesFormat_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("XML") << "XML" << "XML";
  QTest::newRow("YML") << "YML" << "YML";
  QTest::newRow("Binary") << "Binary" << "Binary";
}

void TestSettingsView::test_matchesFormat()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setMatchesFormat(value);
  QCOMPARE(result, this->matchesFormat());
}

void TestSettingsView::test_matchesFormatChange()
{
  QSignalSpy spy_matchesFormatChange(this, &SettingsView::matchesFormatChange);

  this->mMatchesFormat->setCurrentText("YML");

  QCOMPARE(spy_matchesFormatChange.count(), 1);

  QList<QVariant> args = spy_matchesFormatChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "YML");

  this->setMatchesFormat("Binary");
  QCOMPARE(spy_matchesFormatChange.count(), 0);
}

void TestSettingsView::test_useCuda()
{
  this->setUseCuda(false);
  QCOMPARE(false, this->useCuda());

  this->setUseCuda(true);
  QCOMPARE(true, this->useCuda());

  this->setCudaEnabled(false);
  QCOMPARE(false, this->useCuda());

  this->setCudaEnabled(true);
  QCOMPARE(true, this->useCuda());
}

void TestSettingsView::test_useCudaChange()
{

  QSignalSpy spy_useCudaChange(this, &SettingsView::useCudaChange);

  QTest::mouseClick(this->mCheckBoxUseCuda, Qt::MouseButton::LeftButton);

  QCOMPARE(spy_useCudaChange.count(), 1);

  QList<QVariant> args = spy_useCudaChange.takeFirst();
  QCOMPARE(args.at(0).toBool(), true);

  this->setUseCuda(true);
  QCOMPARE(spy_useCudaChange.count(), 0);
}

void TestSettingsView::test_keypointsViewerBGColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettingsView::test_keypointsViewerBGColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setKeypointsViewerBGColor(value);
  QCOMPARE(result, this->keypointsViewerBGColor());
}

void TestSettingsView::test_keypointsViewerBGColorChange()
{
  QSignalSpy spy_keypointsViewerBGColorChange(this, &SettingsView::keypointsViewerBGColorChange);

  this->mLineEditKeypointViewerBGColor->setText("#5625ff");

  QCOMPARE(spy_keypointsViewerBGColorChange.count(), 1);

  QList<QVariant> args = spy_keypointsViewerBGColorChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "#5625ff");

  this->setKeypointsViewerBGColor("FF00FF");
  QCOMPARE(spy_keypointsViewerBGColorChange.count(), 0);
}

void TestSettingsView::test_keypointsViewerMarkerType_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("0") << 0 << 0;
  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
}

void TestSettingsView::test_keypointsViewerMarkerType()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setKeypointsViewerMarkerType(value);
  QCOMPARE(result, this->keypointsViewerMarkerType());
}

void TestSettingsView::test_keypointsViewerMarkerTypeChange()
{
  QSignalSpy spy_keypointsViewerMarkerTypeChange(this, &SettingsView::keypointsViewerMarkerTypeChange);

  this->mListWidgetKeypointsViewerMarkerType->setCurrentRow(1);

  QCOMPARE(spy_keypointsViewerMarkerTypeChange.count(), 1);

  QList<QVariant> args = spy_keypointsViewerMarkerTypeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 1);

  this->setKeypointsViewerMarkerType(1);
  QCOMPARE(spy_keypointsViewerMarkerTypeChange.count(), 0);
}

void TestSettingsView::test_keypointsViewerMarkerSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestSettingsView::test_keypointsViewerMarkerSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setKeypointsViewerMarkerSize(value);
  QCOMPARE(result, this->keypointsViewerMarkerSize());
}

void TestSettingsView::test_keypointsViewerMarkerSizeChange()
{
  QSignalSpy spy_keypointsViewerMarkerSizeChange(this, &SettingsView::keypointsViewerMarkerSizeChange);

  this->mSpinBoxKeypointViewerMarkerSize->setValue(30);

  QCOMPARE(spy_keypointsViewerMarkerSizeChange.count(), 1);

  QList<QVariant> args = spy_keypointsViewerMarkerSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 30);

  this->setKeypointsViewerMarkerSize(20);
  QCOMPARE(spy_keypointsViewerMarkerSizeChange.count(), 0);
}

void TestSettingsView::test_keypointsViewerMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("Out of range value") << 51 << 50;
}

void TestSettingsView::test_keypointsViewerMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setKeypointsViewerMarkerWidth(value);
  QCOMPARE(result, this->keypointsViewerMarkerWidth());
}

void TestSettingsView::test_keypointsViewerMarkerWidthChange()
{
  QSignalSpy spy_keypointsViewerMarkerWidthChange(this, &SettingsView::keypointsViewerMarkerWidthChange);

  this->mSpinBoxKeypointViewerMarkerWidth->setValue(30);

  QCOMPARE(spy_keypointsViewerMarkerWidthChange.count(), 1);

  QList<QVariant> args = spy_keypointsViewerMarkerWidthChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 30);

  this->setKeypointsViewerMarkerWidth(20);
  QCOMPARE(spy_keypointsViewerMarkerWidthChange.count(), 0);
}


void TestSettingsView::test_keypointsViewerMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettingsView::test_keypointsViewerMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setKeypointsViewerMarkerColor(value);
  QCOMPARE(result, this->keypointsViewerMarkerColor());
}

void TestSettingsView::test_keypointsViewerMarkerColorChange()
{
  QSignalSpy spy_keypointsViewerMarkerColorChange(this, &SettingsView::keypointsViewerMarkerColorChange);

  this->mLineEditKeypointViewerMarkerColor->setText("#253612");

  QCOMPARE(spy_keypointsViewerMarkerColorChange.count(), 1);

  QList<QVariant> args = spy_keypointsViewerMarkerColorChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "#253612");

  this->setKeypointsViewerMarkerColor("FF00FF");
  QCOMPARE(spy_keypointsViewerMarkerColorChange.count(), 0);
}

void TestSettingsView::test_matchesViewerBGColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettingsView::test_matchesViewerBGColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setMatchesViewerBGColor(value);
  QCOMPARE(result, this->matchesViewerBGColor());
}

void TestSettingsView::test_matchesViewerBGColorChange()
{
  QSignalSpy spy_matchesViewerBGColorChange(this, &SettingsView::matchesViewerBGColorChange);

  this->mLineEditMatchesViewerBGColor->setText("#253612");

  QCOMPARE(spy_matchesViewerBGColorChange.count(), 1);

  QList<QVariant> args = spy_matchesViewerBGColorChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "#253612");

  this->setMatchesViewerBGColor("FF00FF");
  QCOMPARE(spy_matchesViewerBGColorChange.count(), 0);
}

void TestSettingsView::test_matchesViewerMarkerType_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("0") << 0 << 0;
  QTest::newRow("1") << 1 << 1;
  QTest::newRow("2") << 2 << 2;
}

void TestSettingsView::test_matchesViewerMarkerType()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setMatchesViewerMarkerType(value);
  QCOMPARE(result, this->matchesViewerMarkerType());
}

void TestSettingsView::test_matchesViewerMarkerTypeChange()
{
  QSignalSpy spy_matchesViewerMarkerTypeChange(this, &SettingsView::matchesViewerMarkerTypeChange);

  this->mListWidgetMatchesViewerMarkerType->setCurrentRow(1);

  QCOMPARE(spy_matchesViewerMarkerTypeChange.count(), 1);

  QList<QVariant> args = spy_matchesViewerMarkerTypeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 1);

  this->setMatchesViewerMarkerType(2);
  QCOMPARE(spy_matchesViewerMarkerTypeChange.count(), 0);
}

void TestSettingsView::test_matchesViewerMarkerSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestSettingsView::test_matchesViewerMarkerSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setMatchesViewerMarkerSize(value);
  QCOMPARE(result, this->matchesViewerMarkerSize());
}

void TestSettingsView::test_matchesViewerMarkerSizeChange()
{
  QSignalSpy spy_matchesViewerMarkerSizeChange(this, &SettingsView::matchesViewerMarkerSizeChange);

  this->mSpinBoxMatchesViewerMarkerSize->setValue(30);

  QCOMPARE(spy_matchesViewerMarkerSizeChange.count(), 1);

  QList<QVariant> args = spy_matchesViewerMarkerSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 30);

  this->setMatchesViewerMarkerSize(20);
  QCOMPARE(spy_matchesViewerMarkerSizeChange.count(), 0);
}

void TestSettingsView::test_matchesViewerMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("Out of range value") << 51 << 50;
}

void TestSettingsView::test_matchesViewerMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setMatchesViewerMarkerWidth(value);
  QCOMPARE(result, this->matchesViewerMarkerWidth());
}

void TestSettingsView::test_matchesViewerMarkerWidthChange()
{
  QSignalSpy spy_matchesViewerMarkerWidthChange(this, &SettingsView::matchesViewerMarkerWidthChange);

  this->mSpinBoxMatchesViewerMarkerWidth->setValue(5);

  QCOMPARE(spy_matchesViewerMarkerWidthChange.count(), 1);

  QList<QVariant> args = spy_matchesViewerMarkerWidthChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5);

  this->setMatchesViewerMarkerWidth(3);
  QCOMPARE(spy_matchesViewerMarkerWidthChange.count(), 0);
}

void TestSettingsView::test_matchesViewerMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettingsView::test_matchesViewerMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setMatchesViewerMarkerColor(value);
  QCOMPARE(result, this->matchesViewerMarkerColor());
}

void TestSettingsView::test_matchesViewerMarkerColorChange()
{
  QSignalSpy spy_matchesViewerMarkerColorChange(this, &SettingsView::matchesViewerMarkerColorChange);

  this->mLineEditMatchesViewerMarkerColor->setText("#253612");

  QCOMPARE(spy_matchesViewerMarkerColorChange.count(), 1);

  QList<QVariant> args = spy_matchesViewerMarkerColorChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "#253612");

  this->setMatchesViewerMarkerColor("FF00FF");
  QCOMPARE(spy_matchesViewerMarkerColorChange.count(), 0);
}

void TestSettingsView::test_matchesViewerLineColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettingsView::test_matchesViewerLineColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setMatchesViewerLineColor(value);
  QCOMPARE(result, this->matchesViewerLineColor());
}

void TestSettingsView::test_matchesViewerLineColorChange()
{
  QSignalSpy spy_matchesViewerLineColorChange(this, &SettingsView::matchesViewerLineColorChange);

  this->mLineEditMatchesViewerLineColor->setText("#253612");

  QCOMPARE(spy_matchesViewerLineColorChange.count(), 1);

  QList<QVariant> args = spy_matchesViewerLineColorChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "#253612");

  this->setMatchesViewerLineColor("FF00FF");
  QCOMPARE(spy_matchesViewerLineColorChange.count(), 0);
}

void TestSettingsView::test_matchesViewerLineWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("Out of range value") << 51 << 50;
}

void TestSettingsView::test_matchesViewerLineWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setMatchesViewerLineWidth(value);
  QCOMPARE(result, this->matchesViewerLineWidth());
}

void TestSettingsView::test_matchesViewerLineWidthChange()
{
  QSignalSpy spy_matchesViewerLineWidthChange(this, &SettingsView::matchesViewerLineWidthChange);

  this->mSpinBoxMatchesViewerLineWidth->setValue(5);

  QCOMPARE(spy_matchesViewerLineWidthChange.count(), 1);

  QList<QVariant> args = spy_matchesViewerLineWidthChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5);

  this->setMatchesViewerLineWidth(3);
  QCOMPARE(spy_matchesViewerLineWidthChange.count(), 0);
}

void TestSettingsView::test_groundTruthEditorBGColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettingsView::test_groundTruthEditorBGColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setGroundTruthEditorBGColor(value);
  QCOMPARE(result, this->groundTruthEditorBGColor());
}

void TestSettingsView::test_groundTruthEditorBGColorChange()
{
  QSignalSpy spy_groundTruthEditorBGColorChange(this, &SettingsView::groundTruthEditorBGColorChange);

  this->mLineEditGroundTruthEditorBGColor->setText("#253612");

  QCOMPARE(spy_groundTruthEditorBGColorChange.count(), 1);

  QList<QVariant> args = spy_groundTruthEditorBGColorChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "#253612");

  this->setGroundTruthEditorBGColor("FF00FF");
  QCOMPARE(spy_groundTruthEditorBGColorChange.count(), 0);
}

void TestSettingsView::test_groundTruthEditorMarkerSize_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("Out of range value") << 101 << 100;
}

void TestSettingsView::test_groundTruthEditorMarkerSize()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setGroundTruthEditorMarkerSize(value);
  QCOMPARE(result, this->groundTruthEditorMarkerSize());
}

void TestSettingsView::test_groundTruthEditorMarkerSizeChange()
{
  QSignalSpy spy_groundTruthEditorMarkerSizeChange(this, &SettingsView::groundTruthEditorMarkerSizeChange);

  this->mSpinBoxGroundTruthEditorMarkerSize->setValue(30);

  QCOMPARE(spy_groundTruthEditorMarkerSizeChange.count(), 1);

  QList<QVariant> args = spy_groundTruthEditorMarkerSizeChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 30);

  this->setGroundTruthEditorMarkerSize(20);
  QCOMPARE(spy_groundTruthEditorMarkerSizeChange.count(), 0);
}

void TestSettingsView::test_groundTruthEditorMarkerWidth_data()
{
  QTest::addColumn<int>("value");
  QTest::addColumn<int>("result");

  QTest::newRow("1") << 1 << 1;
  QTest::newRow("5") << 5 << 5;
  QTest::newRow("20") << 20 << 20;
  QTest::newRow("Out of range value") << 51 << 50;
}

void TestSettingsView::test_groundTruthEditorMarkerWidth()
{
  QFETCH(int, value);
  QFETCH(int, result);

  this->setGroundTruthEditorMarkerWidth(value);
  QCOMPARE(result, this->groundTruthEditorMarkerWidth());
}

void TestSettingsView::test_groundTruthEditorMarkerWidthChange()
{
  QSignalSpy spy_groundTruthEditorMarkerWidthChange(this, &SettingsView::groundTruthEditorMarkerWidthChange);

  this->mSpinBoxGroundTruthEditorMarkerWidth->setValue(5);

  QCOMPARE(spy_groundTruthEditorMarkerWidthChange.count(), 1);

  QList<QVariant> args = spy_groundTruthEditorMarkerWidthChange.takeFirst();
  QCOMPARE(args.at(0).toInt(), 5);

  this->setGroundTruthEditorMarkerWidth(3);
  QCOMPARE(spy_groundTruthEditorMarkerWidthChange.count(), 0);
}

void TestSettingsView::test_groundTruthEditorMarkerColor_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("#FF00FF") << "#FF00FF" << "#FF00FF";
  QTest::newRow("#253612") << "#253612" << "#253612";
  QTest::newRow("#205060") << "#205060" << "#205060";
}

void TestSettingsView::test_groundTruthEditorMarkerColor()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setGroundTruthEditorMarkerColor(value);
  QCOMPARE(result, this->groundTruthEditorMarkerColor());
}

void TestSettingsView::test_groundTruthEditorMarkerColorChange()
{
  QSignalSpy spy_groundTruthEditorMarkerColorChange(this, &SettingsView::groundTruthEditorMarkerColorChange);

  this->mLineEditGroundTruthEditorMarkerColor->setText("#253612");

  QCOMPARE(spy_groundTruthEditorMarkerColorChange.count(), 1);

  QList<QVariant> args = spy_groundTruthEditorMarkerColorChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "#253612");

  this->setGroundTruthEditorMarkerColor("FF00FF");
  QCOMPARE(spy_groundTruthEditorMarkerColorChange.count(), 0);
}

void TestSettingsView::test_dialogButtonBox()
{
  QSignalSpy spy_rejected(this, &SettingsView::rejected);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Cancel), Qt::LeftButton);
  QCOMPARE(spy_rejected.count(), 1);

  QSignalSpy spy_accepted(this, &SettingsView::accepted);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Ok), Qt::LeftButton);
  QCOMPARE(spy_accepted.count(), 1);

  QSignalSpy spy_applyChanges(this, &SettingsView::applyChanges);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Apply), Qt::LeftButton);
  QCOMPARE(spy_applyChanges.count(), 0);
  this->setUnsavedChanges(true); //Para activarlo
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Apply), Qt::LeftButton);
  QCOMPARE(spy_applyChanges.count(), 1);

  QSignalSpy spy_help(this, &SettingsView::help);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Help), Qt::LeftButton);
  QCOMPARE(spy_help.count(), 1);
}

void TestSettingsView::test_setUnsavedChanges()
{
  this->setUnsavedChanges(true);
  QCOMPARE(true, mButtonBox->button(QDialogButtonBox::Apply)->isEnabled());

  this->setUnsavedChanges(false);
  QCOMPARE(false, mButtonBox->button(QDialogButtonBox::Apply)->isEnabled());
}

void TestSettingsView::test_onFeatureDetectorDescriptorChange()
{
  ///TODO: completar test
}

void TestSettingsView::test_addFeatureDetectorMethod()
{
  ///TODO: completar test
}

void TestSettingsView::test_onPreprocessChange()
{
  ///TODO: completar test
}

void TestSettingsView::test_addPreprocess()
{
  ///TODO: completar test
}

QTEST_MAIN(TestSettingsView)

#include "tst_settingsview.moc"

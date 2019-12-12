#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/ExportFeaturesView.h"

#include <QPushButton>
#include <QDialogButtonBox>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QCheckBox>

using namespace photomatch;

class TestExportFeaturesView
  : public ExportFeaturesView
{
  Q_OBJECT

public:

  TestExportFeaturesView();
  ~TestExportFeaturesView();

private slots:

  void initTestCase();
  void cleanupTestCase();

  void test_constructor();
  void test_sessions();
  void test_activeSession_data();
  void test_activeSession();
  void test_sessionChange();
  void test_formats();
  void test_currentFormat_data();
  void test_currentFormat();
  void test_formatChange();
  void test_exportFiles();
  void test_exportPath_data();
  void test_exportPath();
  void test_exportPath_keyClick();
  void test_exportAll();
  void test_imageFiles();
  void test_dialogButtonBox();
  void test_clear();

private:

  QStringList sessions;
  QStringList images;
  QStringList formats;
};

TestExportFeaturesView::TestExportFeaturesView()
  : ExportFeaturesView()
{
  QApplication::setActiveWindow(this);
}

TestExportFeaturesView::~TestExportFeaturesView()
{
}

void TestExportFeaturesView::initTestCase()
{
  sessions.push_back("Session01");
  sessions.push_back("Session02");
  sessions.push_back("Session03");
  this->setSessions(sessions);

  formats.push_back("OpenCV XML");
  formats.push_back("OpenCV YML");
  formats.push_back("Plain text");
  this->setFormats(formats);

  images.push_back("C:/images/image1.jpg");
  images.push_back("C:/images/image2.jpg");
  images.push_back("C:/images/image3.jpg");
  images.push_back("C:/images/image4.jpg");
  images.push_back("C:/images/image5.jpg");
  this->setImageFiles(images);
}

void TestExportFeaturesView::cleanupTestCase()
{

}

void TestExportFeaturesView::test_constructor()
{
  ExportFeaturesView exportFeaturesView;
  QCOMPARE(QString(), exportFeaturesView.format());
  QCOMPARE(QStringList(), exportFeaturesView.exportFiles());
  QCOMPARE(QString(), exportFeaturesView.exportPath());
  QCOMPARE(true, exportFeaturesView.exportAll());

  QCOMPARE(QString("OpenCV XML"), this->format());
  QCOMPARE(QString("OpenCV XML"), this->mComboBoxFormat->currentText());
  QCOMPARE(5, this->exportFiles().size());
  QCOMPARE(5, this->mListWidgetfeatures->selectedItems().size());
  QCOMPARE(QString(), this->exportPath());
  QCOMPARE(QString(), this->mLineEditExportPath->text());
  QCOMPARE(true, this->exportAll());
  QCOMPARE(true, this->mCheckBoxExportAll->isChecked());
}

void TestExportFeaturesView::test_sessions()
{
  QCOMPARE(3, this->mComboBoxSession->count());
  QCOMPARE("Session01", this->mComboBoxSession->itemText(0));
  QCOMPARE("Session02", this->mComboBoxSession->itemText(1));
  QCOMPARE("Session03", this->mComboBoxSession->itemText(2));
}

void TestExportFeaturesView::test_activeSession_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("Session01") << "Session01" << "Session01";
  QTest::newRow("Session02") << "Session02" << "Session02";
  QTest::newRow("Session03") << "Session03" << "Session03";
}

void TestExportFeaturesView::test_activeSession()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setActiveSession(value);
  QCOMPARE(result, this->mComboBoxSession->currentText());
}

void TestExportFeaturesView::test_sessionChange()
{
QSignalSpy spy_sessionChange(this, &ExportFeaturesView::sessionChange);

  this->mComboBoxSession->setCurrentText("Session02");

  QCOMPARE(spy_sessionChange.count(), 1);

  QList<QVariant> args = spy_sessionChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "Session02");

  this->setActiveSession("Session03");
  QCOMPARE(spy_sessionChange.count(), 0);
}

void TestExportFeaturesView::test_formats()
{
  QCOMPARE(3, this->mComboBoxFormat->count());
  QCOMPARE("OpenCV XML", this->mComboBoxFormat->itemText(0));
  QCOMPARE("OpenCV YML", this->mComboBoxFormat->itemText(1));
  QCOMPARE("Plain text", this->mComboBoxFormat->itemText(2));
}

void TestExportFeaturesView::test_currentFormat_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("OpenCV XML") << "OpenCV XML" << "OpenCV XML";
  QTest::newRow("OpenCV YML") << "OpenCV YML" << "OpenCV YML";
  QTest::newRow("Plain text") << "Plain text" << "Plain text";
}

void TestExportFeaturesView::test_currentFormat()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setCurrentFormat(value);
  QCOMPARE(result, this->format());
  QCOMPARE(result, this->mComboBoxFormat->currentText());
}

void TestExportFeaturesView::test_formatChange()
{
  QSignalSpy spy_formatChange(this, &ExportFeaturesView::formatChange);

  this->mComboBoxFormat->setCurrentText("OpenCV YML");

  QCOMPARE(spy_formatChange.count(), 1);

  QList<QVariant> args = spy_formatChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "OpenCV YML");

  this->setCurrentFormat("OpenCV XML");
  QCOMPARE(spy_formatChange.count(), 0);
}

void TestExportFeaturesView::test_exportFiles()
{
  QCOMPARE(5, this->exportFiles().size());

  this->setExportAll(false);

  QCOMPARE(5, this->exportFiles().size());

  mListWidgetfeatures->clearSelection();

  QCOMPARE(0, this->exportFiles().size());

  mListWidgetfeatures->item(0)->setSelected(true);

  QCOMPARE(1, this->exportFiles().size());

  this->setExportAll(true);

  QCOMPARE(5, this->exportFiles().size());


}

void TestExportFeaturesView::test_exportPath_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("C:/Users/Tido/Documents/photomatch/Projects")
             << "C:/Users/Tido/Documents/photomatch/Projects"
             << "C:/Users/Tido/Documents/photomatch/Projects";
  QTest::newRow("C:/Users/user1/Documents/photomatch/Projects")
             << "C:/Users/user1/Documents/photomatch/Projects"
             << "C:/Users/user1/Documents/photomatch/Projects";

}

void TestExportFeaturesView::test_exportPath()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setExportPath(value);
  QCOMPARE(result, this->exportPath());
}

void TestExportFeaturesView::test_exportPath_keyClick()
{
  /// Simulación de entrada por teclado

  QString exportPath = this->exportPath();

  QTest::keyClick(this->mLineEditExportPath, '_');
  QCOMPARE(this->exportPath(), exportPath.append("_"));

  this->mLineEditExportPath->clear();
  QTest::keyClicks(this->mLineEditExportPath, "C:/Users/user1/Documents/photomatch/Projects");
  QCOMPARE(this->exportPath(), QString("C:/Users/user1/Documents/photomatch/Projects"));

}

void TestExportFeaturesView::test_exportAll()
{
  this->setExportAll(false);
  QCOMPARE(false, this->exportAll());
  QCOMPARE(false, this->mCheckBoxExportAll->isChecked());

  this->setExportAll(true);
  QCOMPARE(true, this->exportAll());
  QCOMPARE(true, this->mCheckBoxExportAll->isChecked());
}

void TestExportFeaturesView::test_imageFiles()
{

}

void TestExportFeaturesView::test_dialogButtonBox()
{

  QSignalSpy spy_rejected(this, &ExportFeaturesView::rejected);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Cancel), Qt::LeftButton);
  QCOMPARE(spy_rejected.count(), 1);

  mButtonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
  QSignalSpy spy_accepted(this, &ExportFeaturesView::accepted);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Ok), Qt::LeftButton);
  QCOMPARE(spy_accepted.count(), 1);

  QSignalSpy spy_help(this, &ExportFeaturesView::help);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Help), Qt::LeftButton);
  QCOMPARE(spy_help.count(), 1);
}

void TestExportFeaturesView::test_clear()
{
  this->clear();

  QCOMPARE(QString(), this->format());
  QCOMPARE(QString(), this->mComboBoxFormat->currentText());
  QCOMPARE(0, this->exportFiles().size());
  QCOMPARE(0, this->mListWidgetfeatures->selectedItems().size());
  QCOMPARE(QString(), this->exportPath());
  QCOMPARE(QString(), this->mLineEditExportPath->text());
  QCOMPARE(true, this->exportAll());
  QCOMPARE(true, this->mCheckBoxExportAll->isChecked());

  /// Recupero la configuración ya que se llama a test_clear antes de finalizar todos los test
  this->setSessions(sessions);
  this->setFormats(formats);
  this->setImageFiles(images);
}

QTEST_MAIN(TestExportFeaturesView)

#include "tst_exportfeaturesview.moc"

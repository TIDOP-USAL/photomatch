#include <QtTest>
#include <QCoreApplication>

#include "fme/ui/SettingsView.h"

#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>

using namespace fme;

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
  void test_dialogButtonBox();
  void test_setUnsavedChanges();

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

QTEST_MAIN(TestSettingsView)

#include "tst_settingsview.moc"

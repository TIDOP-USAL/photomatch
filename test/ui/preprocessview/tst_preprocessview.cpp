#include <QtTest>
#include <QCoreApplication>

#include "photomatch/ui/preprocess/PreprocessView.h"

#include "photomatch/widgets/AcebsfWidget.h"
#include "photomatch/widgets/ClaheWidget.h"
#include "photomatch/widgets/CmbfheWidget.h"
#include "photomatch/widgets/CmbfheWidget.h"
#include "photomatch/widgets/DheWidget.h"
#include "photomatch/widgets/FaheWidget.h"
#include "photomatch/widgets/HmclaheWidget.h"
#include "photomatch/widgets/LceBsescsWidget.h"
#include "photomatch/widgets/MsrcpWidget.h"
#include "photomatch/widgets/NoshpWidget.h"
#include "photomatch/widgets/PoheWidget.h"
#include "photomatch/widgets/RswheWidget.h"
#include "photomatch/widgets/WallisWidget.h"

#include <QComboBox>
#include <QPushButton>
#include <QDialogButtonBox>

using namespace photomatch;

class TestPreprocessView : public PreprocessViewImp
{
  Q_OBJECT

public:

  TestPreprocessView();
  ~TestPreprocessView();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_dialogButtonBox();
  void test_preprocessChange();
  void test_sessionName();
  void test_addPreprocess();
  void test_currentPreprocess_data();
  void test_currentPreprocess();
  void test_maxImageSize();
  void test_isFullImageSize();

private:

  AcebsfWidget *mACEBS;
  ClaheWidget *mCLAHE;
  CmbfheWidget *mCMBFHE;
  DheWidget *mDHE;
  FaheWidget *mFAHE;
  HmclaheWidget *mHMCLAHE;
  LceBsescsWidget *mLCEBSESCS;
  MsrcpWidget *mMSRCP;
  NoshpWidget *mNOSHP;
  PoheWidget *mPOHE;
  RswheWidget *mRSWHE;
  WallisWidget *mWallis;
};

TestPreprocessView::TestPreprocessView()
  : PreprocessViewImp(),
    mACEBS(new AcebsfWidgetImp),
    mCLAHE(new ClaheWidgetImp),
    mCMBFHE(new CmbfheWidgetImp),
    mDHE(new DheWidgetImp),
    mFAHE(new FaheWidgetImp),
    mHMCLAHE(new HmclaheWidgetImp),
    mLCEBSESCS(new LceBsescsWidgetImp),
    mMSRCP(new MsrcpWidgetImp),
    mNOSHP(new NoshpWidgetImp),
    mPOHE(new PoheWidgetImp),
    mRSWHE(new RswheWidgetImp),
    mWallis(new WallisWidgetImp)
{
  QApplication::setActiveWindow(this);
}

TestPreprocessView::~TestPreprocessView()
{
  if (mACEBS){
    delete mACEBS;
    mACEBS = nullptr;
  }
  if (mCLAHE){
    delete mCLAHE;
    mCLAHE = nullptr;
  }
  if (mCMBFHE){
    delete mCMBFHE;
    mCMBFHE = nullptr;
  }
  if (mDHE){
    delete mDHE;
    mDHE = nullptr;
  }
  if (mFAHE){
    delete mFAHE;
    mFAHE = nullptr;
  }
  if (mHMCLAHE){
    delete mHMCLAHE;
    mHMCLAHE = nullptr;
  }
  if (mLCEBSESCS){
    delete mLCEBSESCS;
    mLCEBSESCS = nullptr;
  }
  if (mMSRCP){
    delete mMSRCP;
    mMSRCP = nullptr;
  }
  if (mNOSHP){
    delete mNOSHP;
    mNOSHP = nullptr;
  }
  if (mPOHE){
    delete mPOHE;
    mPOHE = nullptr;
  }
  if (mRSWHE){
    delete mRSWHE;
    mRSWHE = nullptr;
  }
  if (mWallis){
    delete mWallis;
    mWallis = nullptr;
  }
}

void TestPreprocessView::initTestCase()
{
  this->addPreprocess(mACEBS);
  this->addPreprocess(mCLAHE);
  this->addPreprocess(mCMBFHE);
  this->addPreprocess(mDHE);
  this->addPreprocess(mFAHE);
  this->addPreprocess(mHMCLAHE);
  this->addPreprocess(mLCEBSESCS);
  this->addPreprocess(mMSRCP);
  this->addPreprocess(mNOSHP);
  this->addPreprocess(mPOHE);
  this->addPreprocess(mRSWHE);
  this->addPreprocess(mWallis);
  this->setCurrentPreprocess(mACEBS->windowTitle());
}

void TestPreprocessView::cleanupTestCase()
{

}

void TestPreprocessView::test_dialogButtonBox()
{
  QSignalSpy spy_rejected(this, &PreprocessViewImp::rejected);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Cancel), Qt::LeftButton);
  QCOMPARE(spy_rejected.count(), 1);

  QSignalSpy spy_applyChanges(this, &PreprocessViewImp::run);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Apply), Qt::LeftButton);
  QCOMPARE(spy_applyChanges.count(), 1);

  QSignalSpy spy_help(this, &PreprocessViewImp::help);
  QTest::mouseClick(mButtonBox->button(QDialogButtonBox::Help), Qt::LeftButton);
  QCOMPARE(spy_help.count(), 1);
}

void TestPreprocessView::test_preprocessChange()
{
  QSignalSpy spy_preprocessChange(this, &PreprocessViewImp::preprocessChange);

  this->mComboBoxPreprocess->setCurrentText("CLAHE");

  QCOMPARE(spy_preprocessChange.count(), 1);
  QList<QVariant> args = spy_preprocessChange.takeFirst();
  QCOMPARE(args.at(0).toString(), "CLAHE");

  this->mComboBoxPreprocess->setCurrentText("CLAHE");
  QCOMPARE(spy_preprocessChange.count(), 0);

  this->setCurrentPreprocess("RSWHE");
  QCOMPARE(spy_preprocessChange.count(), 0);
}

void TestPreprocessView::test_sessionName()
{
  this->setSessionName("Session01");
  QCOMPARE("Preprocess Session01", this->windowTitle());
}

void TestPreprocessView::test_addPreprocess()
{
  ///Se añade en initTestCase. Se comprueba que se hayan añadido correctamente
  QCOMPARE(12, this->mComboBoxPreprocess->count());
}

void TestPreprocessView::test_currentPreprocess_data()
{
  QTest::addColumn<QString>("value");
  QTest::addColumn<QString>("result");

  QTest::newRow("ACEBS") << "ACEBS" << "ACEBS";
  QTest::newRow("CLAHE") << "CLAHE" << "CLAHE";
  QTest::newRow("CMBFHE") << "CMBFHE" << "CMBFHE";
  QTest::newRow("DHE") << "DHE" << "DHE";
  QTest::newRow("FAHE") << "FAHE" << "FAHE";
  QTest::newRow("HMCLAHE") << "HMCLAHE" << "HMCLAHE";
  QTest::newRow("LCEBSESCS") << "LCEBSESCS" << "LCEBSESCS";
  QTest::newRow("MSRCP") << "MSRCP" << "MSRCP";
  QTest::newRow("NOSHP") << "NOSHP" << "NOSHP";
  QTest::newRow("POHE") << "POHE" << "POHE";
  QTest::newRow("RSWHE") << "RSWHE" << "RSWHE";
  QTest::newRow("Wallis") << "Wallis" << "Wallis";
}

void TestPreprocessView::test_currentPreprocess()
{
  QFETCH(QString, value);
  QFETCH(QString, result);

  this->setCurrentPreprocess(value);

  QCOMPARE(result, this->currentPreprocess());
}

void TestPreprocessView::test_maxImageSize()
{
  this->setMaxImageSize(3500);
  QCOMPARE(3500, this->maxImageSize());
}

void TestPreprocessView::test_isFullImageSize()
{
  this->setFullImageSize(true);
  QCOMPARE(true, this->fullImageSize());
}

QTEST_MAIN(TestPreprocessView)

#include "tst_preprocessview.moc"

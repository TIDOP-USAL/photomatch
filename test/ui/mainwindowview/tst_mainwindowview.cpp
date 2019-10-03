#include <QtTest>
#include <QCoreApplication>

#include "fme/ui/MainWindowView.h"
#include "fme/widgets/ThumbnailsWidget.h"

#include <QTreeWidgetItem>
#include <QAction>

//#include "ui_MainWindowView.h"

using namespace fme;

class TestMainWindowView
  : public MainWindowView
{
  Q_OBJECT

public:

  TestMainWindowView();
  ~TestMainWindowView();

private slots:

  void initTestCase();
  void cleanupTestCase();
  void test_setProjectTitle();
  void test_setFlag();
  void test_clear();
  void test_updateHistory();
  void test_deleteHistory();

  ///TODO: addSession
  void test_addSession();

// signals:

  /* Menu File */

  void test_openNew();
  void test_openProject();
  void test_openFromHistory();
  void test_clearHistory();
  void test_saveProject();
  void test_saveProjectAs();
  void test_closeProject();
  void test_exit();

  /* Menú herramientas */

  void test_loadImages();
  void test_newProcessing();
  void test_openPreprocess();
  void test_openFeatureExtraction();
  void test_openFeatureMatching();
  void test_openSettings();

  /* Menú Ayuda */

  void test_openHelpDialog();
  void test_openAboutDialog();

  /* Panel de vistas en miniatura */

  void test_openImage();
  void test_selectImage();
  void test_selectImages();
  void test_deleteImages();
  void test_deleteImage();
};

TestMainWindowView::TestMainWindowView()
  : MainWindowView()
{

}

TestMainWindowView::~TestMainWindowView()
{

}

void TestMainWindowView::initTestCase()
{
  QStringList history{
    QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba1\\Prueba1.xml"),
    QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba2\\Prueba2.xml"),
    QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba3\\Prueba3.xml")
  };
  this->updateHistory(history);

  /// Se simula la carga de un proyecto
  this->setProjectTitle("Example");
  setFlag(MainWindowView::Flag::project_exists, true);
  QStringList images {"C:\\img01.jpg", "C:\\img02.jpg"};
  addImages(images);

  //setActiveImage("C:\\img01.jpg");

  this->addSession("session01", "Session 1");
  this->setActiveSession("session01");
}

void TestMainWindowView::cleanupTestCase()
{

}

void TestMainWindowView::test_setProjectTitle()
{
  this->setProjectTitle("Example");
  QCOMPARE("FME - Example", this->windowTitle());
  QTreeWidgetItem *itemProject = mTreeWidgetProject->topLevelItem(0);
  QCOMPARE("Project: Example", itemProject->text(0));
}

void TestMainWindowView::test_setFlag()
{
  setFlag(MainWindowView::Flag::project_exists, true);
  QCOMPARE(true, mActionNewProject->isEnabled());
  QCOMPARE(true, mActionOpenProject->isEnabled());
  QCOMPARE(false, mActionSaveProject->isEnabled());
  QCOMPARE(true, mActionSaveProjectAs->isEnabled());
  QCOMPARE(true, mActionCloseProject->isEnabled());
  QCOMPARE(true, mActionExit->isEnabled());
  QCOMPARE(true, mActionStartPage->isEnabled());
  QCOMPARE(true, mActionLoadImages->isEnabled());
  QCOMPARE(false, mActionNewSession->isEnabled());
  QCOMPARE(false, mActionPreprocess->isEnabled());
  QCOMPARE(false, mActionFeatureExtraction->isEnabled());
  QCOMPARE(false, mActionFeatureMatching->isEnabled());
  QCOMPARE(true, mActionSettings->isEnabled());
  QCOMPARE(true, mActionHelp->isEnabled());
  QCOMPARE(true, mActionAbout->isEnabled());
  QCOMPARE(false, mActionExportTiePointsCvXml->isEnabled());
  QCOMPARE(false, mActionExportTiePointsCvYml->isEnabled());
  QCOMPARE(false, mActionExportMatchesToCvXml->isEnabled());
  QCOMPARE(false, mActionExportMatchesToCvYml->isEnabled());
  QCOMPARE(false, mActionExportMatchesToTxt->isEnabled());
  QCOMPARE(false, mActionMatchesViewer->isEnabled());
  QCOMPARE(false, mActionCreateGroundTruth->isEnabled());
  QCOMPARE(false, mActionImportGroundTruth->isEnabled());
  QCOMPARE(false, mActionHomography->isEnabled());
  QCOMPARE(false, mActionRepeteability->isEnabled());
  QCOMPARE(false, mActionPRCurves->isEnabled());
  QCOMPARE(false, mActionROCCurves->isEnabled());

  /// Projecto modificado
  setFlag(MainWindowView::Flag::project_modified, true);
  QCOMPARE(true, mActionSaveProject->isEnabled());
  QCOMPARE(true, mActionSaveProjectAs->isEnabled());
  QCOMPARE(true, mActionCloseProject->isEnabled());
  QCOMPARE(true, mActionLoadImages->isEnabled());

  /// Imagenes añadidas
  setFlag(MainWindowView::Flag::images_added, true);
  QCOMPARE(true, mActionNewSession->isEnabled());
  QCOMPARE(true, mActionCreateGroundTruth->isEnabled());
  QCOMPARE(true, mActionImportGroundTruth->isEnabled());

  /// Procesamiento, sesion o test (no se muy bien como llamarlo todavía)
  setFlag(MainWindowView::Flag::session_created, true);
  QCOMPARE(true, mActionPreprocess->isEnabled());

  /// Preprocesado
  setFlag(MainWindowView::Flag::preprocess, true);
  QCOMPARE(true, mActionFeatureExtraction->isEnabled());

  /// Extracción de caracteristicas
  setFlag(MainWindowView::Flag::feature_extraction, true);
  QCOMPARE(true, mActionFeatureMatching->isEnabled());
  QCOMPARE(true, mActionExportTiePointsCvXml->isEnabled());
  QCOMPARE(true, mActionExportTiePointsCvYml->isEnabled());

  ///Matching
  setFlag(MainWindowView::Flag::feature_matching, true);
  QCOMPARE(true, mActionMatchesViewer->isEnabled());
  QCOMPARE(true, mActionHomography->isEnabled());
  QCOMPARE(true, mActionRepeteability->isEnabled());
  QCOMPARE(false, mActionPRCurves->isEnabled());
  QCOMPARE(false, mActionROCCurves->isEnabled());
  QCOMPARE(true, mActionExportMatchesToCvXml->isEnabled());
  QCOMPARE(true, mActionExportMatchesToCvYml->isEnabled());
  QCOMPARE(true, mActionExportMatchesToTxt->isEnabled());

  setFlag(MainWindowView::Flag::ground_truth, true);
  QCOMPARE(true, mActionPRCurves->isEnabled());
  QCOMPARE(true, mActionROCCurves->isEnabled());
}

void TestMainWindowView::test_clear()
{
  this->clear();
  QCOMPARE("FME", this->windowTitle());

  QCOMPARE(false, mFlags.isActive(Flag::project_exists));
  QCOMPARE(false, mFlags.isActive(Flag::project_exists));
  QCOMPARE(false, mFlags.isActive(Flag::project_modified));
  QCOMPARE(false, mFlags.isActive(Flag::images_added));
  QCOMPARE(false, mFlags.isActive(Flag::image_open));
  QCOMPARE(false, mFlags.isActive(Flag::session_created));
  QCOMPARE(false, mFlags.isActive(Flag::preprocess));
  QCOMPARE(false, mFlags.isActive(Flag::feature_extraction));
  QCOMPARE(false, mFlags.isActive(Flag::feature_matching));
}

void TestMainWindowView::test_updateHistory()
{
  QCOMPARE(3, mHistory.size());
  QCOMPARE(false, mActionNotRecentProjects->isVisible());
  QCOMPARE(true, mActionClearHistory->isEnabled());
  QCOMPARE(QString("&1 Prueba1.xml"), mHistory[0]->text());
  QCOMPARE(QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba1\\Prueba1.xml"), mHistory[0]->data());
  QCOMPARE(QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba1\\Prueba1.xml"), mHistory[0]->toolTip());
}

void TestMainWindowView::test_deleteHistory()
{
  this->deleteHistory();

  QCOMPARE(0, mHistory.size());
  QCOMPARE(true, mActionNotRecentProjects->isVisible());
  QCOMPARE(false, mActionClearHistory->isEnabled());

  /// Se recupera el historial para evitar problemas con otras pruebas
  QStringList history{
    QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba1\\Prueba1.xml"),
    QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba2\\Prueba2.xml"),
    QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba3\\Prueba3.xml")
  };
  this->updateHistory(history);

}

void TestMainWindowView::test_addSession()
{
  bool add_session = false;
  if (QTreeWidgetItem *itemProject = this->mTreeWidgetProject->topLevelItem(0)) {

    QTreeWidgetItem *itemSessions = nullptr;
    for (int i = 0; i < itemProject->childCount(); i++) {
      QTreeWidgetItem *temp = itemProject->child(i);
      if (temp->text(0).compare(tr("Sessions")) == 0) {
        itemSessions = itemProject->child(i);
        break;
      }
    }

    if (itemSessions != nullptr) {
      QTreeWidgetItem *temp = itemSessions->child(0);
      QCOMPARE("Session 1", temp->toolTip(0));
      QCOMPARE("session01", temp->text(0));
      QCOMPARE(true, temp->font(0).bold());
    }

  }
}

void TestMainWindowView::test_openNew()
{
  QSignalSpy spy_openNew(this, &MainWindowView::openNew);

  emit mActionNewProject->triggered(true);
  QCOMPARE(spy_openNew.count(), 1);
}

void TestMainWindowView::test_openProject()
{
  QSignalSpy spy_openProject(this, &MainWindowView::openProject);

  emit mActionOpenProject->triggered(true);
  QCOMPARE(spy_openProject.count(), 1);
}

void TestMainWindowView::test_openFromHistory()
{
  QSignalSpy spy_openProjectFromHistory(this, &MainWindowView::openProjectFromHistory);

  emit mHistory[0]->triggered(true);
  QCOMPARE(spy_openProjectFromHistory.count(), 1);
  QList<QVariant> args = spy_openProjectFromHistory.takeFirst();
  QCOMPARE(args.at(0).toString(), QString("C:\\Users\\Tido\\Documents\\fme\\Projects\\Prueba1\\Prueba1.xml"));
}

void TestMainWindowView::test_clearHistory()
{
  QSignalSpy spy_clearHistory(this, &MainWindowView::clearHistory);

  emit mActionClearHistory->triggered(true);
  QCOMPARE(spy_clearHistory.count(), 1);
}

void TestMainWindowView::test_saveProject()
{
  QSignalSpy spy_saveProject(this, &MainWindowView::saveProject);

  emit mActionSaveProject->triggered(true);
  QCOMPARE(spy_saveProject.count(), 1);
}

void TestMainWindowView::test_saveProjectAs()
{
  QSignalSpy spy_saveProjectAsy(this, &MainWindowView::saveProjectAs);

  emit mActionSaveProjectAs->triggered(true);
  QCOMPARE(spy_saveProjectAsy.count(), 1);
}

void TestMainWindowView::test_closeProject()
{
  QSignalSpy spy_closeProject(this, &MainWindowView::closeProject);

  emit mActionCloseProject->triggered(true);
  QCOMPARE(spy_closeProject.count(), 1);
}

void TestMainWindowView::test_exit()
{
  QSignalSpy spy_exit(this, &MainWindowView::exit);

  emit mActionExit->triggered(true);
  QCOMPARE(spy_exit.count(), 1);
}

void TestMainWindowView::test_loadImages()
{
  QSignalSpy spy_loadImages(this, &MainWindowView::loadImages);

  emit mActionLoadImages->triggered(true);
  QCOMPARE(spy_loadImages.count(), 1);
}

void TestMainWindowView::test_newProcessing()
{
  QSignalSpy spy_newProcessing(this, &MainWindowView::newSession);

  emit mActionNewSession->triggered(true);
  QCOMPARE(spy_newProcessing.count(), 1);
}

void TestMainWindowView::test_openPreprocess()
{
  QSignalSpy spy_openPreprocess(this, &MainWindowView::openPreprocess);

  emit mActionPreprocess->triggered(true);
  QCOMPARE(spy_openPreprocess.count(), 1);
}

void TestMainWindowView::test_openFeatureExtraction()
{
  QSignalSpy spy_openFeatureExtraction(this, &MainWindowView::openFeatureExtraction);

  emit mActionFeatureExtraction->triggered(true);
  QCOMPARE(spy_openFeatureExtraction.count(), 1);
}

void TestMainWindowView::test_openFeatureMatching()
{
  QSignalSpy spy_openFeatureMatching(this, &MainWindowView::openFeatureMatching);

  emit mActionFeatureMatching->triggered(true);
  QCOMPARE(spy_openFeatureMatching.count(), 1);
}

void TestMainWindowView::test_openSettings()
{
  QSignalSpy spy_openSettings(this, &MainWindowView::openSettings);

  emit mActionSettings->triggered(true);
  QCOMPARE(spy_openSettings.count(), 1);
}

void TestMainWindowView::test_openHelpDialog()
{
  QSignalSpy spy_openHelpDialog(this, &MainWindowView::openHelpDialog);

  emit mActionHelp->triggered(true);
  QCOMPARE(spy_openHelpDialog.count(), 1);
}

void TestMainWindowView::test_openAboutDialog()
{
  QSignalSpy spy_openAboutDialog(this, &MainWindowView::openAboutDialog);

  emit mActionAbout->triggered(true);
  QCOMPARE(spy_openAboutDialog.count(), 1);
}

void TestMainWindowView::test_openImage()
{
  QSignalSpy spy_openImage(this, &MainWindowView::openImage);
  emit mThumbnailsWidget->openImage("C:\\img01.jpg");
  QCOMPARE(spy_openImage.count(), 1);
  QList<QVariant> args = spy_openImage.takeFirst();
  QCOMPARE(args.at(0).toString(), QString("C:\\img01.jpg"));
}

void TestMainWindowView::test_selectImage()
{
  QSignalSpy spy_selectImage(this, &MainWindowView::selectImage);
  emit mThumbnailsWidget->selectImage("C:\\img01.jpg");
  QCOMPARE(spy_selectImage.count(), 1);
  QList<QVariant> args = spy_selectImage.takeFirst();
  QCOMPARE(args.at(0).toString(), QString("C:\\img01.jpg"));

  /// la señal selectImage es escuchada desde MainWindowPresenter y se
  /// establece la imagen activa mediante setImageActive
  setActiveImage("C:\\img02.jpg");
  QCOMPARE(spy_selectImage.count(), 0);
}

void TestMainWindowView::test_selectImages()
{

}

void TestMainWindowView::test_deleteImages()
{
  QSignalSpy spy_deleteImages(this, &MainWindowView::deleteImages);
  QStringList images {"C:\\img01.jpg", "C:\\img02.jpg"};
  emit mThumbnailsWidget->deleteImages(images);
  QCOMPARE(spy_deleteImages.count(), 1);
  QList<QVariant> args = spy_deleteImages.takeFirst();
  QCOMPARE(args.at(0).toStringList(), images);
}

void TestMainWindowView::test_deleteImage()
{

}

QTEST_MAIN(TestMainWindowView)

#include "tst_mainwindowview.moc"

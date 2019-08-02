#ifndef FME_MAINWINDOW_H
#define FME_MAINWINDOW_H

#include <QMainWindow>

#include <tidop/core/flags.h>

namespace Ui {
class MainWindowView;
}

class QTreeWidget;

namespace fme
{

class ThumbnailsWidget;
class LogWidget;

class MainWindowView
  : public QMainWindow
{
  Q_OBJECT

public:

  enum class Flag
  {
    project_exists        = (1 << 0),  // Existe un proyecto
    project_modified      = (1 << 1),  // Se ha modificado el proyecto
    images_added          = (1 << 2),  // Se han añadido fotogramas
    image_open            = (1 << 3),  // Hay una imagen abierta
    session_created       = (1 << 4),
    preprocess            = (1 << 5),
    feature_extraction    = (1 << 6),
    feature_matching      = (1 << 7)
  };

public:

  explicit MainWindowView(QWidget *parent = nullptr);
  ~MainWindowView() override;

  void clear();

  /*!
   * \brief Establece el nombre del proyecto
   * \param[in] title Titulo del proyecto
   */
  void setProjectTitle(const QString &title);

  void setFlag(Flag flag, bool value);
  void addImages(const QStringList &images);
  void setActiveImage(const QString &image);
  void setActiveImages(const QStringList &images);
  void addSession(const QString &sessionName, const QString &sessionDescription);

  /*!
   * \brief Añade un mensaje temporal en la barra de herramientas
   * \param msg Mensaje
   */
  void setStatusBarMsg(const QString &msg);

public slots:

  /*!
   * \brief Actualiza el historial de proyectos recientes
   * \param[in] history Listado con las rutas de los últimos proyectos
   */
  void updateHistory(const QStringList &history);

  /*!
   * \brief Borra el historial de proyectos recientes
   */
  void deleteHistory();

  /*!
   * \brief Elimina una imagen
   * \param[in] file
   */
  void deleteImage(const QString &file);

signals:

  /* Menu File */

  void openNew();
  void openProject();
  void openProjectFromHistory(QString);
  void clearHistory();
  void saveProject();
  void saveProjectAs();
  void closeProject();
  void exit();

  /* Menú herramientas */

  void loadImages();
  void newSession();
  void openAssistant();
  void openPreprocess();
  void openFeatureExtraction();
  void openFeatureMatching();
  void openSettings();

  /* Menú Ayuda */

  void openHelpDialog();
  void openAboutDialog();

  /* Panel de vistas en miniatura */

  void openImage(QString);
  void selectImage(QString);
  void selectImages(QStringList);
  void deleteImages(QStringList);

protected:

  void changeEvent(QEvent *e) override;

private slots:

  void update();
  void openFromHistory();
  void onSelectionChanged();

private:

  void init();

// QWidget interface

public:

  void closeEvent(QCloseEvent *event) override;


protected:

  QTreeWidget *mTreeWidgetProject;
  QAction *mActionNewProject;
  QAction *mActionOpenProject;
  QAction *mActionSaveProject;
  QAction *mActionSaveProjectAs;
  QAction *mActionCloseProject;
  QAction *mActionExit;
  QAction *mActionLoadImages;
  QAction *mActionNewSession;
  QAction *mActionAssistant;
  QAction *mActionPreprocess;
  QAction *mActionFeatureExtraction;
  QAction *mActionFeatureMatching;
  QAction *mActionSettings;
  QAction *mActionHelp;
  QAction *mActionAbout;
  QAction *mActionExportTiePoints;
  QAction *mActionMatchesViewer;
  QAction *mActionHomography;
  QAction *mActionRepeteability;
  QAction *mActionRecall;
  QAction *mActionNotRecentProjects;
  QAction *mActionClearHistory;
  QMenu *mMenuRecentProjects;
  ThumbnailsWidget *mThumbnailsWidget;
  LogWidget *mLogWidget;

  tl::EnumFlags<Flag> mFlags;
  std::vector<QAction*> mHistory;

private:

  Ui::MainWindowView *ui;
};

ALLOW_BITWISE_FLAG_OPERATIONS(MainWindowView::Flag)

} // namespace fme

#endif // FME_MAINWINDOW_H

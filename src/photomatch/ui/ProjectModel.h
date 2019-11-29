#ifndef PHOTOMATCH_PROJECT_MODEL_H
#define PHOTOMATCH_PROJECT_MODEL_H

#include <QObject>

#include "photomatch/core/project.h"
#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IProjectModel
  : public IModel/*,
    public IProject*/
{

  Q_OBJECT

public:

  IProjectModel(QObject *parent = nullptr) : IModel(parent) {}

  /*!
   * \brief Ruta del fichero de proyecto
   * \return
   */
  virtual QString path() const = 0;

  /*!
   * \brief Carga un proyecto
   * \param[in] file Fichero de proyecto
   */
  virtual void load(const QString &file) = 0;

  /*!
   * \brief Guarda el proyecto
   */
  virtual void save() = 0;

  /*!
   * \brief Guarda un proyecto como...
   * \param[in] file Nombre con el cual se guarda el proyecto
   */
  virtual void saveAs(const QString &file) = 0;

  /*!
   * \brief Comprueba si hay cambios sin guardar en el proyecto
   * \return
   */
  virtual bool checkUnsavedChanges() const = 0;

  /*!
   * \brief Comprueba si un proyecto es de una versión antigua
   * \param[in] file
   * \return
   */
  virtual bool checkOldVersion(const QString &file) const = 0;

  /*!
   * \brief Crea una copia de un proyecto antiguo con el mismo nombre y un sufijo con la versión
   * \param[in] file
   */
  virtual void oldVersionBak(const QString &file) const = 0;

  /*!
   * \brief Devuelve el nombre del proyecto
   * \return Nombre del proyecto
   */
  virtual QString name() const = 0;

  /*!
   * \brief Establece el nombre del proyecto
   * \param[in] name Nombre del proyecto
   */
  virtual void setName(const QString &name) = 0;

  /*!
   * \brief Devuelve la descripción del proyecto
   * \return Descripción del proyecto
   */
  virtual QString description() const = 0;

  /*!
   * \brief Establece la descripción del proyecto
   * \param[in] description Descripción del proyecto
   */
  virtual void setDescription(const QString &description) = 0;

  /*!
   * \brief Devuelve el directorio del proyecto
   * \return Directorio del proyecto
   */
  virtual QString projectFolder() const = 0;

  /*!
   * \brief Establece el directorio del proyecto
   * \param[in] path Directorio del proyecto
   */
  virtual void setProjectFolder(const QString &dir) = 0;

  /*!
   * \brief Versión del fichero de proyecto
   * La versión del fichero de proyecto se utiliza para actualizar proyectos antiguos
   * \return Versión del fichero de proyecto
   */
  virtual QString version() const = 0;

  virtual void setGroundTruth(const QString &groundTruth) = 0;

  virtual QString groundTruth() const = 0;

  /*!
   * \brief Añade una imagen al proyecto
   * \param[in] img Imagen
   */
  virtual void addImage(const std::shared_ptr<Image> &img) = 0;

  /*!
   * \brief Elimina una imagen del proyecto
   * \param[in] img Ruta de la imagen que se quiere eliminar
   */
  virtual void deleteImage(const QString &img) = 0;

  /*!
   * \brief Elimina una imagen del proyecto
   * \param[in] imgId Identificador de la imagen que se quiere eliminar
   */
  virtual void deleteImage(size_t imgId) = 0;

  /*!
   * \brief Busca una imagen en el proyecto
   * \param[in] path Ruta de la imagen a buscar
   * \return Objeto Image correspondiente o puntero nulo si no se encuentra
   */
  virtual const std::shared_ptr<Image> findImage(const QString &path) const = 0;

  virtual const std::shared_ptr<Image> findImageById(size_t id) const = 0;
  virtual const std::shared_ptr<Image> findImageByName(const QString &imgName) const = 0;

  /*!
   * \brief Busca una imagen en el proyecto
   * \param[in] path Ruta de la imagen a buscar
   * \return Objeto Identificador de la imagen o std::numeric_limits<size_t>().max() si no se encuentra.
   */
  virtual size_t findImageId(const QString &path) const = 0;

  /*!
   * \brief Devuelve un iterador constante al inicio del listado de imágenes
   * \return Iterador al primer elemento del listado de imágenes
   */
  virtual IProject::image_const_iterator imageBegin() const = 0;

  /*!
   * \brief Devuelve un iterador constante al siguiente elemento después de la última imagen
   * Este elemento actúa como un marcador de posición, intentar acceder a él resulta en un comportamiento no definido
   * \return Iterador constante al siguiente elemento después de la última imagen
   */
  virtual IProject::image_const_iterator imageEnd() const = 0;

  /*!
   * \brief Número de imagenes cargadas en el proyecto
   * \return
   */
  virtual size_t imagesCount() const = 0;

  virtual void addImages(const QStringList &fileNames) = 0;
  virtual void deleteImages(const QStringList &images) = 0;

  /*!
   * \brief Añade una sesión
   * \param[in] name Nombre de la sesión
   * \param[in] description Descripción de la sesión
   */
  virtual void addSession(const QString &name, const QString &description) = 0;

  /*!
   * \brief Añade una sesión
   * \param[in] session Sesión
   */
  virtual void addSession(const std::shared_ptr<Session> &session) = 0;

  /*!
   * \brief Borra una sesión
   * \param[in] nameSession Nombre de la sesión
   */
  virtual void deleteSession(const QString &nameSession) = 0;

  /*!
   * \brief Borra una sesión
   * \param[in] sessionId Identificador de la sesión
   */
  virtual void deleteSession(size_t sessionId) = 0;

  /*!
   * \brief Busca una sesión en el proyecto
   * \param[in] sessionName Nombre de la sesión
   * \return
   */
  virtual std::shared_ptr<Session> findSession(const QString &sessionName) = 0;

  /*!
   * \brief Busca una sesión en el proyecto
   * \param[in] sessionName Nombre de la sesión
   * \return
   */
  virtual const std::shared_ptr<Session> findSession(const QString &sessionName) const = 0;

  /*!
   * \brief Busca el identificador de una sesión en el proyecto
   * \param[in] sessionName Nombre de la sesión
   * \return
   */
  virtual size_t findSessionId(const QString &sessionName) = 0;

  /*!
   * \brief Busca el identificador de una sesión en el proyecto
   * \param[in] sessionName Nombre de la sesión
   * \return
   */
  virtual size_t findSessionId(const QString &sessionName) const = 0;

  /*!
   * \brief Devuelve un iterador constante al inicio del listado de sessiones
   * \return Iterador al primer elemento del listado de sessiones
   */
  virtual IProject::session_const_iterator sessionBegin() const = 0;

  /*!
   * \brief Devuelve un iterador constante al siguiente elemento después de la última sesión
   * Este elemento actúa como un marcador de posición, intentar acceder a él
   * resulta en un comportamiento no definido
   * \return Iterador constante al siguiente elemento después de la última sesión
   */
  virtual IProject::session_const_iterator sessionEnd() const = 0;

  /*!
   * \brief Número de sesiones del proyecto
   * \return
   */
  virtual size_t sessionCount() const = 0;

  virtual const std::shared_ptr<Session> currentSession() const = 0;
  virtual void setCurrentSession(const QString &sessionName) = 0;

  virtual void setPreprocess(const std::shared_ptr<Preprocess> &preprocess) = 0;
  virtual void deletePreprocess() = 0;
  virtual void setDetector(const std::shared_ptr<Feature> &detector) = 0;
  virtual void deleteDetector() = 0;
  virtual void setDescriptor(const std::shared_ptr<Feature> &descriptor) = 0;
  virtual void deleteDescriptor() = 0;
  virtual void setMatcher(const std::shared_ptr<Match> &descriptor) = 0;
  virtual void deleteMatcher() = 0;
  virtual void setRobustMatcherRefinement(const std::shared_ptr<IRobustMatcherRefinement> &robustMatcherRefinement) = 0;
  virtual int maxImageSize() const = 0;
  virtual void setMaxImageSize(int size) = 0;
  virtual bool fullImageSize() const = 0;
  virtual void setFullImageSize(bool fullImageSize) = 0;
  virtual void addPreprocessedImage(const QString &image) = 0;
  virtual void deletePreprocessedImage(const QString &image) = 0;
  virtual void clearPreprocessedImages() = 0;
  virtual void addFeatures(const QString &feat) = 0;
  virtual void deleteFeatures(const QString &feat) = 0;
  virtual void clearFeatures() = 0;
  virtual void addMatches(const QString &img1, const QString &img2, const QString &fileMatch) = 0;
  virtual void deleteMatches(const QString &img1, const QString &img2, const QString &fileMatch) = 0;
  virtual void clearMatches() = 0;

  /*!
   * \brief Limpia el proyecto
   */
  virtual void clear() = 0;

signals:

//  void nameChange(QString);
//  void descriptionChange(QString);
//  void projectFolderChange(QString);
//  void imageAdded(QString);
//  void imageDeleted(QString);
//  void imageDeleted(size_t);
//  void modifiedProject(bool);

};

class ProjectModel
  : public IProjectModel
{

  Q_OBJECT

public:

  explicit ProjectModel(IProjectRW *projectIO, IProject *project, QObject *parent = nullptr);
  ~ProjectModel() override;

signals:

public slots:

// IProject interface

public:

  QString name() const override;
  void setName(const QString &name) override;
  QString description() const override;
  void setDescription(const QString &description) override;
  QString projectFolder() const override;
  void setProjectFolder(const QString &dir) override;
  QString version() const override;
  QString groundTruth() const override;
  void setGroundTruth(const QString &groundTruth) override;
  void addImage(const std::shared_ptr<Image> &img) override;
  void deleteImage(const QString &img) override;
  void deleteImage(size_t imgId) override;
  const std::shared_ptr<Image> findImage(const QString &path) const override;
  const std::shared_ptr<Image> findImageById(size_t id) const override;
  const std::shared_ptr<Image> findImageByName(const QString &imgName) const override;
  size_t findImageId(const QString &path) const override;
  IProject::image_const_iterator imageBegin() const override;
  IProject::image_const_iterator imageEnd() const override;
  size_t imagesCount() const override;
  void addSession(const QString &name, const QString &description) override;
  void addSession(const std::shared_ptr<Session> &session) override;
  void deleteSession(const QString &nameSession) override;
  void deleteSession(size_t sessionId) override;
  std::shared_ptr<Session> findSession(const QString &sessionName) override;
  const std::shared_ptr<Session> findSession(const QString &sessionName) const override;
  size_t findSessionId(const QString &sessionName) override;
  size_t findSessionId(const QString &sessionName) const override;
  IProject::session_const_iterator sessionBegin() const override;
  IProject::session_const_iterator sessionEnd() const override;
  size_t sessionCount() const override;
  const std::shared_ptr<Session> currentSession() const override;
  void setCurrentSession(const QString &sessionName) override;
  void setPreprocess(const std::shared_ptr<Preprocess> &preprocess) override;
  void deletePreprocess() override;
  void setDetector(const std::shared_ptr<Feature> &detector) override;
  void deleteDetector() override;
  void setDescriptor(const std::shared_ptr<Feature> &descriptor) override;
  void deleteDescriptor() override;
  void setMatcher(const std::shared_ptr<Match> &matcher) override;
  void deleteMatcher() override;
  void setRobustMatcherRefinement(const std::shared_ptr<IRobustMatcherRefinement> &robustMatcherRefinement) override;
  int maxImageSize() const override;
  void setMaxImageSize(int size) override;
  bool fullImageSize() const override;
  void setFullImageSize(bool fullImageSize) override;
  void addPreprocessedImage(const QString &image) override;
  void deletePreprocessedImage(const QString &image) override;
  void clearPreprocessedImages() override;
  void addFeatures(const QString &feat) override;
  void deleteFeatures(const QString &feat) override;
  void clearFeatures() override;
  void addMatches(const QString &img1, const QString &img2, const QString &fileMatch) override;
  void deleteMatches(const QString &img1, const QString &img2, const QString &fileMatch) override;
  void clearMatches() override;

  void clear() override;

// IProjectModel interface

public:

  QString path() const override;
  void load(const QString &file) override;
  void save() override;
  void saveAs(const QString &file) override;
  bool checkUnsavedChanges() const override;
  bool checkOldVersion(const QString &file) const override;
  void oldVersionBak(const QString &file) const override;
  void addImages(const QStringList &fileNames) override;
  void deleteImages(const QStringList &images) override;

// IModel interface

private:

  void init() override;

protected:

  IProjectRW *mProjectIO;
  IProject *mProject;
  QString mPrjFile;
  bool bUnsavedChanges;

};

} // namespace photomatch

#endif // PHOTOMATCH_PROJECT_MODEL_H
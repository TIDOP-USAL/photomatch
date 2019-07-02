#ifndef FME_PROJECT_MODEL_H
#define FME_PROJECT_MODEL_H

#include <QObject>

#include "fme/core/project.h"
#include "fme/ui/mvp.h"

namespace fme
{

class IProjectModel
  : public IModel,
    public IProject
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
  void addImage(const std::shared_ptr<Image> &img) override;
  void deleteImage(const QString &img) override;
  void deleteImage(size_t imgId) override;
  std::shared_ptr<Image> findImage(const QString &path) override;
  const std::shared_ptr<Image> findImage(const QString &path) const override;
  size_t findImageId(const QString &path) override;
  size_t findImageId(const QString &path) const override;
  image_iterator imageBegin() override;
  image_const_iterator imageBegin() const override;
  image_iterator imageEnd() override;
  image_const_iterator imageEnd() const override;
  size_t imagesCount() const override;
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

// IModel interface

private:

  void init() override;

protected:

  IProjectRW *mProjectIO;
  IProject *mProject;
  QString mPrjFile;
  bool bUnsavedChanges;
};

} // namespace fme

#endif // FME_PROJECT_MODEL_H

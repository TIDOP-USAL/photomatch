#ifndef FME_PROJECT_MODEL_H
#define FME_PROJECT_MODEL_H

#include <QObject>

#include "fme/core/project.h"

namespace fme
{

///TODO: Interfaz IProjectModel que extienda de IProject
///      - ProjectModel hara composición de Project y ProjectIO
///      - Los metodos save, saveAs y load se quitaran de IProject
///      - bUnsavedChanges se quitará de Project y se movera a ProjectModel
///      - Cuando se establezca algún cambio en ProjectModel se emitira una señal

class IProjectModel
  : public IProject
{

public:

  IProjectModel() {}

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

};

class ProjectModel
  : public QObject
{

  Q_OBJECT

public:

  explicit ProjectModel(QObject *parent = nullptr);

signals:

public slots:

};

} // namespace fme

#endif // FME_PROJECT_MODEL_H

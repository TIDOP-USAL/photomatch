#ifndef FME_NEW_PROJECT_INTERFACES_H
#define FME_NEW_PROJECT_INTERFACES_H

#include "mvp.h"

#include <QString>

namespace fme
{

/*!
 * \brief The INewProjectPresenter class
 */
class INewProjectPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  INewProjectPresenter(){}

  virtual ~INewProjectPresenter() {}

signals:

  /*!
   * \brief Señal que se emite cuando se crea el proyecto
   */
  void projectCreate();
  
protected slots:

  /*!
   * \brief Guarda el proyecto
   */
  virtual void saveProject() = 0;

  /*!
   * \brief Descarta los cambios en el proyecto
   */
  virtual void discartProject() = 0;

};


/*!
 * \brief INewProjectView
 */
class INewProjectView
  : public IDialogView
{

  Q_OBJECT

public:

  INewProjectView(QWidget *parent) : IDialogView(parent) {}
  virtual ~INewProjectView() {}

  /*!
   * \brief Devuelve el nombre del proyecto
   * \return Nombre del proyecto
   */
  virtual QString projectName() const = 0;
  
  /*!
   * \brief Devuelve la ruta del proyecto
   * \return Ruta del proyecto
   */
  virtual QString projectPath() const = 0;
  
  /*!
   * \brief Establece la ruta del proyecto
   * \param path Ruta del proyecto
   */
  virtual void setProjectPath(const QString &path) = 0;

  /*!
   * \brief Devuelve la descripción del proyecto
   * \return Descripción del proyecto
   */
  virtual QString projectDescription() const = 0;

  virtual bool createProjectFolder() const = 0;  
  
protected slots:
  
  virtual void onClickButtonSelectPath() = 0;

};


} // End namespace fme

#endif // FME_NEW_PROJECT_INTERFACES_H

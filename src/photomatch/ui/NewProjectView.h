#ifndef PHOTOMATCH_NEW_PROJECT_VIEW_H
#define PHOTOMATCH_NEW_PROJECT_VIEW_H

#include "photomatch/ui/mvp.h"

class QLineEdit;
class QCheckBox;
class QDialogButtonBox;
class QTextEdit;
class QPushButton;

namespace photomatch
{

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

class NewProjectView 
  : public INewProjectView
{
  Q_OBJECT

public:

  explicit NewProjectView(QWidget *parent = nullptr);
  ~NewProjectView() override;

// INewProjectView interface

public:

  QString projectName() const override;
  QString projectPath() const override;
  void setProjectPath(const QString &path) override;
  QString projectDescription() const override;
  bool createProjectFolder() const override;

protected slots:

  void onClickButtonSelectPath() override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

protected:

  QLineEdit *mLineEditProjectName;
  QLineEdit *mLineEditProjectPath;
  QLineEdit *mLineEditProjectFile;
  QTextEdit *mTextEditDescription;
  QCheckBox *mCheckBoxProjectFolder;
  QPushButton *mPushButtonProjectPath;
  QDialogButtonBox *mButtonBox;

};

} // namespace photomatch


#endif // PHOTOMATCH_NEW_PROJECT_VIEW_H

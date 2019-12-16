#ifndef PHOTOMATCH_NEW_SESSION_PRESENTER_H
#define PHOTOMATCH_NEW_SESSION_PRESENTER_H

#include <memory>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class INewSessionView;
class IProjectModel;
class HelpDialog;

class INewSessionPresenter
  : public IPresenter
{
  Q_OBJECT

public:

  INewSessionPresenter() {}
  virtual ~INewSessionPresenter() {}

signals:

  /*!
   * \brief Señal que se emite cuando se crea la sesión
   */
  void sessionCreate(QString);

protected slots:

  /*!
   * \brief Guarda la sesión en el proyecto
   */
  virtual void saveProject() = 0;

  /*!
   * \brief Descarta los cambios en el proyecto
   */
  virtual void discartProject() = 0;

  /*!
   * \brief Comprueba si ya existe una sesión con el mismo nombre
   * \param[in] name Session name
   */
  virtual void checkSessionName(const QString &name) = 0;
};


class NewSessionPresenter
  : public INewSessionPresenter
{
  Q_OBJECT

public:

  NewSessionPresenter(INewSessionView *view, IProjectModel *model);
  ~NewSessionPresenter() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

// INewSessionPresenter interface

protected slots:

  void saveProject() override;
  void discartProject() override;
  void checkSessionName(const QString &name) override;

private:

  INewSessionView *mView;
  IProjectModel *mProjectModel;
  std::shared_ptr<HelpDialog> mHelp;
};

} // namespace photomatch

#endif // PHOTOMATCH_NEW_SESSION_PRESENTER_H

#ifndef FME_NEW_SESSION_VIEW_H
#define FME_NEW_SESSION_VIEW_H

#include "fme/ui/mvp.h"

class QLineEdit;
class QTextEdit;
class QDialogButtonBox;

namespace fme
{

class INewSessionView
  : public IDialogView
{

  Q_OBJECT

public:

  INewSessionView(QWidget *parent) : IDialogView(parent) {}
  virtual ~INewSessionView() override {}

  /*!
   * \brief Devuelve el nombre de la sesión
   * \return Nombre de la sesión
   */
  virtual QString sessionName() const = 0;

  /*!
   * \brief Devuelve la descripción de la sesión
   * \return Descripción de la sesión
   */
  virtual QString sessionDescription() const = 0;

  virtual void setExistingName(bool nameExist) = 0;

signals:

  void sessionNameChange(QString);
};

class NewSessionView
  : public INewSessionView
{
  Q_OBJECT

public:

  NewSessionView(QWidget *parent = nullptr);
  ~NewSessionView() override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

// INewSessionView interface

public:

  QString sessionName() const override;
  QString sessionDescription() const override;
  void setExistingName(bool nameExist) override;

protected:

  QLineEdit *mLineEditSessionName;
  QTextEdit *mTextEditSessionDescription;
  QDialogButtonBox *mButtonBox;
  bool bNameExist;
};

} // namespace fme

#endif // FME_NEW_SESSION_VIEW_H

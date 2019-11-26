#ifndef PHOTOMATCH_MVP_H
#define PHOTOMATCH_MVP_H

#include <QObject>
#include <QDialog>
#include <QEvent>

namespace photomatch
{

/*!
 * \brief Interfaz para las Vistas que sean QWidget
 */
class IWidgetView
  : public QWidget
{

  Q_OBJECT

public:

  IWidgetView(QWidget *parent)
    : QWidget(parent)
  {
  }

  virtual ~IWidgetView() override {}

private:

  /*!
   * \brief Inicialización del Widget
   */
  virtual void init() = 0;

public slots:

  /*!
   * \brief Limpia los campos  del Widget
   */
  virtual void clear() = 0;

private slots:

  /*!
   * \brief Actualización de los controles  del Widget
   */
  virtual void update() = 0;

  /*!
   * \brief Retranslate
   */
  virtual void retranslate() = 0;

// QWidget interface

protected:

  void changeEvent(QEvent *event) override
  {
    if (event->type() == QEvent::LanguageChange){
      retranslate();
    }
  }

};

/*!
 * \brief Interfaz para las Vistas que sean QDialog
 */
class IDialogView
  : public QDialog
{
  Q_OBJECT

public:

  IDialogView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
    : QDialog(parent, f)
  {
  }

  virtual ~IDialogView() override {}

private:

  /*!
   * \brief Inicialización del dialogo
   */
  virtual void init() = 0;

signals:

  void help();
  void restore();

public slots:

  /*!
   * \brief Limpia los campos  del dialogo
   */
  virtual void clear() = 0;

private slots:

  /*!
   * \brief Actualización de los controles  del dialogo
   */
  virtual void update() = 0;

  /*!
   * \brief Retranslate
   */
  virtual void retranslate() = 0;

// QWidget interface

protected:

  void changeEvent(QEvent *event) override
  {
    if (event->type() == QEvent::LanguageChange){
      retranslate();
    }
  }
};



class IModel
  : public QObject
{

  Q_OBJECT

public:

  IModel(QObject *parent = nullptr) : QObject(parent){}
  virtual ~IModel(){}

private:

  /*!
   * \brief Inicialización de la clase
   */
  virtual void init() = 0;

};


class IPresenter
  : public QObject
{
  Q_OBJECT

public:

  IPresenter() : QObject(){}
  virtual ~IPresenter(){}

public slots:

 /*!
  * \brief Muestra la ayuda de la herramienta
  */
  virtual void help() = 0;

 /*!
  * \brief Muestra la herramienta
  */
  virtual void open() = 0;

  //virtual void setHelp(std::shared_ptr<ui::Help> &help) = 0;

private:

  /*!
   * \brief Inicialización de la herramienta
   */
  virtual void init() = 0;

};

} // namespace photomatch

#endif // PHOTOMATCH_MVP_H

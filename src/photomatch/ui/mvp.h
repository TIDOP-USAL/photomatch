#ifndef PHOTOMATCH_MVP_H
#define PHOTOMATCH_MVP_H

#include <memory>

#include <QObject>
#include <QDialog>
#include <QEvent>

namespace photomatch
{

class HelpDialog;


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
   * \brief Widget Initialization
   */
  virtual void init() = 0;

public slots:

  /*!
   * \brief Clear the widget
   */
  virtual void clear() = 0;

private slots:

  virtual void update() = 0;
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


class IDialogView
  : public QDialog
{
  Q_OBJECT

public:

  IDialogView(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags())
    : QDialog(parent, f)
  {
    Qt::WindowFlags helpFlag = Qt::WindowContextHelpButtonHint;
    Qt::WindowFlags flags = windowFlags();
    flags = flags & (~helpFlag);
    setWindowFlags(flags);
  }

  virtual ~IDialogView() override = default;

private:

  /*!
   * \brief Dialog initialization
   */
  virtual void init() = 0;

signals:

  void help();
  void restore();

public slots:

  /*!
   * \brief Clear dialog
   */
  virtual void clear() = 0;

private slots:

  virtual void update() = 0;

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
   * \brief Class Initialization
   */
  virtual void init() = 0;

};


class IPresenter
  : public QObject
{
  Q_OBJECT

public:

  IPresenter() : QObject(){}
  virtual ~IPresenter() = default;

public slots:

 /*!
  * \brief Show help
  */
  virtual void help() = 0;

 /*!
  * \brief Open
  */
  virtual void open() = 0;

  /*!
   * \brief Set Help
   * \param[in] help
   */
  virtual void setHelp(std::shared_ptr<HelpDialog> &help) = 0;

private:

  /*!
   * \brief Class Initialization
   */
  virtual void init() = 0;

};

} // namespace photomatch

#endif // PHOTOMATCH_MVP_H

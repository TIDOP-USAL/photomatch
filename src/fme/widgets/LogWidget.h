#ifndef FME_LOG_WIDGET_H
#define FME_LOG_WIDGET_H

#include "fme/widgets/FmeWidget.h"

#include <mutex>

#include <tidop/core/defs.h>
#include <tidop/core/flags.h>
#include <tidop/core/messages.h>

class QDateTimeEdit;
class QListWidget;
class QGridLayout;

//namespace Ui {
//class WidgetLog;
//}

namespace fme
{

class FME_EXPORT LogWidget
  : public FmeWidget,
    public tl::MessageManager::Listener
{
  Q_OBJECT

public:

  explicit LogWidget(QWidget *parent = nullptr);
  ~LogWidget() override;

  /*!
   * \brief Filtra los mensajes mostrados en la ventana de log
   * \param level nivel de log
   */
  void filter(tl::MessageLevel level);

  void setLogLevel(tl::MessageLevel level);
  void print(const char *msg, const char *date, tl::MessageLevel level);
  void refresh();

public slots:

  virtual void clear();

  
private slots:

  void onPushButtonShowLogWarningToggled(bool active);
  void onPushButtonShowLogErrorsToggled(bool active);
  void onPushButtonShowLogInfoToggled(bool active);
  void onPushButtonShowLogDebugToggled(bool active);
  void onRowsInserted(const QModelIndex &parent,int start,int end,QPrivateSignal);
  void onRowsRemoved(const QModelIndex &parent,int start,int end,QPrivateSignal);

// FmeWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

// Listener interface

public:

  void onMsgDebug(const char *msg, const char *date) override;
  void onMsgInfo(const char *msg, const char *date) override;
  void onMsgWarning(const char *msg, const char *date) override;
  void onMsgError(const char *msg, const char *date) override;

private:

//  //Ui::WidgetLog *ui;

  static tl::EnumFlags<tl::MessageLevel> sLevel;
  static tl::EnumFlags<tl::MessageLevel> sFilterLevel;
  static std::mutex mtx;

  QGridLayout *mGridLayout;
  QListWidget *mListWidget;
  QAction* mMsgErrorAction;
  QAction* mMsgWarningAction;
  QAction* mMsgInfoAction;
  QAction* mClearAction;
  //QDateTimeEdit *mDateTimeEdit;

};

} // namespace fme

#endif // FME_LOG_WIDGET_H

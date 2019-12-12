#ifndef PHOTOMATCH_HELP_DIALOG_H
#define PHOTOMATCH_HELP_DIALOG_H

#include "mvp.h"

#include <QTextBrowser>

class QHelpEngine;

class HelpBrowser
  : public QTextBrowser
{

public:

  HelpBrowser(QHelpEngine *helpEngine, QWidget *parent = nullptr);

  QVariant loadResource (int type, const QUrl& name);


private:

  QHelpEngine *mHelpEngine;
};

//namespace Ui
//{
//class Help;
//}

namespace photomatch
{

class HelpDialog
  : public IDialogView
{

  Q_OBJECT

public:

  HelpDialog(QWidget *parent = nullptr,
             Qt::WindowFlags f = Qt::WindowFlags());
  ~HelpDialog() override;

 public slots:

 /*!
  * \brief navigateHome
  */
 void navigateHome();

  /*!
   * \brief setPage
   * \param page
   */
  void setPage(const QString &page);

private slots:

  /*!
   * \brief navigateBackward
   */
  void navigateBackward();
  
  /*!
   * \brief navigateForward
   */
  void navigateForward();

  /*!
   * \brief setContentSource
   * \param[in] index Índice de la página
   */
  void setContentSource(const QModelIndex &index);
  
  /*!
   * \brief setIndexSource
   * \param[in] index Índice de la página
   */
  void setIndexSource(const QModelIndex &index);
 
  /*!
   * \brief searchInvoked
   */
  void searchInvoked();

  /*!
   * \brief searchFinished
   * \param[in] hits
   */
  void searchFinished(int hits);

  // IDialogView interface
private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

private:

  //Ui::Help *ui;
  QHelpEngine *mHelpEngine;
  HelpBrowser *mHelpBrowser;
  QTextBrowser *mSearchResultsWidget;
  QAction *mNavigateForwardAction;
};

} // namespace photomatch


#endif // PHOTOMATCH_HELP_DIALOG_H

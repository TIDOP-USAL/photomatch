/************************************************************************
 *                                                                      *
 * Copyright 2020 by Tidop Research Group <daguilera@usal.se>           *
 *                                                                      *
 * This file is part of PhotoMatch                                      *
 *                                                                      *
 * PhotoMatch is free software: you can redistribute it and/or modify   *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation, either version 3 of the License, or    *
 * (at your option) any later version.                                  *
 *                                                                      *
 * PhotoMatch is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of       *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        *
 * GNU General Public License for more details.                         *
 *                                                                      *
 * You should have received a copy of the GNU General Public License    *
 * along with Foobar.  If not, see <http://www.gnu.org/licenses/>.      *
 *                                                                      *
 * @license GPL-3.0+ <http://spdx.org/licenses/GPL-3.0+>                *
 *                                                                      *
 ************************************************************************/


#include "HelpDialog.h"

#include <tidop/core/messages.h>

#include <QHelpEngine>
#include <QHelpContentWidget>
#include <QHelpIndexWidget>
#include <QHelpSearchEngine>
#include <QHelpSearchQueryWidget>
#include <QHelpSearchResultWidget>
#include <QMessageBox>
#include <QLabel>
#include <QTextBrowser>
#include <QToolBar>
#include <QVBoxLayout>
#include <QVariant>
#include <QApplication>

#define PHOTOMATCH_HELP_URL_BASE "qthelp://tidop.com.photomatch.1.0/doc/"
#define PHOTOMATCH_HELP_HOME_PAGE "index.html"

static const QUrl& HOME_PAGE = QUrl(QString(PHOTOMATCH_HELP_URL_BASE) + QString(PHOTOMATCH_HELP_HOME_PAGE));

HelpBrowser::HelpBrowser(QHelpEngine* helpEngine, QWidget *parent)
  : QTextBrowser(parent),
    mHelpEngine(helpEngine)
{
}

QVariant HelpBrowser::loadResource(int type, const QUrl &name)
{
  if (name.scheme() == "qthelp")
    return QVariant(mHelpEngine->fileData(name));
  else
    return QTextBrowser::loadResource(type, name);
}


namespace photomatch
{

HelpDialog::HelpDialog(QWidget *parent)
  : QDialog(parent, Qt::WindowMinMaxButtonsHint | Qt::WindowCloseButtonHint)
{
  init();

  retranslate();

  connect(mHelpBrowser, SIGNAL(forwardAvailable(bool)),  mNavigateForwardAction,  SLOT(setEnabled(bool)));
  connect(mHelpBrowser, SIGNAL(backwardAvailable(bool)), mNavigateForwardAction, SLOT(setEnabled(bool)));

  connect(mHelpEngine->indexWidget(),   SIGNAL(linkActivated(const QUrl&, const QString&)), mHelpBrowser, SLOT(setSource(const QUrl &)));
  connect(mHelpEngine->contentWidget(), SIGNAL(clicked(const QModelIndex &)),               this,         SLOT(setContentSource(const QModelIndex &)));

  connect(mHelpEngine->searchEngine()->queryWidget(), SIGNAL(search()),               this, SLOT(searchInvoked()));
  connect(mHelpEngine->searchEngine(),                SIGNAL(searchingFinished(int)), this, SLOT(searchFinished(int)));

  connect(mSearchResultsWidget, SIGNAL(anchorClicked(const QUrl&)), mHelpBrowser, SLOT(setSource(const QUrl&)));
}

HelpDialog::~HelpDialog()
{
}

void HelpDialog::setPage(const QString &page)
{
  QUrl url(QString(PHOTOMATCH_HELP_URL_BASE).append(page));
  mHelpEngine->contentWidget()->setCurrentIndex(mHelpEngine->contentWidget()->indexOf(page));
  mHelpBrowser->setSource(url);
}

void HelpDialog::setContentSource(const QModelIndex &index)
{
  QHelpContentItem *item = mHelpEngine->contentModel()->contentItemAt(index);
  if (item) {
    mHelpBrowser->setSource(item->url());
  }
}

void HelpDialog::setIndexSource(const QModelIndex &index)
{
  QVariant v = mHelpEngine->indexModel()->data(index, Qt::DisplayRole);
  QMap<QString,QUrl> item = mHelpEngine->indexModel()->linksForKeyword(v.toString());
  mHelpBrowser->setSource(item.constBegin().value());
}

void HelpDialog::searchInvoked()
{
  mHelpEngine->searchEngine()->search(mHelpEngine->searchEngine()->queryWidget()->query());
}

void HelpDialog::searchFinished(int hits)
{
  QList<QPair<QString, QString> > hitList = mHelpEngine->searchEngine()->hits(0, hits - 1);
  QString html = "<html><body>";
  for(int i = 0; i < hitList.size(); i++)
  {
    QString url = hitList[i].first;
    QString title = hitList[i].second;
    html += "<a href=\"" + url + "\">" + title + "</a><br>";
  }
  html += "</body></html>";
  mSearchResultsWidget->setHtml(html);
}

void HelpDialog::navigateHome()
{
  mHelpEngine->contentWidget()->setCurrentIndex(mHelpEngine->contentWidget()->indexOf(HOME_PAGE));
  mHelpBrowser->setSource(HOME_PAGE);
}

void HelpDialog::navigateForward()
{
  mHelpBrowser->forward();
}

void HelpDialog::navigateBackward()
{
  mHelpBrowser->backward();
}

void HelpDialog::init()
{
#ifdef _DEBUG
  mHelpEngine = new QHelpEngine("D:/Desarrollo/libs_sources/FME/res/help/en/photomatch.qhc", this);
#else
  QString path = QApplication::applicationDirPath();
  path.append("/help/en/photomatch.qhc");
  mHelpEngine = new QHelpEngine(path, this);
#endif

  mHelpBrowser = new HelpBrowser(mHelpEngine, this);
  mHelpBrowser->setMinimumSize(600, 450);

  if (!mHelpEngine->setupData()) {
    std::string err = mHelpEngine->error().toStdString();
    msgError(err.c_str());
  }

  QHelpContentWidget* contentWidget = mHelpEngine->contentWidget();
  contentWidget->setFrameStyle(QFrame::NoFrame);

  QHelpIndexWidget* indexWidget = mHelpEngine->indexWidget();
  indexWidget->setFrameStyle(QFrame::NoFrame);

  QTabWidget* tabWidget = new QTabWidget(this);
  tabWidget->addTab(contentWidget, tr("Contents"));
  tabWidget->addTab(indexWidget, tr("Index"));
  tabWidget->setMaximumWidth(300);
  tabWidget->setMinimumWidth(200);

  QWidget *searchTabWidget = new QWidget(this);
  QVBoxLayout* searchTabLayout = new QVBoxLayout(this);
  searchTabLayout->addWidget(mHelpEngine->searchEngine()->queryWidget());
  searchTabLayout->addWidget(new QLabel(tr("Search results: "), this));
  mSearchResultsWidget = new QTextBrowser(this);
  searchTabLayout->addWidget(mSearchResultsWidget);
  searchTabWidget->setLayout(searchTabLayout);

  tabWidget->addTab(searchTabWidget, tr("Search"));
  tabWidget->setContentsMargins(0, 0, 0, 0);

  QToolBar *toolBar = new QToolBar(this);

  QAction* navigateHomeAction = new QAction(QIcon(":/ico/96/img/material/96/icons8_home_page_96px.png"), tr("Home"), this);
  navigateHomeAction->setStatusTip(tr("Home"));
  connect(navigateHomeAction, SIGNAL(triggered()), this, SLOT(navigateHome()));
  toolBar->addAction(navigateHomeAction);

  toolBar->addSeparator();

  QAction* navigateBackwardAction = new QAction(QIcon(":/ico/96/img/material/96/icons8_arrow_pointing_left_96px.png"), tr("Back"), this);
  navigateBackwardAction->setStatusTip(tr("Back"));
  connect(navigateBackwardAction, SIGNAL(triggered()), this, SLOT(navigateBackward()));
  toolBar->addAction(navigateBackwardAction);

  mNavigateForwardAction = new QAction(QIcon(":/ico/96/img/material/96/icons8_arrow_96px.png"), tr("Forward"), this);
  mNavigateForwardAction->setStatusTip(tr("Forward"));
  connect(mNavigateForwardAction, SIGNAL(triggered()), this, SLOT(navigateForward()));
  toolBar->addAction(mNavigateForwardAction);

  QWidget* helpWidget = new QWidget(this);

  QHBoxLayout *vBoxLayout = new QHBoxLayout(this);
  vBoxLayout->addWidget(tabWidget);
  vBoxLayout->addWidget(mHelpBrowser);
  vBoxLayout->setContentsMargins(0, 0, 0, 0);
  helpWidget->setLayout(vBoxLayout);

  QGridLayout *gridLayout = new QGridLayout(this);
  gridLayout->setContentsMargins(0, 0, 0, 0);
  gridLayout->addWidget(toolBar);
  gridLayout->addWidget(helpWidget);

  setLayout(gridLayout);

  mHelpEngine->searchEngine()->reindexDocumentation();

  mSearchResultsWidget->setOpenLinks(false);
  mSearchResultsWidget->setOpenExternalLinks(false);

  navigateHome();
}

void HelpDialog::retranslate()
{
}

} // namespace photomatch

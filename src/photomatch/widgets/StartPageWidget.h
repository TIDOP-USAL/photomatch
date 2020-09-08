#ifndef PHOTOMATCH_START_PAGE_WIDGET_H
#define PHOTOMATCH_START_PAGE_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QLabel;
class QSplitter;
class QCommandLinkButton;
class QListWidget;

namespace photomatch
{

class StartPageWidget
  : public PhotoMatchWidget
{

  Q_OBJECT

public:

  StartPageWidget(QWidget *parent = nullptr);
  ~StartPageWidget() override = default;

  void setHistory(const QStringList &history);

signals:

  void openNew();
  void openProject();
  void openSettings();
  void openGitHub();
  void clearHistory();
  void openProjectFromHistory(QString);

// PhotoMatchWidget interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void reset() override;

protected slots:

  void update() override;
  void retranslate() override;

protected:

  QLabel *mLabelPhotoMatch;
  QLabel *mLabelRecentProjects;
  QSplitter *mSplitter;
  QCommandLinkButton *mCommandLinkButtonNewProject;
  QCommandLinkButton *mCommandLinkButtonOpenProject;
  QCommandLinkButton *mCommandLinkButtonSettings;
  QCommandLinkButton *mCommandLinkButtonGitHub;
  QListWidget *mListWidgetRecentProjects;
  QCommandLinkButton *mCommandLinkButtonClearHistory;
};

} // namespace photomatch

#endif // PHOTOMATCH_START_PAGE_WIDGET_H

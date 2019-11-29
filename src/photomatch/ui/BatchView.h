#ifndef PHOTOMATCH_BATCH_H
#define PHOTOMATCH_BATCH_H

#include "mvp.h"

class QLabel;
class QTabWidget;
class QTextEdit;
class QListWidget;
class QTreeWidget;
class QComboBox;

namespace photomatch
{

class IBatchView
  : public IWidgetView
{

  Q_OBJECT

public:

  IBatchView(QWidget *parent = nullptr)
    : IWidgetView(parent) {}
  virtual ~IBatchView() override = default;

public slots:

  virtual void open() = 0;
  virtual void setSessions(const QStringList &sessions) = 0;
  virtual void setActiveSession(const QString &session) = 0;

signals:

  void sessionChange(QString);

};

class BatchView
  : public IBatchView
{

  Q_OBJECT

public:

  BatchView(QWidget *parent = nullptr);
  ~BatchView() override = default;

// IWidgetView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

 // IBatchView interface

public slots:

  void open() override;
  void setSessions(const QStringList &sessions) override;
  void setActiveSession(const QString &session) override;


protected:

  //QScrollArea *mScrollArea;
  //QWidget *scrollAreaWidgetContents;
  //QGridLayout *gridLayout_3;
  QLabel *mLabelProcess;
  //QSpacerItem *verticalSpacer;
  QPushButton *mPushButtonAddProcess;
  QTabWidget *mTabWidget;
  QWidget *mTabProcess;
  //QGridLayout *gridLayout_4;
  QTreeWidget *mTreeWidget;
  QPushButton *mPushButtonDown;
  QPushButton *mPushButtonUp;
  QPushButton *mPushButtonDeleteProcess;
  QPushButton *pushButton;
  QWidget *tabProcessTextView;
  //QGridLayout *gridLayout_2;
  QTextEdit *mTextEditBatch;
  QWidget *mWidgetProcessContainer;
  QListWidget *mListWidgetProcess;
  QLabel *mLabelSession;
  QComboBox *mComboBoxSession;

};

} // namespace photomatch

#endif // PHOTOMATCH_BATCH_H

#ifndef PHOTOMATCH_EXPORT_MATCHES_VIEW_H
#define PHOTOMATCH_EXPORT_MATCHES_VIEW_H

#include "photomatch/ui/mvp.h"

class QLabel;
class QComboBox;
class QDialogButtonBox;
class QLineEdit;

namespace photomatch
{

class IExportMatchesView
  : public IDialogView
{

  Q_OBJECT

public:

  IExportMatchesView(QWidget *parent) : IDialogView(parent) {}
  virtual ~IExportMatchesView() override = default;

  //virtual QString format() const = 0;
  //virtual QString exportPath() const = 0;

public slots:

  virtual void setSessions(const QStringList &sessions) = 0;
  virtual void setActiveSession(const QString &session) = 0;
  //virtual void setFormats(const QStringList &formats) = 0;
  //virtual void setCurrentFormat(const QString &format) = 0;

signals:

  void sessionChange(QString);
  //void formatChange(QString);
  //void exportMatches();
};


class ExportMatchesView
  : public IExportMatchesView
{

  Q_OBJECT

public:

  ExportMatchesView(QWidget *parent = nullptr);
  virtual ~ExportMatchesView() override;

protected slots:

  //void onPushButtonExportFormat();

// IExportMatchesView interface

  //QString format() const override;
  //QString exportPath() const override;

public slots:

  void setSessions(const QStringList &sessions) override;
  void setActiveSession(const QString &session) override;
  //void setFormats(const QStringList &formats) override;
  //void setCurrentFormat(const QString &format) override;

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QLabel *mLabelSession;
  QComboBox *mComboBoxSession;
  //QLabel *mLabelFormat;
  //QComboBox *mComboBoxFormat;
  //QLabel *mLabelExportPath;
  //QLineEdit *mLineEditExportPath;
  //QPushButton *mPushButtonExportFormat;
  QDialogButtonBox *mButtonBox;
};


} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_MATCHES_VIEW_H

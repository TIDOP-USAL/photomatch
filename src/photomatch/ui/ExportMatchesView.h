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

public slots:

  virtual void setSessions(const QStringList &sessions) = 0;
  virtual void setActiveSession(const QString &session) = 0;

signals:

  void sessionChange(QString);
};


class ExportMatchesView
  : public IExportMatchesView
{

  Q_OBJECT

public:

  ExportMatchesView(QWidget *parent = nullptr);
  virtual ~ExportMatchesView() override;

// IExportMatchesView interface

public slots:

  void setSessions(const QStringList &sessions) override;
  void setActiveSession(const QString &session) override;

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
  QDialogButtonBox *mButtonBox;
};


} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_MATCHES_VIEW_H

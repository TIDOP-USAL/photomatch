#ifndef PHOTOMATCH_EXPORT_FEATURES_VIEW_H
#define PHOTOMATCH_EXPORT_FEATURES_VIEW_H

#include "photomatch/ui/mvp.h"

class QLabel;
class QComboBox;
class QDialogButtonBox;
class QCheckBox;
class QListWidget;
class QLineEdit;

namespace photomatch
{

class IExportFeaturesView
  : public IDialogView
{

  Q_OBJECT

public:

  IExportFeaturesView(QWidget *parent) : IDialogView(parent) {}
  virtual ~IExportFeaturesView() override = default;

  virtual QString format() const = 0;
  virtual QStringList exportFiles() const = 0;
  virtual QString exportPath() const = 0;
  virtual bool exportAll() const = 0;

public slots:

  virtual void setSessions(const QStringList &sessions) = 0;
  virtual void setActiveSession(const QString &session) = 0;
  virtual void setFormats(const QStringList &formats) = 0;
  virtual void setCurrentFormat(const QString &format) = 0;
  virtual void setExportAll(bool active) = 0;
  virtual void setExportPath(const QString &path) = 0;
  virtual void setImageFiles(const QStringList &images) = 0;

signals:

  void sessionChange(QString);
  void formatChange(QString);
  //void exportKeypoints();
};


class ExportFeaturesView
  : public IExportFeaturesView
{

  Q_OBJECT

public:

  ExportFeaturesView(QWidget *parent = nullptr);
  virtual ~ExportFeaturesView() override;

protected slots:

  void onPushButtonExportFormat();

// IExportFeaturesView interface

public:

  QString format() const override;
  QStringList exportFiles() const override;
  QString exportPath() const override;
  bool exportAll() const override;

public slots:

  void setSessions(const QStringList &sessions) override;
  void setActiveSession(const QString &session) override;
  void setFormats(const QStringList &formats) override;
  void setCurrentFormat(const QString &format) override;
  void setExportAll(bool active) override;
  void setExportPath(const QString &path) override;
  void setImageFiles(const QStringList &images) override;

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
  QLabel *mLabelFormat;
  QComboBox *mComboBoxFormat;
  QLabel *mLabelExportPath;
  QLineEdit *mLineEditExportPath;
  QPushButton *mPushButtonExportFormat;
  QCheckBox *mCheckBoxExportAll;
  QListWidget *mListWidgetfeatures;
  QDialogButtonBox *mButtonBox;
};


} // namespace photomatch

#endif // PHOTOMATCH_EXPORT_FEATURES_VIEW_H

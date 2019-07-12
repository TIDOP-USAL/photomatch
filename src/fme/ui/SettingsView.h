#ifndef FME_SETTINGS_VIEW_H
#define FME_SETTINGS_VIEW_H

#include "mvp.h"

class QListWidget;
class QStackedWidget;
class QComboBox;
class QDialogButtonBox;
class QTabWidget;
class QGridLayout;

namespace fme
{

class ISettingsView
  : public IDialogView
{

  Q_OBJECT

public:

  ISettingsView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~ISettingsView(){}

  virtual void setLanguages(const QStringList &languages) = 0;
  virtual void setActiveLanguage(const QString &language) = 0;
  virtual void addPreprocess(QWidget *preprocess) = 0;
  virtual void addFeatureDetectorMethod(QWidget *detector) = 0;

public slots:

  virtual void setUnsavedChanges(bool unsaveChanges) = 0;

signals:

  void languageChange(QString);
  void applyChanges();

};

class SettingsView
  : public ISettingsView
{
  Q_OBJECT

public:

  SettingsView(QWidget *parent = nullptr);
  ~SettingsView() override;

protected slots:

  void onPreprocessChange(const QString &method);
  void onFeatureDetectorDescriptorChange(const QString &method);

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;

// ISettingsView interface

public:

  void setLanguages(const QStringList &languages) override;
  void setActiveLanguage(const QString &language) override;
  void addPreprocess(QWidget *preprocess) override;
  void addFeatureDetectorMethod(QWidget *detector) override;

public slots:

  void setUnsavedChanges(bool unsaveChanges) override;

protected:

  QListWidget *mListWidget;
  QStackedWidget *mStackedWidget;
  QComboBox *mLanguages;
  QTabWidget *mTabWidgetTools;
  QGridLayout *mGridLayoutPreprocess;
  QGridLayout *mGridLayoutFeatures;

  QListWidget *mListWidgetPreprocess;
  QListWidget *mListWidgetFeatures;
  QListWidget *mListWidgetMatching;
  QDialogButtonBox *mButtonBox;
  bool bUnsaveChanges;
};

} // namespace fme

#endif // FME_SETTINGS_VIEW_H

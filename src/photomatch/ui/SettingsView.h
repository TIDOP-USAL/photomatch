#ifndef PHOTOMATCH_SETTINGS_VIEW_H
#define PHOTOMATCH_SETTINGS_VIEW_H

#include "mvp.h"

class QListWidget;
class QStackedWidget;
class QComboBox;
class QDialogButtonBox;
class QTabWidget;
class QGridLayout;
class QSpinBox;
class QLineEdit;

namespace photomatch
{

class ISettingsView
  : public IDialogView
{

  Q_OBJECT

public:

  ISettingsView(QWidget *parent = nullptr) : IDialogView(parent) {}
  virtual ~ISettingsView(){}

  /*!
   * \brief Active language
   */
  virtual QString activeLanguage() const = 0;

  /*!
   * \brief History size
   */
  virtual int historyMaxSize() const = 0;

  virtual QString imageViewerBGColor() const = 0;

  virtual QString keypointsFormat() const = 0;
  virtual QString matchesFormat() const = 0;

  virtual QString keypointsViewerBGColor() const = 0;
  virtual int keypointsViewerMarkerType() const = 0;
  virtual int keypointsViewerMarkerSize() const = 0;
  virtual int keypointsViewerMarkerWidth() const = 0;
  virtual QString keypointsViewerMarkerColor() const = 0;

  virtual QString matchesViewerBGColor() const = 0;
  virtual int matchesViewerMarkerType() const = 0;
  virtual int matchesViewerMarkerSize() const = 0;
  virtual int matchesViewerMarkerWidth() const = 0;
  virtual QString matchesViewerMarkerColor() const = 0;
  virtual QString matchesViewerLineColor() const = 0;
  virtual int matchesViewerLineWidth() const = 0;

  virtual QString groundTruthEditorBGColor() const = 0;
  virtual int groundTruthEditorMarkerSize() const = 0;
  virtual int groundTruthEditorMarkerWidth() const = 0;
  virtual QString groundTruthEditorMarkerColor() const = 0;

public slots:

  /*!
   * \brief Set active page
   * \param[in] page Active page
   */
  virtual void setPage(int page) = 0;

  /*!
   * \brief Set available languages
   * \param[in] languages Available languages
   */
  virtual void setLanguages(const QStringList &languages) = 0;

  /*!
   * \brief Set active language
   * \param[in] language Active language
   */
  virtual void setActiveLanguage(const QString &language) = 0;

  /*!
   * \brief Set history size
   * \param[in] size History size
   */
  virtual void setHistoryMaxSize(int size) = 0;

  virtual void setImageViewerBGcolor(const QString &color) = 0;

  virtual void setKeypointsFormat(const QString &format) = 0;
  virtual void setMatchesFormat(const QString &format) = 0;

  virtual void addPreprocess(QWidget *preprocess) = 0;
  virtual void addFeatureDetectorMethod(QWidget *detector) = 0;
  virtual void addDescriptorMatcher(QWidget *detector) = 0;

  virtual void setKeypointsViewerBGColor(const QString &color) = 0;
  virtual void setKeypointsViewerMarkerType(int type) = 0;
  virtual void setKeypointsViewerMarkerSize(int size) = 0;
  virtual void setKeypointsViewerMarkerWidth(int width) = 0;
  virtual void setKeypointsViewerMarkerColor(const QString &color) = 0;

  virtual void setMatchesViewerBGColor(const QString &color) = 0;
  virtual void setMatchesViewerMarkerType(int type) = 0;
  virtual void setMatchesViewerMarkerSize(int size) = 0;
  virtual void setMatchesViewerMarkerWidth(int width) = 0;
  virtual void setMatchesViewerMarkerColor(const QString &color) = 0;
  virtual void setMatchesViewerLineColor(const QString &color) = 0;
  virtual void setMatchesViewerLineWidth(int width) = 0;

  virtual void setGroundTruthEditorBGColor(const QString &bgColor) = 0;
  virtual void setGroundTruthEditorMarkerSize(int size) = 0;
  virtual void setGroundTruthEditorMarkerWidth(int width) = 0;
  virtual void setGroundTruthEditorMarkerColor(const QString &color) = 0;

  virtual void setUnsavedChanges(bool unsaveChanges) = 0;

signals:

  void languageChange(QString);
  void historyMaxSizeChange(int);
  void imageViewerBGColorChange(QString);
  void keypointsFormatChange(QString);
  void matchesFormatChange(QString);
  void applyChanges();

  void keypointsViewerBGColorChange(QString);
  void keypointsViewerMarkerTypeChange(int);
  void keypointsViewerMarkerSizeChange(int);
  void keypointsViewerMarkerWidthChange(int);
  void keypointsViewerMarkerColorChange(QString);

  void matchesViewerBGColorChange(QString);
  void matchesViewerMarkerTypeChange(int);
  void matchesViewerMarkerSizeChange(int);
  void matchesViewerMarkerWidthChange(int);
  void matchesViewerMarkerColorChange(QString);
  void matchesViewerLineWidthChange(int);
  void matchesViewerLineColorChange(QString);

  void groundTruthEditorBGColorChange(QString);
  void groundTruthEditorMarkerSizeChange(int);
  void groundTruthEditorMarkerWidthChange(int);
  void groundTruthEditorMarkerColorChange(QString);

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
  void onPushButtonImageViewerBGColorClicked();
  void onPushButtonKeypointViewerBGColorClicked();
  void onPushButtonKeypointViewerMarkerColorClicked();
  void onPushButtonMatchViewerBGColorClicked();
  void onPushButtonMatchViewerMarkerColorClicked();
  void onPushButtonMatchViewerLineColorClicked();
  void onPushButtonGroundTruthEditorBGColorClicked();
  void onPushButtonGroundTruthEditorMarkerColorClicked();

// IDialogView interface

private:

  void init() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

// ISettingsView interface

public:

  QString activeLanguage() const override;
  int historyMaxSize() const override;

  QString imageViewerBGColor() const override;

  QString keypointsFormat() const override;
  QString matchesFormat() const override;

  QString keypointsViewerBGColor() const override;
  int keypointsViewerMarkerType() const override;
  int keypointsViewerMarkerSize() const override;
  int keypointsViewerMarkerWidth() const override;
  QString keypointsViewerMarkerColor() const override;

  QString matchesViewerBGColor() const override;
  int matchesViewerMarkerType() const override;
  int matchesViewerMarkerSize() const override;
  int matchesViewerMarkerWidth() const override;
  QString matchesViewerMarkerColor() const override;
  QString matchesViewerLineColor() const override;
  int matchesViewerLineWidth() const override;

  QString groundTruthEditorBGColor() const override;
  int groundTruthEditorMarkerSize() const override;
  int groundTruthEditorMarkerWidth() const override;
  QString groundTruthEditorMarkerColor() const override;

public slots:

  void setPage(int page) override;

  void setLanguages(const QStringList &languages) override;
  void setActiveLanguage(const QString &language) override;

  void setHistoryMaxSize(int size) override;

  void setImageViewerBGcolor(const QString &color) override;

  void setKeypointsFormat(const QString &format) override;
  void setMatchesFormat(const QString &format) override;

  void addPreprocess(QWidget *preprocess) override;
  void addFeatureDetectorMethod(QWidget *detector) override;
  void addDescriptorMatcher(QWidget *detector) override;

  void setKeypointsViewerBGColor(const QString &color) override;
  void setKeypointsViewerMarkerType(int type) override;
  void setKeypointsViewerMarkerSize(int size) override;
  void setKeypointsViewerMarkerWidth(int width) override;
  void setKeypointsViewerMarkerColor(const QString &color) override;

  void setMatchesViewerBGColor(const QString &color) override;
  void setMatchesViewerMarkerType(int type) override;
  void setMatchesViewerMarkerSize(int size) override;
  void setMatchesViewerMarkerWidth(int width) override;
  void setMatchesViewerMarkerColor(const QString &color) override;
  void setMatchesViewerLineColor(const QString &color) override;
  void setMatchesViewerLineWidth(int width) override;

  void setGroundTruthEditorBGColor(const QString &bgColor) override;
  void setGroundTruthEditorMarkerSize(int size) override;
  void setGroundTruthEditorMarkerWidth(int width) override;
  void setGroundTruthEditorMarkerColor(const QString &color) override;

  void setUnsavedChanges(bool unsaveChanges) override;

protected:

  QListWidget *mListWidget;
  QStackedWidget *mStackedWidget;
  QComboBox *mLanguages;
  QSpinBox *mHistoryMaxSize;
  QTabWidget *mTabWidgetTools;
  QTabWidget *mTabQualityControl;
  QComboBox *mKeypointsFormat;
  QComboBox *mMatchesFormat;
  QGridLayout *mGridLayoutPreprocess;
  QGridLayout *mGridLayoutFeatures;
  QGridLayout *mGridLayoutMatcher;

  QLineEdit *mLineEditImageViewerBGcolor;
  QPushButton *mPushButtonImageViewerBGcolor;

  QLineEdit *mLineEditKeypointViewerBGColor;
  QPushButton *mPushButtonKeypointViewerBGColor;
  QSpinBox *mSpinBoxKeypointViewerMarkerSize;
  QSpinBox *mSpinBoxKeypointViewerMarkerWidth;
  QLineEdit *mLineEditKeypointViewerMarkerColor;
  QPushButton *mPushButtonKeypointViewerMarkerColor;
  QListWidget *mListWidgetKeypointsViewerMarkerType;

  //QLineEdit *mLineEditMatchesKeypointMarkerColor;
  QLineEdit *mLineEditMatchesViewerBGColor;
  QPushButton *mPushButtonMatchesViewerBGColor;
  QLineEdit *mLineEditMatchesViewerMarkerColor;
  QPushButton *mPushButtonMatchesViewerMarkerColor;
  QSpinBox *mSpinBoxMatchesViewerMarkerSize;
  QSpinBox *mSpinBoxMatchesViewerMarkerWidth;
  QListWidget *mListWidgetMatchesViewerMarkerType;
  QLineEdit *mLineEditMatchesViewerLineColor;
  QPushButton *mPushButtonMatchesViewerLineColor;
  QSpinBox *mSpinBoxMatchesViewerLineWidth;

  QLineEdit *mLineEditGroundTruthEditorBGColor;
  QPushButton *mPushButtonGroundTruthEditorBGColor;
  QSpinBox *mSpinBoxGroundTruthEditorMarkerSize;
  QSpinBox *mSpinBoxGroundTruthEditorMarkerWidth;
  QLineEdit *mLineEditGroundTruthEditorMarkerColor;
  QPushButton *mPushButtonGroundTruthEditorMarkerColor;

  QListWidget *mListWidgetPreprocess;
  QListWidget *mListWidgetFeatures;
  //QListWidget *mListWidgetMatching;
  QDialogButtonBox *mButtonBox;

  bool bUnsaveChanges;
};


} // namespace photomatch

#endif // PHOTOMATCH_SETTINGS_VIEW_H

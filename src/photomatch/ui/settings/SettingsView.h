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


#ifndef PHOTOMATCH_SETTINGS_VIEW_H
#define PHOTOMATCH_SETTINGS_VIEW_H

#include "photomatch/ui/settings/Settings.h"

class QListWidget;
class QStackedWidget;
class QComboBox;
class QDialogButtonBox;
class QTabWidget;
class QGridLayout;
class QSpinBox;
class QLineEdit;
class QCheckBox;
class QLabel;

namespace photomatch
{



class SettingsViewImp
  : public SettingsView
{
  Q_OBJECT

public:

  SettingsViewImp(QWidget *parent = nullptr);
  ~SettingsViewImp() override;

protected slots:

  void onPreprocessChange(const QString &method);
  void onFeatureDetectorDescriptorChange(const QString &method);
  void onPushButtonImageViewerBGColorClicked();
  void onPushButtonKeypointViewerBGColorClicked();
  void onPushButtonKeypointViewerMarkerColorClicked();
  void onPushButtonSelectKeypointViewerMarkerColorClicked();
  void onPushButtonMatchViewerBGColorClicked();
  void onPushButtonMatchViewerMarkerColorClicked();
  void onPushButtonSelectMatchViewerMarkerColorClicked();
  void onPushButtonMatchViewerLineColorClicked();
  void onPushButtonGroundTruthEditorBGColorClicked();
  void onPushButtonGroundTruthEditorMarkerColorClicked();
  void onPushButtonSelectGroundTruthEditorMarkerColorClicked();

private:

  void initGeneralPage();
  void initImageViewerPage();
  void initToolsPage();
  void initQualityControlPage();

// SettingsView interface

public:

  QString activeLanguage() const override;
  int historyMaxSize() const override;

  QString imageViewerBGColor() const override;

  QString keypointsFormat() const override;
  QString matchesFormat() const override;
  bool useCuda() const override;

  QString keypointsViewerBGColor() const override;
  int keypointsViewerMarkerType() const override;
  int keypointsViewerMarkerSize() const override;
  int keypointsViewerMarkerWidth() const override;
  QString keypointsViewerMarkerColor() const override;
  int selectKeypointsViewerMarkerWidth() const override;
  QString selectKeypointsViewerMarkerColor() const override;

  QString matchesViewerBGColor() const override;
  int matchesViewerMarkerType() const override;
  int matchesViewerMarkerSize() const override;
  int matchesViewerMarkerWidth() const override;
  QString matchesViewerMarkerColor() const override;
  int selectMatchesViewerMarkerWidth() const override;
  QString selectMatchesViewerMarkerColor() const override;
  QString matchesViewerLineColor() const override;
  int matchesViewerLineWidth() const override;

  QString groundTruthEditorBGColor() const override;
  int groundTruthEditorMarkerSize() const override;
  int groundTruthEditorMarkerWidth() const override;
  QString groundTruthEditorMarkerColor() const override;
  int selectGroundTruthEditorMarkerWidth() const override;
  QString selectGroundTruthEditorMarkerColor() const override;
  QString groundTruthEditorMatrixAdjust() const override;

public slots:

  void setPage(int page) override;

  void setLanguages(const QStringList &languages) override;
  void setActiveLanguage(const QString &language) override;

  void setHistoryMaxSize(int size) override;

  void setImageViewerBGcolor(const QString &color) override;

  void setKeypointsFormat(const QString &format) override;
  void setMatchesFormat(const QString &format) override;
  void setUseCuda(bool active) override;
  void setCudaEnabled(bool enabled) override;

  void addPreprocess(QWidget *preprocess) override;
  void addFeatureDetectorMethod(QWidget *detector) override;
  void addDescriptorMatcher(QWidget *detector) override;

  void setKeypointsViewerBGColor(const QString &color) override;
  void setKeypointsViewerMarkerType(int type) override;
  void setKeypointsViewerMarkerSize(int size) override;
  void setKeypointsViewerMarkerWidth(int width) override;
  void setKeypointsViewerMarkerColor(const QString &color) override;
  void setSelectKeypointsViewerMarkerWidth(int width) override;
  void setSelectKeypointsViewerMarkerColor(const QString &color) override;

  void setMatchesViewerBGColor(const QString &color) override;
  void setMatchesViewerMarkerType(int type) override;
  void setMatchesViewerMarkerSize(int size) override;
  void setMatchesViewerMarkerWidth(int width) override;
  void setMatchesViewerMarkerColor(const QString &color) override;
  void setSelectMatchesViewerMarkerWidth(int width) override;
  void setSelectMatchesViewerMarkerColor(const QString &color) override;
  void setMatchesViewerLineColor(const QString &color) override;
  void setMatchesViewerLineWidth(int width) override;

  void setGroundTruthEditorBGColor(const QString &bgColor) override;
  void setGroundTruthEditorMarkerSize(int size) override;
  void setGroundTruthEditorMarkerWidth(int width) override;
  void setGroundTruthEditorMarkerColor(const QString &color) override;
  void setSelectGroundTruthEditorMarkerWidth(int width) override;
  void setSelectGroundTruthEditorMarkerColor(const QString &color) override;
  void setGroundTruthEditorMatrixAdjust(const QString &matrix) override;

  void setUnsavedChanges(bool unsaveChanges) override;

// PhotoMatchDialogView interface

private:

  void initUI() override;
  void initSignalAndSlots() override;

public slots:

  void clear() override;

private slots:

  void update() override;
  void retranslate() override;

protected:

  QListWidget *mListWidget;
  QStackedWidget *mStackedWidget;
  QLabel *mLabelLanguage;
  QComboBox *mLanguages;
  QLabel *mLabelHistoryMaxSize;
  QSpinBox *mHistoryMaxSize;
  QTabWidget *mTabWidgetTools;
  QTabWidget *mTabQualityControl;
  QComboBox *mKeypointsFormat;
  QComboBox *mMatchesFormat;
  QLabel *mLabelUseCuda;
  QCheckBox *mCheckBoxUseCuda;
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
  QSpinBox *mSpinBoxSelectKeypointViewerMarkerWidth;
  QLineEdit *mLineEditSelectKeypointViewerMarkerColor;
  QPushButton *mPushButtonSelectKeypointViewerMarkerColor;
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
  QSpinBox *mSpinBoxSelectMatchesViewerMarkerWidth;
  QLineEdit *mLineEditSelectMatchesViewerMarkerColor;
  QPushButton *mPushButtonSelectMatchesViewerMarkerColor;

  QLineEdit *mLineEditGroundTruthEditorBGColor;
  QPushButton *mPushButtonGroundTruthEditorBGColor;
  QSpinBox *mSpinBoxGroundTruthEditorMarkerSize;
  QSpinBox *mSpinBoxGroundTruthEditorMarkerWidth;
  QLineEdit *mLineEditGroundTruthEditorMarkerColor;
  QPushButton *mPushButtonGroundTruthEditorMarkerColor;
  QSpinBox *mSpinBoxSelectGTEditorMarkerWidth;
  QLineEdit *mLineEditSelectGTEditorMarkerColor;
  QPushButton *mPushButtonSelectGTEditorMarkerColor;
  QComboBox *mGroundTruthEditorMatrixAdjust;

  QListWidget *mListWidgetPreprocess;
  QListWidget *mListWidgetFeatures;
  //QListWidget *mListWidgetMatching;
  QDialogButtonBox *mButtonBox;

  bool bUnsaveChanges;
};


} // namespace photomatch

#endif // PHOTOMATCH_SETTINGS_VIEW_H

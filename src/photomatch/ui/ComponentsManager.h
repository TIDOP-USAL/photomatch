#ifndef PHOTOMATCH_COMPONENTSMANAGER_H
#define PHOTOMATCH_COMPONENTSMANAGER_H

#include <QObject>

namespace photomatch
{

class MainWindowModel;
class MainWindowView;
class MainWindowPresenter;

class ProjectModel;
class ProjectController;
class Project;

class Settings;
class SettingsController;
class SettingsModel;
class SettingsPresenter;

class NewProjectPresenter;
class NewSessionPresenter;

class ExportFeaturesModel;
class ExportFeaturesPresenter;
class ExportMatchesModel;
class ExportMatchesPresenter;

class PreprocessPresenter;
class PreprocessModel;

class FeatureExtractorModel;
class FeatureExtractorPresenter;

class DescriptorMatcherModel;
class DescriptorMatcherPresenter;

class FeaturesViewerModel;
class FeaturesViewerPresenter;

class MatchViewerPresenter;
class MatchViewerModel;

class MultiViewMatchingAssessmentModel;
class MultiViewMatchingAssessmentPresenter;

class GroundTruthModel;
class GroundTruthPresenter;

class HomographyViewerPresenter;
class HomographyViewerModel;

class CurvesViewerPresenter;
class CurvesViewerModel;

class RepeatabilityModel;
class RepeatabilityPresenter;

class AboutDialog;
class HelpDialog;

class ProgressHandler;
class IProgressDialog;


class ComponentsManager
  : public QObject
{
  Q_OBJECT

public:

  explicit ComponentsManager(QObject *parent = nullptr);
  ~ComponentsManager();


  MainWindowView *mainWindowView();
  MainWindowModel *mainWindowModel();
  MainWindowPresenter *mainWindowPresenter();

  ProjectModel *projectModel();

  SettingsModel *settingsModel();
  SettingsPresenter *settingsPresenter();

  NewProjectPresenter *newProjectPresenter();

  NewSessionPresenter *newSessionPresenter();

  ExportFeaturesPresenter *exportFeaturesPresenter();
  ExportFeaturesModel *exportFeaturesModel();
  ExportMatchesPresenter *exportMatchesPresenter();
  ExportMatchesModel *exportMatchesModel();

  PreprocessPresenter *preprocessPresenter();

  FeatureExtractorPresenter *featureExtractorPresenter();

  DescriptorMatcherPresenter *descriptorMatcherPresenter();

  FeaturesViewerPresenter *featuresViewerPresenter();
  FeaturesViewerModel *featuresViewerModel();

  MatchViewerPresenter *matchesViewerPresenter();
  MatchViewerModel *matchesViewerModel();

  MultiViewMatchingAssessmentModel *multiviewMatchingAssessmentModel();
  MultiViewMatchingAssessmentPresenter *multiviewMatchingAssessmentPresenter();

  GroundTruthPresenter *groundTruthPresenter();
  GroundTruthModel *groundTruthModel();

  HomographyViewerPresenter *homographyViewerPresenter();
  HomographyViewerModel *homographyViewerModel();

  CurvesViewerPresenter *curvesPRViewerPresenter();
  CurvesViewerModel *curvesPRViewerModel();
  CurvesViewerPresenter *curvesROCViewerPresenter();
  CurvesViewerModel *curvesROCViewerModel();
  CurvesViewerPresenter *curvesDETViewerPresenter();
  CurvesViewerModel *curvesDETViewerModel();

  RepeatabilityPresenter *repeatabilityPresenter();
  RepeatabilityModel *repeatabilityModel();

  AboutDialog *aboutDialog();

  HelpDialog *helpDialog();

  ProgressHandler *progressHandler();
  IProgressDialog *progressDialog();

signals:

protected slots:

  void initAndOpenNewProjectDialog();
  void initAndOpenNewSessionDialog();
  void initAndOpenPreprocessDialog();
  void initAndOpenFeatureExtractionDialog();
  void initAndOpenFeatureMatchingDialog();
  void initAndOpenKeypointsViewerDialogFromSession(const QString &session);
  void initAndOpenKeypointsViewerDialogFromSessionAndImage(const QString &session, const QString &image);
  void initKeypointsViewer();
  void initAndOpenMatchesViewerDialogFromSession(const QString &session);
  void initAndOpenMatchesViewerDialogFromSessionAndImages(const QString &session, const QString &leftImage, const QString &rightImage);
  void initMatchesViewer();
  void initAndOpenExportFeaturesDialog();
  void initAndOpenExportMatchesDialog();
  void initAndOpenGroundTruthEditorDialog();
  void initAndOpenHomographyViewerDialog();
  void initAndOpenPRCurvesViewerDialog();
  void initAndOpenROCCurvesViewerDialog();
  void initAndOpenDETCurvesViewerDialog();
  void initAndOpenAboutDialog();
  void initAndOpenSettingsDialog();
  void initAndOpenViewSettingsDialog();
  void initAndOpenQualityControlDialog();
  void initAndOpenToolSettingsDialog();
  void initSettingsDialog();
  void initAndOpenMultiviewMatchingAssessmentDialog();

protected:

  MainWindowView *mMainWindowView;
  MainWindowModel *mMainWindowModel;
  MainWindowPresenter *mMainWindowPresenter;

  Project *mProject;
  ProjectController *mProjectController;
  ProjectModel *mProjectModel;

  NewProjectPresenter *mNewProjectPresenter;

  NewSessionPresenter *mNewSessionPresenter;

  ExportFeaturesPresenter *mExportFeaturesPresenter;
  ExportFeaturesModel *mExportFeaturesModel;

  ExportMatchesPresenter *mExportMatchesPresenter;
  ExportMatchesModel *mExportMatchesModel;

  Settings *mSettings;
  SettingsController *mSettingsRW;
  SettingsModel *mSettingsModel;
  SettingsPresenter *mSettingsPresenter;

  PreprocessPresenter *mPreprocessPresenter;

  FeatureExtractorPresenter *mFeatureExtractorPresenter;

  DescriptorMatcherPresenter *mDescriptorMatcherPresenter;

  FeaturesViewerPresenter *mFeaturesViewerPresenter;
  FeaturesViewerModel *mFeaturesViewerModel;

  MatchViewerPresenter *mMatchesViewerPresenter;
  MatchViewerModel *mMatchesViewerModel;

  MultiViewMatchingAssessmentModel *mMultiviewMatchingAssessmentModel;
  MultiViewMatchingAssessmentPresenter *mMultiviewMatchingAssessmentPresenter;

  GroundTruthPresenter *mGroundTruthPresenter;
  GroundTruthModel *mGroundTruthModel;

  HomographyViewerPresenter *mHomographyViewerPresenter;
  HomographyViewerModel *mHomographyViewerModel;

  CurvesViewerPresenter *mCurvesPRViewerPresenter;
  CurvesViewerModel *mCurvesPRViewerModel;
  CurvesViewerPresenter *mCurvesROCViewerPresenter;
  CurvesViewerModel *mCurvesROCViewerModel;
  CurvesViewerPresenter *mCurvesDETViewerPresenter;
  CurvesViewerModel *mCurvesDETViewerModel;

  RepeatabilityPresenter *mRepeatabilityPresenter;
  RepeatabilityModel *mRepeatabilityModel;

  AboutDialog *mAboutDialog;
  HelpDialog *mHelpDialog;

  ProgressHandler *mProgressHandler;
  IProgressDialog *mProgressDialog;

};

} // namespace photomatch


#endif // PHOTOMATCH_COMPONENTS_MANAGER_H

#ifndef PHOTOMATCH_COMPONENTSMANAGER_H
#define PHOTOMATCH_COMPONENTSMANAGER_H

#include <QObject>

namespace photomatch
{

class MainWindowModel;
class MainWindowView;
class MainWindowPresenter;

class IProjectModel;
class ProjectController;
class Project;

class Settings;
class SettingsController;
class ISettingsModel;
class ISettingsPresenter;

class INewProjectPresenter;
class INewSessionPresenter;

class IExportFeaturesModel;
class IExportFeaturesPresenter;
class IExportMatchesModel;
class IExportMatchesPresenter;

class IPreprocessPresenter;
class IPreprocessModel;

class IFeatureExtractorModel;
class IFeatureExtractorPresenter;

class IDescriptorMatcherModel;
class IDescriptorMatcherPresenter;

class IFeaturesViewerModel;
class IFeaturesViewerPresenter;

class IMatchViewerPresenter;
class IMatchViewerModel;

class IMultiViewMatchingAssessmentModel;
class IMultiViewMatchingAssessmentPresenter;

class IGroundTruthModel;
class IGroundTruthPresenter;

class IHomographyViewerPresenter;
class IHomographyViewerModel;

class ICurvesViewerPresenter;
class ICurvesViewerModel;

class IRepeatabilityModel;
class IRepeatabilityPresenter;

class AboutDialog;
class HelpDialog;

class ProgressHandler;
class IProgressDialog;


class ComponentsManager : public QObject
{
  Q_OBJECT

public:

  explicit ComponentsManager(QObject *parent = nullptr);
  ~ComponentsManager();


  MainWindowView *mainWindowView();
  MainWindowModel *mainWindowModel();
  MainWindowPresenter *mainWindowPresenter();

  IProjectModel *projectModel();

//  Settings *settings();
//  SettingsController *settingsRW();
  ISettingsModel *settingsModel();
  ISettingsPresenter *settingsPresenter();

  INewProjectPresenter *newProjectPresenter();

  INewSessionPresenter *newSessionPresenter();

  IExportFeaturesPresenter *exportFeaturesPresenter();
  IExportFeaturesModel *exportFeaturesModel();
  IExportMatchesPresenter *exportMatchesPresenter();
  IExportMatchesModel *exportMatchesModel();

  //IPreprocessModel *preprocessModel();
  IPreprocessPresenter *preprocessPresenter();

  //IFeatureExtractorModel *featureExtractorModel();
  IFeatureExtractorPresenter *featureExtractorPresenter();

  //IDescriptorMatcherModel *descriptorMatcherModel();
  IDescriptorMatcherPresenter *descriptorMatcherPresenter();

  IFeaturesViewerPresenter *featuresViewerPresenter();
  IFeaturesViewerModel *featuresViewerModel();

  IMatchViewerPresenter *matchesViewerPresenter();
  IMatchViewerModel *matchesViewerModel();

  IMultiViewMatchingAssessmentModel *multiviewMatchingAssessmentModel();
  IMultiViewMatchingAssessmentPresenter *multiviewMatchingAssessmentPresenter();

  IGroundTruthPresenter *groundTruthPresenter();
  IGroundTruthModel *groundTruthModel();

  IHomographyViewerPresenter *homographyViewerPresenter();
  IHomographyViewerModel *homographyViewerModel();

  ICurvesViewerPresenter *curvesPRViewerPresenter();
  ICurvesViewerModel *curvesPRViewerModel();
  ICurvesViewerPresenter *curvesROCViewerPresenter();
  ICurvesViewerModel *curvesROCViewerModel();
  ICurvesViewerPresenter *curvesDETViewerPresenter();
  ICurvesViewerModel *curvesDETViewerModel();

  IRepeatabilityPresenter *repeatabilityPresenter();
  IRepeatabilityModel *repeatabilityModel();

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
  ProjectController *mProjectIO;
  IProjectModel *mProjectModel;

  INewProjectPresenter *mNewProjectPresenter;

  INewSessionPresenter *mNewSessionPresenter;

  IExportFeaturesPresenter *mExportFeaturesPresenter;
  IExportFeaturesModel *mExportFeaturesModel;

  IExportMatchesPresenter *mExportMatchesPresenter;
  IExportMatchesModel *mExportMatchesModel;

  Settings *mSettings;
  SettingsController *mSettingsRW;
  ISettingsModel *mSettingsModel;
  ISettingsPresenter *mSettingsPresenter;

  IPreprocessPresenter *mPreprocessPresenter;

  IFeatureExtractorPresenter *mFeatureExtractorPresenter;

  IDescriptorMatcherPresenter *mDescriptorMatcherPresenter;

  IFeaturesViewerPresenter *mFeaturesViewerPresenter;
  IFeaturesViewerModel *mFeaturesViewerModel;

  IMatchViewerPresenter *mMatchesViewerPresenter;
  IMatchViewerModel *mMatchesViewerModel;

  IMultiViewMatchingAssessmentModel *mMultiviewMatchingAssessmentModel;
  IMultiViewMatchingAssessmentPresenter *mMultiviewMatchingAssessmentPresenter;

  IGroundTruthPresenter *mGroundTruthPresenter;
  IGroundTruthModel *mGroundTruthModel;

  IHomographyViewerPresenter *mHomographyViewerPresenter;
  IHomographyViewerModel *mHomographyViewerModel;

  ICurvesViewerPresenter *mCurvesPRViewerPresenter;
  ICurvesViewerModel *mCurvesPRViewerModel;
  ICurvesViewerPresenter *mCurvesROCViewerPresenter;
  ICurvesViewerModel *mCurvesROCViewerModel;
  ICurvesViewerPresenter *mCurvesDETViewerPresenter;
  ICurvesViewerModel *mCurvesDETViewerModel;

  IRepeatabilityPresenter *mRepeatabilityPresenter;
  IRepeatabilityModel *mRepeatabilityModel;

  AboutDialog *mAboutDialog;
  HelpDialog *mHelpDialog;

  ProgressHandler *mProgressHandler;
  IProgressDialog *mProgressDialog;

};

} // namespace photomatch


#endif // PHOTOMATCH_COMPONENTS_MANAGER_H

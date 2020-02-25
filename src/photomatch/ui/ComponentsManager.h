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

class IMultiViewModel;
class IMultiViewPresenter;

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

  IMultiViewModel *multiviewModel();
  IMultiViewPresenter *multiviewPresenter();

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

public slots:

  void initAndOpenNewProjectDialog();
  void initAndOpenNewSessionDialog();
  void initAndOpenPreprocessDialog();
  void initAndOpenFeatureExtractionDialog();
  void initAndOpenFeatureMatchingDialog();
  void initAndOpenKeypointsViewerDialog();
  void initAndOpenKeypointsViewerDialog(const QString &session, const QString &image);
  void initAndOpenMatchesViewerDialog();
  void initAndOpenMatchesViewerDialog(const QString &session, const QString &leftImage, const QString &rightImage);

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

  IMultiViewModel *mMultiviewModel;
  IMultiViewPresenter *mMultiviewPresenter;

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

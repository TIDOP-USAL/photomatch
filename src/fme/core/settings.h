#ifndef FME_SETTINGS_H
#define FME_SETTINGS_H

#include "fme/fme_global.h"

#include <QString>

class QSettings;

namespace fme
{

class FME_EXPORT ISurf
{
public:

  ISurf() {}
  virtual ~ISurf() = default;

  /*!
   * \brief Threshold for hessian keypoint detector used in SURF
   * \return
   */
  virtual double hessianThreshold() const = 0;

  /*!
   * \brief Threshold for hessian keypoint detector used in SURF
   * \param[in] hessianThreshold
   */
  virtual void setHessianThreshold(double hessianThreshold) = 0;

  /*!
   * \brief Number of pyramid octaves the keypoint detector will use.
   * \return
   */
  virtual int octaves() const = 0;

  /*!
   * \brief Set the number of pyramid octaves
   * \param[in] octaves Number of pyramid octaves the keypoint detector will use.
   */
  virtual void setOctaves(int octaves) = 0;

  /*!
   * \brief Number of octave layers within each octave
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief Set the number of octave layers
   * \param[in] octaveLayers Number of octave layers within each octave
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief Extended descriptor
   * \return true (use extended 128-element descriptors) or false (use 64-element descriptors)
   */
  virtual bool extendedDescriptor() const = 0;

  /*!
   * \brief setExtendedDescriptor
   * \param[in] extendedDescriptor true for use extended 128-element descriptors or false for use 64-element descriptors)
   */
  virtual void setExtendedDescriptor(bool extendedDescriptor) = 0;

  /*!
   * \brief Up-right or rotated features
   * \return true (do not compute orientation of features) or false (compute orientation)
   */
  virtual bool rotatedFeatures() const = 0;

  /*!
   * \brief compute orientation of features
   * \param[in] rotatedFeatures false for compute orientation
   */
  virtual void setRotatedFeatures(bool rotatedFeatures) = 0;
};

class FME_EXPORT Surf
  : public ISurf
{

public:

  Surf();
  ~Surf() override;

  // ISurf interface

public:

  double hessianThreshold() const override;
  void setHessianThreshold(double hessianThreshold) override;
  int octaves() const override;
  void setOctaves(int octaves) override;
  int octaveLayers() const override;
  void setOctaveLayers(int octaveLayers) override;
  bool extendedDescriptor() const override;
  void setExtendedDescriptor(bool extendedDescriptor) override;
  bool rotatedFeatures() const override;
  void setRotatedFeatures(bool rotatedFeatures) override;

protected:

  double mHessianThreshold;
  int mOctaves;
  int mOctaveLayers;
  bool mExtendedDescriptor;
  bool mRotatedFeatures;
};


class FME_EXPORT ISift
{
public:
  ISift() {}
  virtual ~ISift() = default;

  /*!
   * \brief featuresNumber
   * \return
   */
  virtual int featuresNumber() const = 0;

  /*!
   * \brief octaveLayers
   * \return
   */
  virtual int octaveLayers() const = 0;

  /*!
   * \brief contrastThreshold
   * \return
   */
  virtual double contrastThreshold() const = 0;

  /*!
   * \brief edgeThreshold
   * \return
   */
  virtual double edgeThreshold() const = 0;

  /*!
   * \brief sigma
   * \return
   */
  virtual double sigma() const = 0;

  /*!
   * \brief setFeaturesNumber
   * \param featuresNumber
   */
  virtual void setFeaturesNumber(int featuresNumber) = 0;

  /*!
   * \brief setOctaveLayers
   * \param octaveLayers
   */
  virtual void setOctaveLayers(int octaveLayers) = 0;

  /*!
   * \brief setContrastThreshold
   * \param contrastThreshold
   */
  virtual void setContrastThreshold(double contrastThreshold) = 0;

  /*!
   * \brief setEdgeThreshold
   * \param edgeThreshold
   */
  virtual void setEdgeThreshold(double edgeThreshold) = 0;

  /*!
   * \brief setSigma
   * \param sigma
   */
  virtual void setSigma(double sigma) = 0;
};

class FME_EXPORT Sift
  : public ISift
{

public:

  Sift();
  ~Sift() override;

// ISift interface

public:

  int featuresNumber() const override;
  int octaveLayers() const override;
  double contrastThreshold() const override;
  double edgeThreshold() const override;
  double sigma() const override;
  void setFeaturesNumber(int featuresNumber) override;
  void setOctaveLayers(int octaveLayers) override;
  void setContrastThreshold(double contrastThreshold) override;
  void setEdgeThreshold(double edgeThreshold) override;
  void setSigma(double sigma) override;

protected:

  int mFeaturesNumber;
  int mOctaveLayers;
  double mContrastThreshold;
  double mEdgeThreshold;
  double mSigma;
};


class FME_EXPORT ISettings
{

public:

  ISettings() {}
  virtual ~ISettings() = default;

  /*!
   * \brief getLanguage
   * \return
   */
  virtual QString language() const = 0;

  /*!
   * \brief setLanguage
   * \param[in] language
   */
  virtual void setLanguage(const QString &language) = 0;

  virtual ISift *sift() = 0;
  virtual const ISift *sift() const = 0;
  virtual ISurf *surf() = 0;
  virtual const ISurf *surf() const = 0;

  /*!
   * \brief Recupera la configuración por defecto
   */
  virtual void reset() = 0;
};

class FME_EXPORT ISettingsRW
{

public:

  ISettingsRW() {}
  virtual ~ISettingsRW() = default;

  /*!
   * \brief read
   * \return
   */
  virtual void read(ISettings &settings) = 0;

  /*!
   * \brief write
   * \return
   */
  virtual void write(const ISettings &settings) = 0;

};


class FME_EXPORT Settings
  : public ISettings
{

public:

  Settings();
  ~Settings() override;

// ISettings interface

public:

  QString language() const override;
  void setLanguage(const QString &language) override;
  ISift *sift() override;
  const ISift *sift() const override;
  ISurf *surf() override;
  const ISurf *surf() const override;

  void reset() override;

protected:

  QString mLanguage;

  ISift *mSift;
  ISurf *mSurf;
};


class FME_EXPORT SettingsRW
  : public ISettingsRW
{

public:

  explicit SettingsRW();
  ~SettingsRW() override;

// ISettingsRW interface

public:

  void read(ISettings &settings) override;
  void write(const ISettings &settings) override;

protected:

  QSettings *mSettingsRW;

};

} // namespace fme

#endif // FME_SETTINGS_H

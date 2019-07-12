#ifndef FME_SETTINGS_H
#define FME_SETTINGS_H

#include "fme/fme_global.h"

#include <QString>
#include <QStringList>
#include <QSize>

#include "fme/core/features.h"
#include "fme/core/preprocess.h"


class QSettings;

namespace fme
{

/*----------------------------------------------------------------*/

/*!
 * \brief Settings interface
 */
class FME_EXPORT ISettings
{

public:

  ISettings() {}
  virtual ~ISettings() = default;

  /*!
   * \brief Idioma actual
   * \return
   */
  virtual QString language() const = 0;

  /*!
   * \brief Establece el idioma del programa
   * \param[in] language Idioma
   */
  virtual void setLanguage(const QString &language) = 0;

  /*!
   * \brief Historial del proyectos recientes
   * \return Listado con los proyectos recientes
   */
  virtual QStringList history() const = 0;

  /*!
   * \brief Añade un proyecto al historial
   * \param[in] project Fichero de proyecto
   */
  virtual void addToHistory(const QString &project) = 0;

  /*!
   * \brief Borra el historial de proyectos recientes
   */
  virtual void clearHistory() = 0;

  /*!
   * \brief Tamaño máximo del historial
   * \return
   */
  virtual int historyMaxSize() const = 0;

  /*!
   * \brief Establece el tamaño máximo de elementos del historial
   * \param[in] maxSize Tamaño máximo del historial
   */
  virtual void setHistoryMaxSize(int maxSize) = 0;

  virtual IFahe *fahe() = 0;
  virtual const IFahe *fahe() const = 0;

  virtual IAgast *agast() = 0;
  virtual const IAgast *agast() const = 0;
  virtual IAkaze *akaze() = 0;
  virtual const IAkaze *akaze() const = 0;
  virtual ISift *sift() = 0;
  virtual const ISift *sift() const = 0;
  virtual ISurf *surf() = 0;
  virtual const ISurf *surf() const = 0;

  /*!
   * \brief Recupera la configuración por defecto
   */
  virtual void reset() = 0;
};


/*----------------------------------------------------------------*/


/*!
 * \brief Settings read and write interface
 */
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

  virtual void writeHistory(const ISettings &settings) = 0;
};



/*----------------------------------------------------------------*/
/* Feature Detectors/descriptors                                  */
/*----------------------------------------------------------------*/


/*!
 * \brief AGAST detector properties class
 */
class FME_EXPORT Agast
  : public IAgast
{

public:

  Agast();
  ~Agast() override;

// IAgast interface

public:

  int threshold() const override;
  bool nonmaxSuppression() const override;
  QString detectorType() const override;
  void setThreshold(int threshold) override;
  void setNonmaxSuppression(bool nonmaxSuppression) override;
  void setDetectorType(const QString &detectorType) override;
  void reset() override;

protected:

  int mThreshold;
  bool mNonmaxSuppression;
  QString mDetectorType;

};


/*----------------------------------------------------------------*/


/*!
 * \brief AKAZE detector/descriptor properties class
 */
class FME_EXPORT Akaze
  : public IAkaze
{

public:

  Akaze();
  ~Akaze() override;

// IAkaze interface

public:

  QString descriptorType() const override;
  int descriptorSize() const override;
  int descriptorChannels() const override;
  double threshold() const override;
  int octaves() const override;
  int octaveLayers() const override;
  QString diffusivity() const override;
  void setDescriptorType(const QString &descriptorType) override;
  void setDescriptorSize(int descriptorSize) override;
  void setDescriptorChannels(int channels) override;
  void setThreshold(double threshold) override;
  void setOctaves(int octaves) override;
  void setOctaveLayers(int octaveLayers) override;
  void setDiffusivity(const QString &diffusivity) override;
  void reset() override;

protected:

  QString mDescriptorType;
  int mDescriptorSize;
  int mDescriptorChannels;
  double mThreshold;
  int mOctaves;
  int mOctaveLayers;
  QString mDiffusivity;

};


/*----------------------------------------------------------------*/


/*!
 * \brief SURF detector/descriptor properties class
 */
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
  void reset() override;

protected:

  double mHessianThreshold;
  int mOctaves;
  int mOctaveLayers;
  bool mExtendedDescriptor;
  bool mRotatedFeatures;
};


/*----------------------------------------------------------------*/


/*!
 * \brief SIFT detector/descriptor properties class
 */
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
  void reset() override;

protected:

  int mFeaturesNumber;
  int mOctaveLayers;
  double mContrastThreshold;
  double mEdgeThreshold;
  double mSigma;
};


/*----------------------------------------------------------------*/
/* Image preprocessing                                            */
/*----------------------------------------------------------------*/


/*!
 * \brief Fahe image preprocess class
 */
class FME_EXPORT Fahe
  : public IFahe
{

public:

  Fahe();
  ~Fahe() override = default;

  QSize blockSize() const override;
  void setBlockSize(const QSize &blockSize) override;

  void reset() override;

protected:

  QSize mBlockSize;

};


/*----------------------------------------------------------------*/


/*!
 * \brief The Settings class
 */
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

  QStringList history() const override;
  void addToHistory(const QString &project) override;
  void clearHistory() override;
  int historyMaxSize() const override;
  void setHistoryMaxSize(int maxSize) override;

  IFahe *fahe() override;
  const IFahe *fahe() const override;

  IAgast *agast() override;
  const IAgast *agast() const override;
  IAkaze *akaze() override;
  const IAkaze *akaze() const override;
  ISift *sift() override;
  const ISift *sift() const override;
  ISurf *surf() override;
  const ISurf *surf() const override;

  void reset() override;

protected:

  QString mLanguage;
  int mHistoyMaxSize;
  QStringList mHistory;

  IFahe *mFahe;

  IAgast *mAgast;
  IAkaze *mAkaze;
  ISift *mSift;
  ISurf *mSurf;
};


/*----------------------------------------------------------------*/


/*!
 * \brief The SettingsRW class
 */
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
  void writeHistory(const ISettings &settings) override;

protected:

  QSettings *mSettingsRW;

};

} // namespace fme

#endif // FME_SETTINGS_H

#ifndef FME_SETTINGS_MODEL_H
#define FME_SETTINGS_MODEL_H

#include <QObject>

#include "fme/core/settings.h"
#include "fme/ui/mvp.h"

namespace fme
{

class ISettingsModel
  : public IModel/*,
    public ISettings*/
{

  Q_OBJECT

public:

  ISettingsModel(QObject *parent = nullptr) : IModel(parent) {}

  /*!
   * \brief Listado de idiomas disponibles
   * \return
   */
  virtual QStringList languages() const = 0;

  /*!
   * \brief Idioma actual
   * \return
   */
  virtual QString language() const = 0;

  /*!
   * \brief Historial del proyectos recientes
   * \return Listado con los proyectos recientes
   */
  virtual QStringList history() const = 0;

  /*!
   * \brief Historial del proyectos recientes
   * \return Listado con los proyectos recientes
   */
  virtual int historyMaxSize() const = 0;

  virtual QSize faheBlockSize() const = 0;

  virtual QString akazeDescriptorType() const = 0;
  virtual int akazeDescriptorSize() const = 0;
  virtual int akazeDescriptorChannels() const = 0;
  virtual double akazeThreshold() const = 0;
  virtual int akazeOctaves() const = 0;
  virtual int akazeOctaveLayers() const = 0;
  virtual QString akazeDiffusivity() const = 0;

  virtual int agastThreshold() const = 0;
  virtual bool agastNonmaxSuppression() const = 0;
  virtual QString agastDetectorType() const = 0;

  virtual int siftFeaturesNumber() const = 0;
  virtual int siftOctaveLayers() const = 0;
  virtual double siftContrastThreshold() = 0;
  virtual double siftEdgeThreshold() = 0;
  virtual double siftSigma() = 0;

  virtual double surfHessianThreshold() const = 0;
  virtual int surfOctaves() const = 0;
  virtual int surfOctaveLayers() const = 0;
  virtual bool surfExtendedDescriptor() const = 0;
  virtual bool surfRotatedFeatures() const = 0;

  /*!
   * \brief read
   * \return
   */
  virtual void read() = 0;

  /*!
   * \brief write
   * \return
   */
  virtual void write() = 0;

  /*!
   * \brief Comprueba si hay cambios sin guardar en el proyecto
   * \return
   */
  //virtual bool checkUnsavedChanges() const = 0;

public slots:

  /*!
   * \brief Establece el idioma del programa
   * \param[in] language Idioma
   */
  virtual void setLanguage(const QString &language) = 0;

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
   * \brief Establece el tamaño máximo de elementos del historial
   * \param[in] maxSize Tamaño máximo del historial
   */
  virtual void setHistoryMaxSize(int maxSize) = 0;

  virtual void setFaheBlockSize(const QSize &size) = 0;

  virtual void setAgastThreshold(int threshold) = 0;
  virtual void setAgastNonmaxSuppression(bool nonmaxSuppression) = 0;
  virtual void setAgastDetectorType(const QString &detectorType) = 0;

  virtual void setAkazeDescriptorType(const QString &descriptorType) = 0;
  virtual void setAkazeDescriptorSize(int descriptorSize) = 0;
  virtual void setAkazeDescriptorChannels(int channels) = 0;
  virtual void setAkazeThreshold(double threshold) = 0;
  virtual void setAkazeOctaves(int octaves) = 0;
  virtual void setAkazeOctaveLayers(int octaveLayers) = 0;
  virtual void setAkazeDiffusivity(const QString &diffusivity) = 0;

  virtual void setSiftFeaturesNumber(int featuresNumber) = 0;
  virtual void setSiftOctaveLayers(int octaveLayers) = 0;
  virtual void setSiftContrastThreshold(double contrastThreshold) = 0;
  virtual void setSiftEdgeThreshold(double edgeThreshold) = 0;
  virtual void setSiftSigma(double sigma) = 0;

  virtual void setSurfHessianThreshold(double hessianThreshold) = 0;
  virtual void setSurfOctaves(int octaves) = 0;
  virtual void setSurfOctaveLayers(int octaveLayers) = 0;
  virtual void setSurfExtendedDescriptor(bool extendedDescriptor) = 0;
  virtual void setSurfRotatedFeatures(bool rotatedFeatures) = 0;

  virtual void reset() = 0;

signals:

  void unsavedChanges(bool);
};

class SettingsModel
  : public ISettingsModel
{

  Q_OBJECT

public:

  explicit SettingsModel(ISettings *settings,
                         ISettingsRW *settingsRW,
                         QObject *parent = nullptr);
  ~SettingsModel() override;

// IModel interface
public:

  QString language() const override;
  QStringList history() const override;
  int historyMaxSize() const override;

  QSize faheBlockSize() const override;

  int agastThreshold() const override;
  bool agastNonmaxSuppression() const override;
  QString agastDetectorType() const override;

  QString akazeDescriptorType() const override;
  int akazeDescriptorSize() const override;
  int akazeDescriptorChannels() const override;
  double akazeThreshold() const override;
  int akazeOctaves() const override;
  int akazeOctaveLayers() const override;
  QString akazeDiffusivity() const override;

  int siftFeaturesNumber() const override;
  int siftOctaveLayers() const override;
  double siftContrastThreshold() override;
  double siftEdgeThreshold() override;
  double siftSigma() override;

  double surfHessianThreshold() const override;
  int surfOctaves() const override;
  int surfOctaveLayers() const override;
  bool surfExtendedDescriptor() const override;
  bool surfRotatedFeatures() const override;

  QStringList languages() const override;
  void read() override;
  void write() override;


public slots:

  void setLanguage(const QString &language) override;
  void addToHistory(const QString &project) override;
  void clearHistory() override;
  void setHistoryMaxSize(int maxSize) override;

  void setFaheBlockSize(const QSize &size) override;

  void setAgastThreshold(int threshold) override;
  void setAgastNonmaxSuppression(bool nonmaxSuppression) override;
  void setAgastDetectorType(const QString &detectorType) override;

  void setAkazeDescriptorType(const QString &descriptorType) override;
  void setAkazeDescriptorSize(int descriptorSize) override;
  void setAkazeDescriptorChannels(int channels) override;
  void setAkazeThreshold(double threshold) override;
  void setAkazeOctaves(int octaves) override;
  void setAkazeOctaveLayers(int octaveLayers) override;
  void setAkazeDiffusivity(const QString &diffusivity) override;

  void setSurfHessianThreshold(double hessianThreshold) override;
  void setSurfOctaves(int octaves) override;
  void setSurfOctaveLayers(int octaveLayers) override;
  void setSurfExtendedDescriptor(bool extendedDescriptor) override;
  void setSurfRotatedFeatures(bool rotatedFeatures) override;

  void setSiftFeaturesNumber(int featuresNumber) override;
  void setSiftOctaveLayers(int octaveLayers) override;
  void setSiftContrastThreshold(double contrastThreshold) override;
  void setSiftEdgeThreshold(double edgeThreshold) override;
  void setSiftSigma(double sigma) override;

  void reset() override;

private:

  void init() override;

protected:

  ISettings *mSettings;
  ISettingsRW *mSettingsRW;

};

} // namespace fme

#endif // FME_SETTINGS_MODEL_H

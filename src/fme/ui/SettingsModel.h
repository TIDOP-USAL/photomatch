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

  virtual QString language() const = 0;

  virtual double surfHessianThreshold() const = 0;
  virtual int surfOctaves() const = 0;
  virtual int surfOctaveLayers() const = 0;
  virtual bool surfExtendedDescriptor() const = 0;
  virtual bool surfRotatedFeatures() const = 0;

  virtual int siftFeaturesNumber() const = 0;
  virtual int siftOctaveLayers() const = 0;
  virtual double siftContrastThreshold() = 0;
  virtual double siftEdgeThreshold() = 0;
  virtual double siftSigma() = 0;

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

  virtual void setLanguage(const QString &language) = 0;

  virtual void setSurfHessianThreshold(double hessianThreshold) = 0;
  virtual void setSurfOctaves(int octaves) = 0;
  virtual void setSurfOctaveLayers(int octaveLayers) = 0;
  virtual void setSurfExtendedDescriptor(bool extendedDescriptor) = 0;
  virtual void setSurfRotatedFeatures(bool rotatedFeatures) = 0;

  virtual void setSiftFeaturesNumber(int featuresNumber) = 0;
  virtual void setSiftOctaveLayers(int octaveLayers) = 0;
  virtual void setSiftContrastThreshold(double contrastThreshold) = 0;
  virtual void setSiftEdgeThreshold(double edgeThreshold) = 0;
  virtual void setSiftSigma(double sigma) = 0;

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

  double surfHessianThreshold() const override;
  int surfOctaves() const override;
  int surfOctaveLayers() const override;
  bool surfExtendedDescriptor() const override;
  bool surfRotatedFeatures() const override;

  int siftFeaturesNumber() const override;
  int siftOctaveLayers() const override;
  double siftContrastThreshold() override;
  double siftEdgeThreshold() override;
  double siftSigma() override;

  QStringList languages() const override;
  void read() override;
  void write() override;


public slots:

  void setLanguage(const QString &language) override;

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

#ifndef PHOTOMATCH_VGG_WIDGET_H
#define PHOTOMATCH_VGG_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QCheckBox;
class QComboBox;
class QDoubleSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for VGG Widgets
 */
class PHOTOMATCH_EXPORT IVggWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IVggWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IVggWidget() = default;

  virtual QString descriptorType() const = 0;
  virtual double scaleFactor() const = 0;
  virtual double sigma() const = 0;
  virtual bool useNormalizeDescriptor() const = 0;
  virtual bool useNormalizeImage() const = 0;
  virtual bool useScaleOrientation() const = 0;

signals:

  void descriptorTypeChange(QString);
  void scaleFactorChange(double);
  void sigmaChange(double);
  void useNormalizeDescriptorChange(bool);
  void useNormalizeImageChange(bool);
  void useScaleOrientationChange(bool);

public slots:

  virtual void setDescriptorType(const QString &descriptorType) = 0;
  virtual void setScaleFactor(double scaleFactor) = 0;
  virtual void setSigma(double sigma) = 0;
  virtual void setUseNormalizeDescriptor(bool active) = 0;
  virtual void setUseNormalizeImage(bool active) = 0;
  virtual void setUseScaleOrientation(bool active) = 0;
};




class PHOTOMATCH_EXPORT VggWidget
  : public IVggWidget
{
  Q_OBJECT

public:

  VggWidget(QWidget *parent = nullptr);
  ~VggWidget() override;

// IVggWidget interface

public:

  QString descriptorType() const override;
  double scaleFactor() const override;
  double sigma() const override;
  bool useNormalizeDescriptor() const override;
  bool useNormalizeImage() const override;
  bool useScaleOrientation() const override;

public slots:

  void setDescriptorType(const QString &descriptorType) override;
  void setScaleFactor(double scaleFactor) override;
  void setSigma(double sigma) override;
  void setUseNormalizeDescriptor(bool active) override;
  void setUseNormalizeImage(bool active) override;
  void setUseScaleOrientation(bool active) override;

// PhotoMatchWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QComboBox *mDescriptorType;
  QDoubleSpinBox *mScaleFactor;
  QDoubleSpinBox *mSigma;
  QCheckBox *mUseNormalizeDescriptor;
  QCheckBox *mUseNormalizeImage;
  QCheckBox *mUseScaleOrientation;

};

} // namespace photomatch

#endif // PHOTOMATCH_VGG_WIDGET_H

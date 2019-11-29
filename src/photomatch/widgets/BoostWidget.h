#ifndef PHOTOMATCH_BOOST_WIDGET_H
#define PHOTOMATCH_BOOST_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QCheckBox;
class QComboBox;
class QDoubleSpinBox;

namespace photomatch
{

/*!
 * \brief Interface for BOOST Widgets
 */
class PHOTOMATCH_EXPORT IBoostWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IBoostWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IBoostWidget() = default;

  virtual QString descriptorType() const = 0;
  virtual bool useOrientation() const = 0;
  virtual double scaleFactor() const = 0;

signals:

  void descriptorTypeChange(QString);
  void useOrientationChange(bool);
  void scaleFactorChange(double);
  
public slots:

  virtual void setDescriptorType(const QString &descriptorType) = 0;
  virtual void setUseOrientation(bool useOrientation) = 0;
  virtual void setScaleFactor(double scaleFactor) = 0;

};

class PHOTOMATCH_EXPORT BoostWidget
  : public IBoostWidget
{
  Q_OBJECT

public:

  BoostWidget(QWidget *parent = nullptr);
  ~BoostWidget() override;

// IBoostWidget interface

public:

  QString descriptorType() const override;
  bool useOrientation() const override;
  double scaleFactor() const override;
  
public slots:

  void setDescriptorType(const QString &descriptorType) override;
  void setUseOrientation(bool useOrientation) override;
  void setScaleFactor(double scaleFactor) override;
  
// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

  void reset() override;

private:

  void init() override;

protected:

  QComboBox *mDescriptorType;
  QCheckBox *mUseOrientation;
  QDoubleSpinBox *mScaleFactor;
  
};

} // namespace photomatch

#endif // PHOTOMATCH_BOOST_WIDGET_H

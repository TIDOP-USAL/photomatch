#ifndef PHOTOMATCH_GFTT_WIDGET_H
#define PHOTOMATCH_GFTT_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT IGfttWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IGfttWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IGfttWidget() = default;

  virtual int maxFeatures() const = 0;
  virtual double qualityLevel() const = 0;
  virtual double minDistance() const = 0;
  virtual int blockSize() const = 0;
  virtual bool harrisDetector() const = 0;
  virtual double k() const = 0;

signals:

  void maxFeaturesChange(int);
  void qualityLevelChange(double);
  void minDistanceChange(double);
  void blockSizeChange(int);
  void harrisDetectorChange(bool);
  void kChange(double);

public slots:

  virtual void setMaxFeatures(int maxFeatures) = 0;
  virtual void setQualityLevel(double qlevel) = 0;
  virtual void setMinDistance(double minDistance) = 0;
  virtual void setBlockSize(int blockSize) = 0;
  virtual void setHarrisDetector(bool value) = 0;
  virtual void setK(double k) = 0;
};

class PHOTOMATCH_EXPORT GfttWidget
  : public IGfttWidget
{
  Q_OBJECT

public:

  GfttWidget(QWidget *parent = nullptr);
  ~GfttWidget() override;

// IGfttWidget interface

public:

  int maxFeatures() const override;
  double qualityLevel() const override;
  double minDistance() const override;
  int blockSize() const override;
  bool harrisDetector() const override;
  double k() const override;

public slots:

  void setMaxFeatures(int maxFeatures) override;
  void setQualityLevel(double qlevel) override;
  void setMinDistance(double minDistance) override;
  void setBlockSize(int blockSize) override;
  void setHarrisDetector(bool value) override;
  void setK(double k) override;

// PhotoMatchWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mMaxFeatures;
  QDoubleSpinBox *mQualityLevel;
  QDoubleSpinBox *mMinDistance;
  QSpinBox *mBlockSize;
  QCheckBox *mHarrisDetector;
  QDoubleSpinBox *mK;
};

} // namespace photomatch

#endif // PHOTOMATCH_GFTT_WIDGET_H

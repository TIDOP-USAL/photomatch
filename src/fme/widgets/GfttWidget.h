#ifndef FME_GFTT_WIDGET_H
#define FME_GFTT_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;

namespace fme
{

class FME_EXPORT IGfttWidget
  : public QWidget
{
  Q_OBJECT

public:

  IGfttWidget(QWidget *parent = nullptr) : QWidget(parent){}
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

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;
};

class FME_EXPORT GfttWidget
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

} // namespace fme

#endif // FME_GFTT_WIDGET_H

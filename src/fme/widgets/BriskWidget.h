#ifndef FME_BRISK_WIDGET_H
#define FME_BRISK_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;

namespace fme
{

class FME_EXPORT IBriskWidget
  : public QWidget
{
  Q_OBJECT

public:

  IBriskWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IBriskWidget() = default;

  virtual int threshold() const = 0;
  virtual int octaves() const = 0;
  virtual double patternScale() const = 0;

signals:

  void thresholdChange(int);
  void octavesChange(int);
  void patternScaleChange(double);

public slots:

  virtual void setThreshold(int threshold) = 0;
  virtual void setOctaves(int octaves) = 0;
  virtual void setPatternScale(double patternScale) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class FME_EXPORT BriskWidget
  : public IBriskWidget
{
  Q_OBJECT

public:

  BriskWidget(QWidget *parent = nullptr);
  ~BriskWidget() override;

// IBriskWidget interface

  int threshold() const override;
  int octaves() const override;
  double patternScale() const override;

public slots:

  void setThreshold(int threshold) override;
  void setOctaves(int octaves) override;
  void setPatternScale(double patternScale) override;

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mThreshold;
  QSpinBox *mOctaves;
  QDoubleSpinBox *mPatternScale;
};

} // namespace fme

#endif // FME_BRISK_WIDGET_H

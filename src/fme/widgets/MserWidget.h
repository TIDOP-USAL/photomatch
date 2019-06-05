#ifndef FME_MSER_WIDGET_H
#define FME_MSER_WIDGET_H

#include "fme/fme_global.h"

#include <QWidget>

class QSpinBox;
class QDoubleSpinBox;

namespace fme
{

class FME_EXPORT IMserWidget
  : public QWidget
{
  Q_OBJECT

public:

  IMserWidget(QWidget *parent = nullptr) : QWidget(parent){}
  virtual ~IMserWidget() = default;

  virtual int delta() const = 0;
  virtual int minArea() const = 0;
  virtual int maxArea() const = 0;
  virtual double maxVariation() const = 0;
  virtual double minDiversity() const = 0;
  virtual int maxEvolution() const = 0;
  virtual double areaThreshold() const = 0;
  virtual double minMargin() const = 0;
  virtual int edgeBlurSize() const = 0;

signals:

  void deltaChange(int);
  void minAreaChange(int);
  void maxAreaChange(int);
  void maxVariationChange(double);
  void minDiversityChange(double);
  void maxEvolutionChange(int);
  void areaThresholdChange(double);
  void minMarginChange(double);
  void edgeBlurSizeChange(int);

public slots:

  virtual void setDelta(int delta) = 0;
  virtual void setMinArea(int minArea) = 0;
  virtual void setMaxArea(int maxArea) = 0;
  virtual void setMaxVariation(double maxVariation) = 0;
  virtual void setMinDiversity(double minDiversity) = 0;
  virtual void setMaxEvolution(int maxEvolution) = 0;
  virtual void setAreaThreshold(double areaThreshold) = 0;
  virtual void setMinMargin(double minMargin) = 0;
  virtual void setEdgeBlurSize(int edgeBlurSize) = 0;

  virtual void update() = 0;
  virtual void reset() = 0;

private:

  virtual void init() = 0;

};

class FME_EXPORT MserWidget
  : public IMserWidget
{
  Q_OBJECT

public:

  MserWidget(QWidget *parent = nullptr);
  ~MserWidget() override;

  int delta() const override;
  int minArea() const override;
  int maxArea() const override;
  double maxVariation() const override;
  double minDiversity() const override;
  int maxEvolution() const override;
  double areaThreshold() const override;
  double minMargin() const override;
  int edgeBlurSize() const override;

// IMserWidget interface

public slots:

  void setDelta(int delta) override;
  void setMinArea(int minArea) override;
  void setMaxArea(int maxArea) override;
  void setMaxVariation(double maxVariation) override;
  void setMinDiversity(double minDiversity) override;
  void setMaxEvolution(int maxEvolution) override;
  void setAreaThreshold(double areaThreshold) override;
  void setMinMargin(double minMargin) override;
  void setEdgeBlurSize(int edgeBlurSize) override;

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QSpinBox *mDelta;
  QSpinBox *mMinArea;
  QSpinBox *mMaxArea;
  QDoubleSpinBox *mMaxVariation;
  QDoubleSpinBox *mMinDiversity;
  QSpinBox *mMaxEvolution;
  QDoubleSpinBox *mAreaThreshold;
  QDoubleSpinBox *mMinMargin;
  QSpinBox *mEdgeBlurSize;

};

} // namespace fme

#endif // FME_MSER_WIDGET_H

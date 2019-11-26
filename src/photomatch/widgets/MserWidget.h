#ifndef PHOTOMATCH_MSER_WIDGET_H
#define PHOTOMATCH_MSER_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QDoubleSpinBox;

namespace photomatch
{

class PHOTOMATCH_EXPORT IMserWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IMserWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
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

};

class PHOTOMATCH_EXPORT MserWidget
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

// PhotoMatchWidget interface

protected slots:

  void update() override;
  void retranslate() override;

public slots:

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

} // namespace photomatch

#endif // PHOTOMATCH_MSER_WIDGET_H

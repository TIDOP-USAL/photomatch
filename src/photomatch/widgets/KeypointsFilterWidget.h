#ifndef PHOTOMATCH_KEYPOINTS_FILTER_WIDGET_H
#define PHOTOMATCH_KEYPOINTS_FILTER_WIDGET_H

#include "photomatch/widgets/PhotoMatchWidget.h"

class QSpinBox;
class QDoubleSpinBox;
class QCheckBox;

namespace photomatch
{

class IKeypointsFilterWidget
  : public PhotoMatchWidget
{
  Q_OBJECT

public:

  IKeypointsFilterWidget(QWidget *parent = nullptr) : PhotoMatchWidget(parent){}
  virtual ~IKeypointsFilterWidget() = default;

  virtual int nPoints() const = 0;
  virtual double minSize() const = 0;
  virtual double maxSize() const = 0;

  virtual bool isActiveFilterBest() const = 0;
  virtual bool isActiveFilterSize() const = 0;

signals:

  void nPointsChange(int);
  void minSizeChange(double);
  void maxSizeChange(double);

public slots:

  virtual void setNPoints(int nPoints) = 0;
  virtual void setMinSize(double minSize) = 0;
  virtual void setMaxSize(double maxSize) = 0;

};


class KeypointsFilterWidget
  : public IKeypointsFilterWidget
{
  Q_OBJECT

public:

  KeypointsFilterWidget(QWidget *parent = nullptr);
  ~KeypointsFilterWidget() override;

// IKeypointsFilterWidget interface

public:

  int nPoints() const override;
  double minSize() const override;
  double maxSize() const override;
  bool isActiveFilterBest() const override;
  bool isActiveFilterSize() const override;

public slots:

  void setNPoints(int nPoints) override;
  void setMinSize(double minSize) override;
  void setMaxSize(double maxSize) override;

// PhotoMatchWidget interface

public slots:

  void update() override;
  void reset() override;

private:

  void init() override;

protected:

  QCheckBox *mCheckBoxPointsNumber;
  QSpinBox *mPointsNumber;
  QCheckBox *mCheckBoxSize;
  QDoubleSpinBox *mMinSize;
  QDoubleSpinBox *mMaxSize;
  bool bActiveFilterBest;
  bool bActiveFilterSize;
};

} // namespace photomatch

#endif // PHOTOMATCH_KEYPOINTS_FILTER_WIDGET_H

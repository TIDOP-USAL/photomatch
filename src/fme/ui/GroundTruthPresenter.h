#ifndef FME_GROUND_TRUTH_PRESENTER_H
#define FME_GROUND_TRUTH_PRESENTER_H

#include <memory>

#include <QObject>

#include "fme/ui/mvp.h"

namespace fme
{

class IGroundTruthView;
class IGroundTruthModel;
class Help;

class IGroundTruthPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IGroundTruthPresenter(){}
  virtual ~IGroundTruthPresenter() override {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void loadGroundTruth(const QString &imageLeft, const QString &imageRight) = 0;
  //virtual void markedLeftPoint(const QPointF &pt) = 0;
  //virtual void markedRightPoint(const QPointF &pt) = 0;
  virtual void addPoint(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2) = 0;
  virtual void importGroundTruth() = 0;

  virtual void save() = 0;
  virtual void discart() = 0;

signals:

  void groundTruthAdded();

};

class GroundTruthPresenter
  : public IGroundTruthPresenter
{

  Q_OBJECT

public:

  GroundTruthPresenter(IGroundTruthView *view,
                       IGroundTruthModel *model);
  ~GroundTruthPresenter() override;

// IGroundTruthPresenter interface

protected slots:

  void loadLeftImage(const QString &image) override;
  void loadRightImage(const QString &image) override;
  void loadGroundTruth(const QString &imageLeft, const QString &imageRight) override;
  //void markedLeftPoint(const QPointF &pt) override;
  //void markedRightPoint(const QPointF &pt) override;
  void addPoint(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2) override;
  void importGroundTruth() override;

  void save() override;
  void discart() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;

private:

  void init() override;

private:

  IGroundTruthView *mView;
  IGroundTruthModel *mModel;
  std::shared_ptr<Help> mHelp;

};

} // namespace fme

#endif // FME_GROUND_TRUTH_PRESENTER_H

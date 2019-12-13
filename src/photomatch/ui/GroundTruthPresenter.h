#ifndef PHOTOMATCH_GROUND_TRUTH_PRESENTER_H
#define PHOTOMATCH_GROUND_TRUTH_PRESENTER_H

#include <memory>

#include <QObject>

#include "photomatch/ui/mvp.h"

namespace photomatch
{

class IGroundTruthView;
class IGroundTruthModel;
class ISettingsModel;
class HelpDialog;

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
  virtual void addHomologousPoints(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2) = 0;
  virtual void deleteHomologous(const QString &image1, const QString &image2, int pointId) = 0;
  virtual void importGroundTruth() = 0;
  virtual void selectHomologous(const QString &image1, const QString &image2, int pointId) = 0;
  virtual void leftPointClicked(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual void rightPointClicked(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual void findLeftPoint(const QString &image1, const QString &image2, const QPointF &pt) = 0;
  virtual void findRightPoint(const QString &image1, const QString &image2, const QPointF &pt) = 0;

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
                       IGroundTruthModel *model,
                       ISettingsModel *settings);
  ~GroundTruthPresenter() override;

// IGroundTruthPresenter interface

protected slots:

  void loadLeftImage(const QString &image) override;
  void loadRightImage(const QString &image) override;
  void loadGroundTruth(const QString &imageLeft, const QString &imageRight) override;
  void addHomologousPoints(const QString &image1, const QPointF &pt1, const QString &image2, const QPointF &pt2) override;
  void deleteHomologous(const QString &image1, const QString &image2, int pointId) override;
  void importGroundTruth() override;
  void selectHomologous(const QString &image1, const QString &image2, int pointId) override;
  void leftPointClicked(const QString &image1, const QString &image2, const QPointF &pt) override;
  void rightPointClicked(const QString &image1, const QString &image2, const QPointF &pt) override;
  void findLeftPoint(const QString &image1, const QString &image2, const QPointF &pt) override;
  void findRightPoint(const QString &image1, const QString &image2, const QPointF &pt) override;

  void save() override;
  void discart() override;

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  void setHelp(std::shared_ptr<HelpDialog> &help) override;

private:

  void init() override;

private:

  IGroundTruthView *mView;
  IGroundTruthModel *mModel;
  ISettingsModel *mSettingsModel;
  std::shared_ptr<HelpDialog> mHelp;

};

} // namespace photomatch

#endif // PHOTOMATCH_GROUND_TRUTH_PRESENTER_H

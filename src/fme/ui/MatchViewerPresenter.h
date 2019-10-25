#ifndef FME_MATCH_VIEWER_PRESENTER_H
#define FME_MATCH_VIEWER_PRESENTER_H

#include <memory>

#include <QObject>

#include "fme/ui/mvp.h"

namespace fme
{

class IMatchViewerView;
class IMatchViewerModel;
class Help;

/*!
 * \brief The IMatchViewerPresenter class
 */
class IMatchViewerPresenter
  : public IPresenter
{

  Q_OBJECT

public:

  IMatchViewerPresenter(){}
  virtual ~IMatchViewerPresenter() {}

protected slots:

  virtual void loadLeftImage(const QString &image) = 0;
  virtual void loadRightImage(const QString &image) = 0;
  virtual void loadMatches(const QString &imageLeft, const QString &imageRight) = 0;
  virtual void deleteMatch(const QString &imageLeft, const QString &imageRight, int query_id, int train_id) = 0;
};


class MatchViewerPresenter
  : public IMatchViewerPresenter
{
  Q_OBJECT

public:

  MatchViewerPresenter(IMatchViewerView *view,
                       IMatchViewerModel *model);

  ~MatchViewerPresenter() override;

protected slots:

  void loadLeftImage(const QString &image) override;
  void loadRightImage(const QString &image) override;
  void loadMatches(const QString &imageLeft, const QString &imageRight) override;
  void deleteMatch(const QString &imageLeft, const QString &imageRight, int query_id, int train_id) override;

  //void save();
  //void discart();

// IPresenter interface

public slots:

  void help() override;
  void open() override;
  //void setHelp(std::shared_ptr<Help> &help) override;

private:

  void init() override;

// IMatchViewerPresenter interface

public slots:

// IMatchViewerPresenter interface

protected slots:

private:

  IMatchViewerView *mView;
  IMatchViewerModel *mModel;
//  IProjectModel *mProjectModel;
//  ISettingsModel *mSettingsModel;
  std::shared_ptr<Help> mHelp;

};

} // namespace fme

#endif // MATCHVIEWERPRESENTER_H

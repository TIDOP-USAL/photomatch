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

  virtual void leftImageChange(const QString &image) = 0;
  virtual void rightImageChange(const QString &image) = 0;
  virtual void loadMatches(const QString &imageLeft, const QString &imageRight) = 0;

};


class MatchViewerPresenter
  : public IMatchViewerPresenter
{
  Q_OBJECT

public:

  MatchViewerPresenter(IMatchViewerView *view, IMatchViewerModel *model);


protected slots:

  void leftImageChange(const QString &image) override;
  void rightImageChange(const QString &image) override;
  void loadMatches(const QString &imageLeft, const QString &imageRight) override;

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
  std::shared_ptr<Help> mHelp;

};

} // namespace fme

#endif // MATCHVIEWERPRESENTER_H

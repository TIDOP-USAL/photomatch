#ifndef FME_MATCH_VIEWER_MODEL_H
#define FME_MATCH_VIEWER_MODEL_H

#include <memory>

#include "fme/core/settings.h"
#include "fme/ui/mvp.h"

namespace fme
{

class Image;
class Camera;

/*!
 * \brief The IMatchViewerModel class
 */
class IMatchViewerModel
  : public IModel
{

  Q_OBJECT

public:

  IMatchViewerModel() {}

  virtual ~IMatchViewerModel() {}

  virtual void load() = 0;
  virtual void save() = 0;

  virtual std::vector<QString> images() const = 0;
  virtual std::vector<QString> imagePairs(const QString &image) const = 0;
  virtual std::vector<std::pair<QPointF, QPointF>> loadMatches(const QString &file1, const QString &file2) const = 0;

public slots:

};


class MatchViewerModel
  : public IMatchViewerModel
{

public:

  MatchViewerModel();


// IModel interface

private:

  void init() override;

// IMatchViewerModel interface

public:

  void load() override;
  void save() override;
  std::vector<QString> images() const override;
  std::vector<QString> imagePairs(const QString &image) const override;
  std::vector<std::pair<QPointF, QPointF> > loadMatches(const QString &file1, const QString &file2) const override;
};

} // namespace fme

#endif // FME_MATCH_VIEWER_MODEL_H

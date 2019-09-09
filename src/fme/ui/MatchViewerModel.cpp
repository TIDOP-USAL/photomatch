#include "MatchViewerModel.h"

namespace fme
{

MatchViewerModel::MatchViewerModel()
{

}

void MatchViewerModel::init()
{
}

void MatchViewerModel::load()
{
}

void MatchViewerModel::save()
{
}

std::vector<QString> MatchViewerModel::images() const
{
  return std::vector<QString>();
}

std::vector<QString> MatchViewerModel::imagePairs(const QString &image) const
{
  return std::vector<QString>();
}

std::vector<std::pair<QPointF, QPointF> > MatchViewerModel::loadMatches(const QString &file1, const QString &file2) const
{
  return std::vector<std::pair<QPointF, QPointF>>();
}

} // namespace fme

#include "tsfssortfilterproxymodel.h"

TSFSSortFilterProxyModel::TSFSSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool TSFSSortFilterProxyModel::filterAcceptsRow(
    int sourceRow, const QModelIndex &sourceParent) const {
  QRegExp rx = filterRegExp();
  bool result = false;

  // Match current item
  QModelIndex itemIndex = sourceModel()->index(sourceRow, 0, sourceParent);
  int matchResult = rx.indexIn(
      itemIndex.data(TSFSModel::ItemData::AbsoluteFilePath).toString());
  if (matchResult != -1)
    return true;

  // Iterate over children and try to find a match recursively
  if (sourceModel()->hasChildren(itemIndex)) {
    int childrenTotal = sourceModel()->rowCount(itemIndex);
    for (int i = 0; i < childrenTotal; i++) {
      if (result)
        break;

      result = result | filterAcceptsRow(i, itemIndex);
    }
  }

  return result;
}

bool TSFSSortFilterProxyModel::lessThan(const QModelIndex &left,
                                        const QModelIndex &right) const {
  QString leftPath = sourceModel()
                         ->data(left, TSFSModel::ItemData::AbsoluteFilePath)
                         .toString();
  QString rightPath = sourceModel()
                          ->data(right, TSFSModel::ItemData::AbsoluteFilePath)
                          .toString();
  bool leftIsDir =
      sourceModel()->data(left, TSFSModel::ItemData::IsDirectory).toBool();
  bool rightIsDir =
      sourceModel()->data(right, TSFSModel::ItemData::IsDirectory).toBool();

  // Directories first
  if (leftIsDir && !rightIsDir)
    return false;
  if (rightIsDir && !leftIsDir)
    return true;

  return leftPath.localeAwareCompare(rightPath) > 0;
}

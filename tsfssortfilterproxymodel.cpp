#include "tsfssortfilterproxymodel.h"

TSFSSortFilterProxyModel::TSFSSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent) {}

bool TSFSSortFilterProxyModel::filterAcceptsRow(
    int sourceRow, const QModelIndex &sourceParent) const {
  QRegExp rx = filterRegExp();
  bool result = false;

  // Match current item
  QModelIndex itemIndex = sourceModel()->index(sourceRow, 0, sourceParent);
  int matchResult = rx.indexIn(itemIndex.data(Qt::UserRole).toString());
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

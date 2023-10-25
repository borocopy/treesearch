#ifndef TSFSSORTFILTERPROXYMODEL_H
#define TSFSSORTFILTERPROXYMODEL_H

#include "tsfsmodel.h"
#include <QSortFilterProxyModel>

class TSFSSortFilterProxyModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  TSFSSortFilterProxyModel(QObject *parent = nullptr);

protected:
  bool filterAcceptsRow(int sourceRow,
                        const QModelIndex &sourceParent) const override;
  bool lessThan(const QModelIndex &left,
                const QModelIndex &right) const override;
};

#endif // TSFSSORTFILTERPROXYMODEL_H

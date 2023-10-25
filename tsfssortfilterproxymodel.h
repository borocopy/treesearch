#ifndef TSFSSORTFILTERPROXYMODEL_H
#define TSFSSORTFILTERPROXYMODEL_H

#include <QSortFilterProxyModel>

class TSFSSortFilterProxyModel : public QSortFilterProxyModel {
  Q_OBJECT
public:
  TSFSSortFilterProxyModel(QObject *parent = nullptr);

protected:
  bool filterAcceptsRow(int sourceRow,
                        const QModelIndex &sourceParent) const override;
};

#endif // TSFSSORTFILTERPROXYMODEL_H

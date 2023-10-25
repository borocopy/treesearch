#ifndef TSFSWORKER_H
#define TSFSWORKER_H

#include "tsfsmodel.h"
#include <QObject>

class TSFSWorker : public QObject {
  Q_OBJECT
public:
  explicit TSFSWorker(TSFSModel *model, QObject *parent = nullptr);

signals:
  void fsTreeHasBeenBuilt();

public slots:
  void buildFSTree();

private:
  TSFSModel *fsModel;
};

#endif // TSFSWORKER_H

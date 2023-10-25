#ifndef TREESEARCH_H
#define TREESEARCH_H

#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>

#include "tsfsmodel.h"
#include "tsfssortfilterproxymodel.h"
#include "tsfsworker.h"
#include "tsheader.h"

class TreeSearch : public QWidget {
  Q_OBJECT

public:
  TreeSearch(QWidget *parent = nullptr);
  ~TreeSearch();

public slots:
  void on_filterQuerySubmitted(const QString &query);
  void on_fsTreeHasBeenBuilt();

private:
  // Build UI
  void initUI();
  // Connect signals to slots
  void initSignalHandlers();
  // Widgets declarations
  TSHeader *header;
  QTreeView *fsTreeView;

  // File System model
  void initFSModel();
  TSFSModel *fsModel;
  // Proxy model for filtering
  TSFSSortFilterProxyModel *fsProxyModel;
};
#endif // TREESEARCH_H

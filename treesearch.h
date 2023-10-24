#ifndef TREESEARCH_H
#define TREESEARCH_H

#include <QTreeView>
#include <QVBoxLayout>
#include <QWidget>

#include "tsfsmodel.h"
#include "tsheader.h"

class TreeSearch : public QWidget {
  Q_OBJECT

public:
  TreeSearch(QWidget *parent = nullptr);
  ~TreeSearch();

private:
  // Build UI
  void initUI();
  // Connect signals to slots
  void initSignalHandlers();
  // Widgets declarations
  TSHeader *header;
  QTreeView *fsTreeView;

  void initFSModel();
  TSFSModel *fsModel;
};
#endif // TREESEARCH_H

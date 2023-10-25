#include "treesearch.h"

TreeSearch::TreeSearch(QWidget *parent) : QWidget(parent) {
  initUI();
  initFSModel();
  connect(header, &TSHeader::filterQuerySubmitted, this,
          &TreeSearch::on_filterQuerySubmitted);
}

TreeSearch::~TreeSearch() {}

void TreeSearch::initUI() {
  // Window settings
  resize(640, 480);
  setWindowTitle("Дерево файловой системы");

  // Build UI
  header = new TSHeader();
  fsTreeView = new QTreeView();

  QVBoxLayout *centralLayout = new QVBoxLayout();
  centralLayout->addWidget(header);
  centralLayout->addWidget(fsTreeView);

  setLayout(centralLayout);
}

void TreeSearch::initFSModel() {
  QString homePath = qgetenv("HOME");
  fsModel = new TSFSModel(homePath);
  fsProxyModel = new TSFSSortFilterProxyModel();

  // Build FS tree in another thread
  QThread *fsWorkerThread = new QThread();
  TSFSWorker *fsWorker = new TSFSWorker(fsModel);
  fsWorker->moveToThread(fsWorkerThread);

  connect(fsWorkerThread, &QThread::started, fsWorker,
          &TSFSWorker::buildFSTree);
  // FS tree built hook
  connect(fsWorker, &TSFSWorker::fsTreeHasBeenBuilt, this,
          &TreeSearch::on_fsTreeHasBeenBuilt);

  fsWorkerThread->start();
}

void TreeSearch::on_fsTreeHasBeenBuilt() {
  fsProxyModel->setSourceModel(fsModel);
  fsTreeView->setModel(fsProxyModel);
  fsTreeView->setUniformRowHeights(true);
  fsTreeView->setSortingEnabled(true);
}

void TreeSearch::on_filterQuerySubmitted(const QString &query) {
  if (query.isEmpty()) {
    fsProxyModel->setFilterRegExp("");
    return;
  }
  fsProxyModel->setFilterWildcard(query);
}

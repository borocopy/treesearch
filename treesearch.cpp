#include "treesearch.h"

TreeSearch::TreeSearch(QWidget *parent) : QWidget(parent) {
  initUI();
  initFSModel();
  connect(headerWidget, &TSHeader::filterQuerySubmitted, this,
          &TreeSearch::on_filterQuerySubmitted);
}

TreeSearch::~TreeSearch() {}

void TreeSearch::initUI() {
  // Window settings
  resize(640, 480);
  setWindowTitle("Дерево файловой системы");

  // Build UI
  headerWidget = new TSHeader();
  progressWidget = new TSProgress();
  fsTreeView = new QTreeView();

  // Hide before FS Tree is fully loaded
  fsTreeView->setHidden(true);

  QVBoxLayout *centralLayout = new QVBoxLayout();
  centralLayout->setAlignment(Qt::AlignJustify | Qt::AlignTop);

  centralLayout->addWidget(headerWidget);
  centralLayout->addWidget(progressWidget);
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

  // Show loading bar
  progressWidget->setStepsTotal(fsModel->countItemsInRootDir());
  connect(fsWorker, &TSFSWorker::fsTreeRootDirectoryChildHasBeenProcessed,
          progressWidget, &TSProgress::on_directoryScanned);

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

  progressWidget->setHidden(true);
  fsTreeView->setHidden(false);
}

void TreeSearch::on_filterQuerySubmitted(const QString &query) {
  if (query.isEmpty()) {
    fsProxyModel->setFilterRegExp("");
    return;
  }
  fsProxyModel->setFilterWildcard(query);
}

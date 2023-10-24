#include "treesearch.h"

TreeSearch::TreeSearch(QWidget *parent) : QWidget(parent) {
  initUI();
  initFSModel();
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
  // Offload it to a thread, show user a spinner while loading
  fsModel = new TSFSModel(homePath);
  fsTreeView->setModel(fsModel);
  fsTreeView->setUniformRowHeights(true);
}

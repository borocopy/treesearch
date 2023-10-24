#include "treesearch.h"

TreeSearch::TreeSearch(QWidget *parent) : QWidget(parent) { initUI(); }

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

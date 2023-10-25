#include "tsfsworker.h"

TSFSWorker::TSFSWorker(TSFSModel *model, QObject *parent) : QObject(parent) {
  fsModel = model;
}

void TSFSWorker::buildFSTree() {
  QStandardItem *rootElement = fsModel->getRootElement();
  // Iterate over every file starting from rootPath
  QDirIterator it(rootElement->data(Qt::UserRole).toString(),
                  QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden |
                      QDir::System,
                  QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);

  while (it.hasNext()) {
    it.next();
    // Get current file info
    QFileInfo fileinfo = it.fileInfo();
    QString canonicalPath = fileinfo.canonicalPath();
    QString fileName = fileinfo.fileName();
    // Create new item
    QStandardItem *item = new QStandardItem(fileName);
    item->setData(fileinfo.absoluteFilePath(), Qt::UserRole);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    // Set corresponding icon
    if (fileinfo.isDir()) {
      item->setIcon(QIcon::fromTheme("folder"));
    } else {
      item->setIcon(QIcon::fromTheme("text-x-generic"));
    }

    // Every absolutePath works as a UID so we can infer parent from it,
    // because QDirIterator will always first return a parent directory
    // before any of the directory children
    QModelIndexList parentIndex = fsModel->match(
        rootElement->index(), Qt::UserRole, fileinfo.absolutePath(), 1,
        Qt::MatchRecursive | Qt::MatchExactly);

    // Always has one and only one element
    QStandardItem *parent = fsModel->itemFromIndex(parentIndex.at(0));
    parent->appendRow(item);

    if (parent == rootElement) {
      emit fsTreeRootDirectoryChildHasBeenProcessed();
    }
  }

  emit fsTreeHasBeenBuilt();
}

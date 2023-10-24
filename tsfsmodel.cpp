#include "tsfsmodel.h"
#include <QDebug>

TSFSModel::TSFSModel(const QString &rootPath, QObject *parent)
    : QStandardItemModel(parent) {

  rootDir = new QDir(rootPath);
  QStandardItem *invisibleRoot = invisibleRootItem();
  rootElement = new QStandardItem(rootPath);
  rootElement->setData(rootPath, Qt::UserRole);
  rootElement->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
  rootElement->setIcon(QIcon::fromTheme("user-home"));
  invisibleRoot->appendRow(rootElement);

  QStringList headerLabels;
  headerLabels << "Название";
  setHorizontalHeaderLabels(headerLabels);

  QDirIterator it(rootPath,
                  QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden,
                  QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);

  while (it.hasNext()) {
    QFile file(it.next());
    QFileInfo fileinfo = it.fileInfo();
    QString canonicalPath = fileinfo.canonicalPath();
    QString fileName = fileinfo.fileName();
    QStandardItem *item = new QStandardItem(fileName);
    item->setData(fileinfo.absoluteFilePath(), Qt::UserRole);
    item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);

    if (fileinfo.isDir()) {
      item->setIcon(QIcon::fromTheme("folder"));
    } else {
      item->setIcon(QIcon::fromTheme("text-x-generic"));
    }

    QModelIndexList parentIndex =
        match(rootElement->index(), Qt::UserRole, fileinfo.absolutePath(), 1,
              Qt::MatchRecursive | Qt::MatchExactly);
    if (parentIndex.count() > 0) {
      QStandardItem *parent = itemFromIndex(parentIndex.at(0));
      parent->appendRow(item);
    }
  }
}

// QStandardItem *TSFSModel::findElementByAbsolutePath(const QString &path,
//                                                    QStandardItem *parent) {
//  // Parent found
//  if (parent->data(Qt::UserRole).toString() == path) {
//    return parent;
//  }
//  // No parent found at all
//  if (!parent->hasChildren())
//    return nullptr;

//  for (int i = 0; i < parent->rowCount(); i++) {
//    QModelIndex idx = parent->index();
//     findElementByAbsolutePath(path, ));
//  }
//}

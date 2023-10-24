#include "tsfsmodel.h"
#include <QDebug>

TSFSModel::TSFSModel(const QString &rootPath, QObject *parent)
    : QStandardItemModel(parent) {

  rootDir = new QDir(rootPath);
  rootElement = invisibleRootItem();
  rootElement->setText(rootPath);

  qDebug() << rootPath;

  QDirIterator it(rootPath,
                  QDir::NoDotAndDotDot | QDir::AllEntries | QDir::Hidden,
                  QDirIterator::Subdirectories | QDirIterator::FollowSymlinks);

  while (it.hasNext()) {
    QString dir = it.next();
    QStandardItem *item = new QStandardItem(dir);
    rootElement->appendRow(item);
    qDebug() << dir;
  }
}

#include "tsfsmodel.h"

TSFSModel::TSFSModel(const QString &rootPath, QObject *parent)
    : QStandardItemModel(parent) {

  QStandardItem *invisibleRoot = invisibleRootItem();
  rootElement = new QStandardItem(rootPath);
  rootElement->setData(rootPath, Qt::UserRole);
  rootElement->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable);
  rootElement->setIcon(QIcon::fromTheme("user-home"));
  invisibleRoot->appendRow(rootElement);

  QStringList headerLabels;
  headerLabels << "Название";
  setHorizontalHeaderLabels(headerLabels);
}

QStandardItem *TSFSModel::getRootElement() { return rootElement; }

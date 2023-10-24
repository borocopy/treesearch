#ifndef TSFSMODEL_H
#define TSFSMODEL_H

#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QStandardItem>
#include <QStandardItemModel>

class TSFSModel : public QStandardItemModel {
  Q_OBJECT
public:
  TSFSModel(const QString &rootPath, QObject *parent = nullptr);

private:
  QDir *rootDir;
  QStandardItem *rootElement;
  QStandardItem *findElementByAbsolutePath(const QString &path,
                                           QStandardItem *item);
};

#endif // TSFSMODEL_H

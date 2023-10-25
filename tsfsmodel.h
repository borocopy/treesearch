#ifndef TSFSMODEL_H
#define TSFSMODEL_H

#include <QDir>
#include <QDirIterator>
#include <QFileInfo>
#include <QStandardItem>
#include <QStandardItemModel>
#include <QThread>

class TSFSModel : public QStandardItemModel {
  Q_OBJECT
public:
  TSFSModel(const QString &rootPath, QObject *parent = nullptr);

  QStandardItem *getRootElement();
  qsizetype countItemsInRootDir();

  enum ItemData { AbsoluteFilePath = Qt::UserRole, IsDirectory };

private:
  QStandardItem *rootElement;
  QStandardItem *findElementByAbsolutePath(const QString &path,
                                           QStandardItem *item);
  void buildFSTree();
};

#endif // TSFSMODEL_H

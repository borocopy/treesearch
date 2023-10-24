#ifndef TSHEADER_H
#define TSHEADER_H

#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

class TSHeader : public QWidget {
  Q_OBJECT
public:
  explicit TSHeader(QWidget *parent = nullptr);

signals:
  void filterQuerySubmitted(const QString &query);

public slots:
  void on_filterQuerySubmit();

private:
  void initUI();
  QLabel *headerLabel;
  QLineEdit *searchLineEdit;
  QPushButton *searchButton;
};

#endif // TSHEADER_H

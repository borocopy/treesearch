#ifndef TSPROGRESS_H
#define TSPROGRESS_H

#include <QLabel>
#include <QProgressBar>
#include <QVBoxLayout>
#include <QWidget>

class TSProgress : public QWidget {
  Q_OBJECT
public:
  explicit TSProgress(QWidget *parent = nullptr);
  ~TSProgress();
  void setStepsTotal(qsizetype steps);

public slots:
  void on_directoryScanned();

private:
  void initUI();
  QLabel *infoLabel;
  QProgressBar *progressBar;

  // Progress bar current value
  int value;
  // Increment value
  void incrementValue();
};

#endif // TSPROGRESS_H

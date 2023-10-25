#include "tsprogress.h"

TSProgress::TSProgress(QWidget *parent) : QWidget(parent) {
  initUI();
  value = 0;
  progressBar->setValue(value);
}

TSProgress::~TSProgress() {}

void TSProgress::initUI() {
  infoLabel = new QLabel();
  progressBar = new QProgressBar();
  QVBoxLayout *progressLayout = new QVBoxLayout();

  infoLabel->setText("Загрузка файловой системы. Пожалуйста, подождите.");

  progressLayout->addWidget(infoLabel);
  progressLayout->addWidget(progressBar);
  setLayout(progressLayout);

  setMaximumHeight(80);
}

void TSProgress::setStepsTotal(qsizetype steps) {
  progressBar->setMinimum(0);
  progressBar->setMaximum(steps);
}

void TSProgress::incrementValue() {
  value++;
  progressBar->setValue(value);
}

void TSProgress::on_directoryScanned() { incrementValue(); }

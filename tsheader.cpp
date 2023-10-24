#include "tsheader.h"

TSHeader::TSHeader(QWidget *parent) : QWidget(parent) {
  initUI();
  connect(searchLineEdit, &QLineEdit::returnPressed, this,
          &TSHeader::on_filterQuerySubmit);
  connect(searchButton, &QPushButton::clicked, this,
          &TSHeader::on_filterQuerySubmit);
}

void TSHeader::initUI() {
  headerLabel = new QLabel("Введите строку для поиска:");
  searchButton = new QPushButton("Найти");
  searchLineEdit = new QLineEdit();

  QVBoxLayout *headerLayout = new QVBoxLayout();
  QHBoxLayout *searchLayout = new QHBoxLayout();

  searchLayout->addWidget(searchLineEdit);
  searchLayout->addWidget(searchButton);

  headerLayout->addWidget(headerLabel);
  headerLayout->addLayout(searchLayout);

  setLayout(headerLayout);
}

void TSHeader::on_filterQuerySubmit() {
  const QString &query = searchLineEdit->text();
  emit filterQuerySubmitted(query);
}

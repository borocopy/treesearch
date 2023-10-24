#include "treesearch.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TreeSearch w;
    w.show();
    return a.exec();
}

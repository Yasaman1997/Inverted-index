#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <set>
#include <cstdlib>

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

#include <QApplication>

#include "DataManager.h"

int main(int argc, char *argv[])
{
    QApplication myApp(argc, argv);

    DataManager dataManager;
    dataManager.show();
    return myApp.exec();
}
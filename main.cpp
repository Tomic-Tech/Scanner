#include <QtGui/QApplication>
#include "manager.h"

int main(int argc, char *argv[])
{
    Manager m(argc, argv);
    return m.exec();
}

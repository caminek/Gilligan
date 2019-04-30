#include "gilligan.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Gilligan window;
    window.show();

    return application.exec();
}

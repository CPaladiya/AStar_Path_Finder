#include <QtWidgets/QApplication>
#include "Window.h"

//This is the main file that starts the instance of window. It contains members of all the other class
//it will hand over control to the qt module.

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Window window;
    window.show();
    return app.exec();
}
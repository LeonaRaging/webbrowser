#include <QApplication>
#include "URL.hpp"
#include "Browser.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Browser browser;
    browser.load(URL(argv[1]));
    return app.exec();
}
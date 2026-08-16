#include <QApplication>
#include "network/URL.hpp"
#include "browser/Browser.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    Browser browser;
    browser.chrome->new_tab(argv[1]);
    return app.exec();
}
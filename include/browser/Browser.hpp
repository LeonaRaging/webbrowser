#include <QMainWindow>
#include "browser/Chrome.hpp"

struct Browser {
    QMainWindow window;
    Chrome* chrome;

    Browser();
};
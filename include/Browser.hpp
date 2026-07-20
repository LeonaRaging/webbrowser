#include "URL.hpp"
#include "Canvas.hpp"
#include <QMainWindow>

struct Browser {
    QMainWindow window;
    Canvas* canvas;
    void load(URL url);
    Browser();
};
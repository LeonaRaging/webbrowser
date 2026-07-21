#include "URL.hpp"
#include "Canvas.hpp"
#include <QMainWindow>
#include <Text.hpp>
#include <Tag.hpp>

struct Browser {
    QMainWindow window;
    Canvas* canvas;
    void load(URL url);
    Browser();
};
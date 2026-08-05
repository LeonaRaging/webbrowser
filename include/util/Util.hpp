#pragma once

#include <vector>
#include <QString>

const int HSTEP = 13;
const int VSTEP = 18;
const int WIDTH = 800;
const int HEIGHT = 600;
const int SCROLL_STEP = 100;

extern int scroll_pos;

inline bool contains(const std::vector<QString>& vec, const QString& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}
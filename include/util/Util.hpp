#pragma once

#include <vector>
#include <QString>

const int HSTEP = 13;
const int VSTEP = 18;
const int WIDTH = 800;
const int HEIGHT = 600;
const int SCROLL_STEP = 100;

template <typename T>
inline bool contains(const std::vector<T>& vec, const T& value) {
    return std::find(vec.begin(), vec.end(), value) != vec.end();
}

template <typename T>
inline void tree_to_list(T* tree, std::vector<T*>& list) {
    list.push_back(tree);
    for (auto& child : tree->children) {
        tree_to_list(child.get(), list);
    }
}
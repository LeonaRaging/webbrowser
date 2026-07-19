#include "URL.hpp"
#include <iostream>

void show(std::string body) {
    bool in_tag = false;
    for (char c : body) {
        if (c == '<') in_tag = true;
        else if (c == '>') in_tag = false;
        else if (!in_tag) std::cout << c;
    }
}

void load(URL url) {
    std::string body = url.request();
    show(body);
}

int main(int argc, char* argv[])
{
    load(URL(argv[1]));
}
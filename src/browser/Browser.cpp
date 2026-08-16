#include "browser/Browser.hpp"

Browser::Browser() {
    chrome = new Chrome(&window);

    window.setCentralWidget(chrome);

    window.show();
}
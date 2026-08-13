cmake_minimum_required(VERSION 3.16)

project(webbrowser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(webbrowser
    src/main.cpp
    
    src/browser/Browser.cpp 
    src/browser/Canvas.cpp
    
    src/network/URL.cpp
    src/network/TcpConnection.cpp
    src/network/TlsConnection.cpp

    src/html/HTMLParser.cpp

    src/layout/Layout.cpp
    src/layout/BlockLayout.cpp
    src/layout/DocumentLayout.cpp
    src/layout/LineLayout.cpp
    src/layout/TextLayout.cpp

    src/painting/DrawText.cpp
    src/painting/DrawRect.cpp

    src/css/CSSParser.cpp
    src/css/Style.cpp
    src/css/TagSelector.cpp
    src/css/DescendantSelector.cpp

    src/util/Util.cpp
    src/util/CachedFont.cpp
)

target_include_directories(webbrowser PRIVATE include)

target_link_libraries(webbrowser 
    PRIVATE 
        Qt6::Widgets
        OpenSSL::SSL 
        OpenSSL::Crypto
)

configure_file(
    ${CMAKE_SOURCE_DIR}/resources/browser.css
    ${CMAKE_BINARY_DIR}/resources/browser.css
    COPYONLY
)
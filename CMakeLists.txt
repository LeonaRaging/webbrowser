cmake_minimum_required(VERSION 3.16)

project(webbrowser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(webbrowser
    src/main.cpp
    src/URL.cpp
    src/TcpConnection.cpp
    src/TlsConnection.cpp
    src/Browser.cpp
    src/Canvas.cpp
    src/HTMLParser.cpp
)

target_include_directories(webbrowser PRIVATE include)

target_link_libraries(webbrowser 
    PRIVATE 
        Qt6::Widgets
        OpenSSL::SSL 
        OpenSSL::Crypto
)
cmake_minimum_required(VERSION 3.16)

project(webbrowser)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSSL REQUIRED)

add_executable(webbrowser
    src/main.cpp
    src/URL.cpp
    src/TcpConnection.cpp
    src/TlsConnection.cpp
)

target_include_directories(webbrowser PRIVATE include)

target_link_libraries(webbrowser PRIVATE OpenSSL::SSL OpenSSL::Crypto)
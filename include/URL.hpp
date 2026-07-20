#pragma once

#include <cassert>
#include <string>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include "TcpConnection.hpp"
#include "TlsConnection.hpp"

class URL {
    public:
        std::string scheme;
        std::string host;
        std::string port;
        std::string path;
        std::unique_ptr<Connection> conn;

        std::string request();

        URL(const std::string& input);
};
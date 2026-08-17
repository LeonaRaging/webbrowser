#pragma once

#include <cassert>
#include <string>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <memory>
#include <QString>
#include "network/TcpConnection.hpp"
#include "network/TlsConnection.hpp"

class URL {
    public:
        std::string scheme;
        std::string host;
        std::string port;
        std::string path;
        std::string request();
        std::string to_string();
        URL resolve(QString);

        URL(const std::string& input);
        URL();
};
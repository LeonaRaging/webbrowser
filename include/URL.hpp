#include <cassert>
#include <string>
#include <stdexcept>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include "TcpConnection.hpp"
#include "TlsConnection.hpp"
#include <memory>

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
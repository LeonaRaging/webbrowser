#include "TcpConnection.hpp"

int TcpConnection::write(const char* data, size_t len) {
    return send(socket, data, len, 0);
}

int TcpConnection::read(char* buffer, size_t len) {
    return recv(socket, buffer, len, 0);
}

TcpConnection::~TcpConnection() {
    close(socket);
}
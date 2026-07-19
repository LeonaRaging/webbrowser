#include "TlsConnection.hpp"

int TlsConnection::write(const char* data, size_t len)
{
    return SSL_write(ssl, data, len);
}

int TlsConnection::read(char* buffer, size_t len)
{
    return SSL_read(ssl, buffer, len);
}

TlsConnection::~TlsConnection() {
    SSL_shutdown(ssl);
    SSL_free(ssl);
    SSL_CTX_free(ctx);
    close(socket);
}
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <unistd.h>
#include "Connection.hpp"

class TlsConnection : public Connection {
    private:
        SSL* ssl;
        SSL_CTX* ctx;
        int socket;
    public:
        int write(const char* data, size_t len) override;
        int read(char* buffer, size_t len) override;
        explicit TlsConnection(SSL* ssl, SSL_CTX* ctx, int socket): ssl(ssl), ctx(ctx), socket(socket) {}
        ~TlsConnection() override;
};
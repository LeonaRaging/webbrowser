#include "Connection.hpp"
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>

class TcpConnection : public Connection {
    private:
        int socket;
    public:
        int write(const char* data, size_t len) override;
        int read(char* buffer, size_t len) override;
        explicit TcpConnection(int socket): socket(socket) {}
        ~TcpConnection() override;
};
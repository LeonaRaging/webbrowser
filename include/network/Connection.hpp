#pragma once

#include <cstddef>

class Connection {
    public:
        virtual int write(const char* data, size_t len) = 0;
        virtual int read(char* buffer, size_t len) = 0;
        virtual ~Connection() = default;
};
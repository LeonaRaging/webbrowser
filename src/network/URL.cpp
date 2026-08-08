#include "network/URL.hpp"

int connect_to_host(std::string host, std::string port) {
    addrinfo hints{};
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_STREAM;

    addrinfo* result = nullptr;

    int status = getaddrinfo(host.c_str(), port.c_str(), &hints, &result);

    if (status != 0) return -1;

    int s = socket(result->ai_family,
                   result->ai_socktype,
                   result->ai_protocol);
    
    if (s == -1) {
        freeaddrinfo(result);
        return -1;
    }

    if (connect(s, result->ai_addr, result->ai_addrlen) == -1) {
        freeaddrinfo(result);
        return -1;
    }

    freeaddrinfo(result);
    return s;
}

std::string read_all(Connection& conn) {
    std::string response;
    char buffer[4096];

    while (true) {
        int n = conn.read(buffer, sizeof(buffer));

        if (n <= 0)
            break;

        response.append(buffer, n);
    }

    return response;
}

std::string URL::request() {
    int s = connect_to_host(host, port);

    if (s == -1) {
        throw std::runtime_error("socket() failed");
    }

    if (scheme == "http") {
        conn = std::unique_ptr<Connection>(new TcpConnection(s));
    }
    else if (scheme == "https") {
        SSL_CTX* ctx = SSL_CTX_new(TLS_client_method());

        SSL* ssl = SSL_new(ctx);

        SSL_set_fd(ssl, s);

        SSL_set_tlsext_host_name(ssl, host.c_str());

        if (SSL_connect(ssl) != 1) {
            SSL_free(ssl);
            SSL_CTX_free(ctx);
            throw std::runtime_error("TLS handshake failed");
        }

        conn = std::unique_ptr<Connection>(new TlsConnection(ssl, ctx, s));
    }

    std::string request;

    request += "GET " + path + " HTTP/1.0\r\n";
    request += "Host: " + host + "\r\n";
    request += "\r\n";

    ssize_t bytes_send = conn->write(request.c_str(), request.size());

    if (bytes_send <= 0) {
        throw std::runtime_error("send() failed");
    }

    std::string response = read_all(*conn);

    std::istringstream stream(response);

    std::string statusline;
    std::getline(stream, statusline);

    if (!statusline.empty() && statusline.back() == '\r')
        statusline.pop_back();
    
    std::istringstream iss(statusline);

    std::string version;
    std::string status;
    std::string explanation;

    iss >> version;
    iss >> status;
    std::getline(iss, explanation);

    if (!explanation.empty() && explanation.front() == ' ') {
        explanation.erase(0, 1);
    }

    std::unordered_map<std::string, std::string> response_headers;
    std::string line;

    while (std::getline(stream, line)) {
        if (!line.empty() && line.back() == '\r')
            line.pop_back();
        
        if (line.empty()) break;

        std::size_t pos = line.find(':');

        std::string header = line.substr(0, pos);
        std::string value = line.substr(pos + 1);

        std::transform(header.begin(), header.end(), header.begin(), [](unsigned char c) {
            return std::tolower(c);
        });

        if (!value.empty() && value.front() == ' ')
            value.erase(0, 1);
        
        response_headers[header] = value;
    }

    assert(response_headers.find("transfer-encoding") == response_headers.end());
    assert(response_headers.find("content-encoding") == response_headers.end());

    std::string content{
        std::istreambuf_iterator<char>(stream),
        std::istreambuf_iterator<char>()
    };

    return content;
}

URL URL::resolve(QString url) {
    std::string resolved = url.toStdString();

    if (url.contains("://")) return URL(resolved);
    
    if (!(url.startsWith('/'))) {
        int pos = path.rfind('/');
        std::string dir = path.substr(0, pos);
        while (url.startsWith("../")) {
            url.remove(0, 3);
            int dirPos = dir.rfind('/');
            if (dirPos != std::string::npos) {
                dir = dir.substr(0, dirPos);
            }
        }
        resolved = dir + "/" + url.toStdString();
    }

    if (resolved.rfind("//", 0) == 0) {
        return URL(scheme + ":" + resolved);
    }

    return URL(
        scheme + "://" + 
        host + ":" + 
        port + 
        resolved
    );
}

URL::URL(const std::string& input) {
    std::string url = input;

    std::size_t pos = url.find("://");
    assert(pos != std::string::npos);

    scheme = url.substr(0, pos);
    assert(scheme == "http" || scheme == "https");

    if (scheme == "http") port = "80";
    else port = "443";

    url = url.substr(pos + 3);

    if (url.find('/') == std::string::npos) {
        url += '/';
    }

    pos = url.find('/');
    host = url.substr(0, pos);
    path = url.substr(pos);

    std::size_t colon = host.find(':');
    if (colon != std::string::npos) {
        port = host.substr(colon + 1);
        host = host.substr(0, colon);
    }
}
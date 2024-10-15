#include "http_server.hpp"

static void server_usage(const char* proc) {
    std::cout << proc << ": port" << std::endl;
}

int main(int argc, char* argv[]) {
    if(argc != 2) {
        server_usage(argv[1]);
        exit(2);
    }
    Http_Server server(atoi(argv[1]), http_response);
    server.start();
    return 0;
}
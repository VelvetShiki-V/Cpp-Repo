#include "selectServer.hpp"
#include <memory>

int main() {

    std::unique_ptr<selectServer> p(new selectServer());
    p->run();
    return 0;
}
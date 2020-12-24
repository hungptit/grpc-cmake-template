#include "utilities.h"

int main(const int argc, const char *argv[]) {
    const int      count       = argc > 1 ? std::atoi(argv[1]) : 1;
    constexpr char ipaddress[] = "localhost:50051";
    for (auto idx = 0; idx < count; ++idx) {
        if (!utils::is_available(ipaddress, 10, 10)) {
            std::cerr << "Cannot reach the gRPC server at " << ipaddress << "\n";
        }
    }

    return EXIT_SUCCESS;
}

#include "client/utilities.h"
#include "healthcheck.grpc.pb.h"
#include "healthcheck.pb.h"

#include <cstdlib>
#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <grpcpp/impl/codegen/status_code_enum.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <thread>

int main(const int argc, const char *argv[]) {
    constexpr char ipaddress[] = "localhost:50051";
    auto           channel     = grpc::CreateChannel(ipaddress, grpc::InsecureChannelCredentials());
    const int      count       = (argc > 1) ? atoi(argv[1]) : 10;
    const int      interval_ms = 300;
    auto const     status      = utils::get_grpc_health_status(channel, count, interval_ms);
    if (status.is_available()) {
        std::cout << "The gRPC server is serving at " << std::quoted(ipaddress) << "\n";
    } else {
        std::cout << "The gRPC server is not available at " << std::quoted(ipaddress)
                  << ". Error code: " << status.status << "\n";
    }
    return EXIT_SUCCESS;
}

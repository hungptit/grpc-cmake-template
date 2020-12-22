#include "healthcheck.pb.h"

#include <cstdlib>
#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <iomanip>
#include <iostream>
#include <ostream>

void check(const std::string &service_name, const int count = 1) {
    using monitor::HealthCheckResponse;

    constexpr char ipaddress[] = "localhost:50051";

    monitor::HealthCheckRequest query;
    query.set_service(service_name);

    monitor::HealthCheckResponse response;
    auto                         channel = grpc::CreateChannel(ipaddress, grpc::InsecureChannelCredentials());
    auto                         stub    = monitor::Health::NewStub(channel);
    for (int iter = 0; iter < count; ++iter) {
        grpc::ClientContext context;
        grpc::Status        status = stub->Check(&context, query, &response);
        std::cout << "errcode: " << status.error_code() << "\n";
        std::cout << "health-check: request " << query.DebugString() << "\n";
        std::cout << "health-check: response " << response.status() << "\n";
    }
}

int main(const int argc, const char *argv[]) {
    for (auto idx = 1; idx < argc; ++idx) {
        std::cout << "Service: " << argv[idx] << "\n";
        check(argv[idx], 1);
    }
    return EXIT_SUCCESS;
}

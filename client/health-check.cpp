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

namespace std {
    std::string to_string(const grpc::StatusCode errcode) {
        switch (errcode) {
        case grpc::StatusCode::NOT_FOUND:
            return "NOT_FOUND";
        case grpc::StatusCode::OK:
            return "OK";
        default:
            return "UNRECOGNIZED_ERROR_CODE: " + std::to_string(errcode);
        }
    }
} // namespace std

void check(const std::string &service_name, const int count = 1) {
    using grpc::health::v1::HealthCheckRequest;
    using grpc::health::v1::HealthCheckResponse;

    constexpr char ipaddress[] = "localhost:50051";

    HealthCheckRequest query;
    query.set_service(service_name);
    HealthCheckResponse response;

    auto channel = grpc::CreateChannel(ipaddress, grpc::InsecureChannelCredentials());
    auto stub    = grpc::health::v1::Health::NewStub(channel);

    constexpr std::chrono::milliseconds sleep_time(1);

    for (int iter = 0; iter < count; ++iter) {
        std::this_thread::sleep_for(sleep_time);

        const std::chrono::system_clock::time_point deadline =
            std::chrono::system_clock::now() + std::chrono::milliseconds(1000);
        grpc::ClientContext context;
        context.set_deadline(deadline);
        grpc::Status status = stub->Check(&context, query, &response);
        std::cout << "errcode: " << std::to_string(status.error_code()) << "\n";
        std::cout << "health-check: request: {" << query.ShortDebugString() << "}\n";
        std::cout << "health-check: response: {" << response.ShortDebugString() << "}\n";
    }
}

int main(const int argc, const char *argv[]) {
    if (argc > 1) {
        for (auto idx = 1; idx < argc; ++idx) {
            check(std::string(argv[idx]), 1);
        }
    } else {
        check("", 10);
    }

    return EXIT_SUCCESS;
}

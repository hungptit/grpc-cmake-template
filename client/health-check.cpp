#include "client/utilities.h"
#include "healthcheck.grpc.pb.h"
#include "healthcheck.pb.h"

#include <cstdint>
#include <cstdlib>
#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <grpcpp/impl/codegen/status_code_enum.h>
#include <iomanip>
#include <iostream>
#include <ostream>
#include <quill/Quill.h>
#include <quill/detail/LogMacros.h>
#include <thread>

void watch(std::shared_ptr<grpc::Channel> channel, const int sleep_time_ms, const std::uint32_t ntries = 1000,
           const std::string service_name = "") {
    using grpc::health::v1::HealthCheckRequest;
    using grpc::health::v1::HealthCheckResponse;
    using std::chrono::milliseconds;
    auto logger = quill::get_logger();

    const milliseconds sleep_time(sleep_time_ms);

    HealthCheckRequest query;
    query.set_service(service_name);
    HealthCheckResponse response;

    auto stub = grpc::health::v1::Health::NewStub(channel);

    for (uint32_t iter = 0; iter < ntries; ++iter) {
        std::this_thread::sleep_for(sleep_time);
        const std::chrono::system_clock::time_point deadline = std::chrono::system_clock::now() + milliseconds(1000);
        grpc::ClientContext                         context;
        context.set_deadline(deadline);
        response.Clear(); // Reset the response
        auto const reader = stub->Watch(&context, query);
        reader->Read(&response);
        LOG_INFO(logger, "{0}", response.ShortDebugString());
    }
}

int main(const int argc, const char *argv[]) {
    quill::enable_console_colours();
    quill::start();

    constexpr char ipaddress[] = "localhost:50051";
    auto           channel     = grpc::CreateChannel(ipaddress, grpc::InsecureChannelCredentials());
    const int      interval_ms = 300;
    auto const     status      = utils::get_grpc_health_status(channel, 1000, interval_ms);
    auto           logger      = quill::get_logger();
    if (status.is_available()) {
        LOG_INFO(logger, "The gRPC server is serving at \"{0}\"", ipaddress);
    } else {
        LOG_INFO(logger, "The gRPC server is not available at \"{0}\". Error code: {1} ", ipaddress, status.status);
    }

    // Watch the gRPC server
    watch(channel, 100, 1000, argc > 1 ? argv[1] : "");

    return EXIT_SUCCESS;
}

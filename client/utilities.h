#pragma once

#include "healthcheck.grpc.pb.h"
#include "healthcheck.pb.h"
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/impl/codegen/status_code_enum.h>
#include <iostream>
#include <thread>

namespace utils {
    std::string errcode2string(const grpc::StatusCode errcode) {
        switch (errcode) {
        case grpc::StatusCode::NOT_FOUND:
            return "NOT_FOUND";
        case grpc::StatusCode::OK:
            return "OK";
        case grpc::StatusCode::UNAVAILABLE:
            return "UNAVAILABLE";
        case grpc::StatusCode::DEADLINE_EXCEEDED:
            return "DEADLINE_EXCEEDED";
        default:
            return "UNRECOGNIZED_ERROR_CODE: " + std::to_string(errcode);
        }
    }

    struct GRPCHealthInfo {
        grpc::StatusCode                                    errcode = grpc::StatusCode::UNKNOWN;
        grpc::health::v1::HealthCheckResponse_ServingStatus status =
            grpc::health::v1::HealthCheckResponse_ServingStatus::HealthCheckResponse_ServingStatus_UNKNOWN;

        bool is_available() const {
            return (errcode == grpc::OK) &&
                   (status ==
                    grpc::health::v1::HealthCheckResponse_ServingStatus::HealthCheckResponse_ServingStatus_SERVING);
        }
    };

    GRPCHealthInfo get_grpc_health_status(std::shared_ptr<grpc::Channel> channel, const int ntries,
                                          const int miliseconds) {
        using grpc::health::v1::HealthCheckRequest;
        using grpc::health::v1::HealthCheckResponse;
        using std::chrono::milliseconds;

        GRPCHealthInfo results = {};

        const milliseconds sleep_time(miliseconds);
        const std::string  service_name = "";

        HealthCheckRequest query;
        query.set_service(service_name);
        HealthCheckResponse response;

        auto stub = grpc::health::v1::Health::NewStub(channel);

        for (int iter = 0; iter < ntries; ++iter) {
            const std::chrono::system_clock::time_point deadline =
                std::chrono::system_clock::now() + milliseconds(1000);
            grpc::ClientContext context;
            context.set_deadline(deadline);
            response.Clear(); // Reset the response
            auto const status = stub->Check(&context, query, &response);
            if (status.ok()) {
                if (response.status() == grpc::health::v1::HealthCheckResponse_ServingStatus_SERVING) {
                    return {status.error_code(), response.status()};
                }
            }

            const auto errcode = status.error_code();
            std::cout << utils::errcode2string(errcode) << ": " << status.error_message() << "\n";
            results = {errcode, response.status()};
        }

        return results;
    }
} // namespace utils

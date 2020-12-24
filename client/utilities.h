#pragma once

#include "healthcheck.grpc.pb.h"
#include "healthcheck.pb.h"
#include <grpcpp/channel.h>
#include <grpcpp/create_channel.h>
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

    bool is_available(std::shared_ptr<grpc::Channel> channel, const int ntries, const int miliseconds) {
        using grpc::health::v1::HealthCheckRequest;
        using grpc::health::v1::HealthCheckResponse;

        const std::chrono::milliseconds sleep_time(miliseconds);
        const std::string service_name = {""};

        HealthCheckRequest query;
        query.set_service(service_name);
        HealthCheckResponse response;
        auto stub    = grpc::health::v1::Health::NewStub(channel);

        for (int iter = 0; iter < ntries; ++iter) {
            const std::chrono::system_clock::time_point deadline =
                std::chrono::system_clock::now() + std::chrono::milliseconds(1000);
            grpc::ClientContext context;
            context.set_deadline(deadline);
            grpc::Status status = stub->Check(&context, query, &response);
            if (status.ok()) {
                std::cout << "health-check: request: {" << query.ShortDebugString() << "}\n";
                std::cout << "health-check: response: {" << response.ShortDebugString() << "}\n";
                return true;
            }
            std::cout << "errcode: " << errcode2string(status.error_code()) << "\n";
        }

        return false;
    }
} // namespace utils

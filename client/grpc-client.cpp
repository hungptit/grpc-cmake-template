#include "proto/address.pb.h"
#include "proto/addressbook.grpc.pb.h"

#include "quill/Quill.h"

#include <cstdlib>
#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <iomanip>
#include <iostream>
#include <ostream>
#include <quill/detail/LogMacros.h>
#include <thread>

#include "utilities.h"

namespace std {
    ostream &operator<<(ostream &os, const address::Address &address) {
        os << "{" << std::quoted("name") << ":" << std::quoted(address.name()) << "," << std::quoted("street") << ":"
           << std::quoted(address.street()) << "," << std::quoted("zip") << ":" << std::quoted(address.zip()) << ","
           << std::quoted("city") << ":" << std::quoted(address.city()) << "," << std::quoted("country") << ":"
           << std::quoted(address.country()) << "}";
        return os;
    }
} // namespace std

void request(const std::string &username, const int count) {

    constexpr char      ipaddress[] = "localhost:50051";
    address::NameQuerry query;
    address::Address    response;
    query.set_name(username);

    auto channel = grpc::CreateChannel(ipaddress, grpc::InsecureChannelCredentials());
    auto stub    = address::AddressBook::NewStub(channel);

    auto          logger           = quill::get_logger();
    constexpr int polling_interval = 200;
    auto const    status           = utils::get_grpc_health_status(channel, count, polling_interval);
    if (status.is_available()) {
        LOG_INFO(logger, "The gRPC server is serving at \"{0}\"", ipaddress);
    } else {
        LOG_ERROR(logger, "Cannot connect to the gRPC server at \"{0}\"", ipaddress);
        return;
    }

    for (int iter = 0; iter < count; ++iter) {
        const std::chrono::system_clock::time_point deadline =
            std::chrono::system_clock::now() + std::chrono::milliseconds(1000);
        grpc::ClientContext context;
        context.set_deadline(deadline);
        response.Clear();
        const grpc::Status status = stub->GetAddress(&context, query, &response);
        if (!status.ok()) {
            LOG_ERROR(logger, "{}", status.error_message());
        } else {
            LOG_INFO(logger, "{}", response.ShortDebugString());
        }
    }
}

int main(const int argc, const char *argv[]) {
    quill::enable_console_colours();
    quill::start();
    LOG_INFO(quill::get_logger(), "grpc-client");

    const int count = argc > 1 ? std::atoi(argv[1]) : 1;
    request("John", count);
    return EXIT_SUCCESS;
}

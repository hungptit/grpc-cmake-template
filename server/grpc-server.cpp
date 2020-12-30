#include "proto/address.pb.h"
#include "proto/addressbook.grpc.pb.h"

#include "grpc/grpc.h"
#include "grpcpp/server_builder.h"
#include <cassert>
#include <grpcpp/health_check_service_interface.h>

#include <iomanip>
#include <iostream>
#include <quill/Quill.h>
#include <quill/detail/LogMacros.h>
#include <thread>

class AddressBookService final : public address::AddressBook::Service {
  public:
    virtual ::grpc::Status GetAddress(::grpc::ServerContext *, const ::address::NameQuerry *request,
                                      ::address::Address *response) {
        auto logger = quill::get_logger();
        LOG_INFO(logger, "request: {0}", request->ShortDebugString());
        response->set_name("John Doe");
        response->set_zip("12345");
        response->set_country("USA");
        return grpc::Status::OK;
    }
};

int main() {
    constexpr char ipaddress[] = "localhost:50051";

    quill::enable_console_colours();
    quill::start();

    // Enable the default health check service
    grpc::EnableDefaultHealthCheckService(true);
    assert(grpc::DefaultHealthCheckServiceEnabled());

    grpc::ServerBuilder builder;
    builder.AddListeningPort(ipaddress, grpc::InsecureServerCredentials());
    AddressBookService my_service;

    // Delay the startup by sleep_time miliseconds to simulate the gRPC server startup time in production.
    constexpr std::chrono::milliseconds sleep_time(1000);
    std::this_thread::sleep_for(sleep_time);

    builder.RegisterService(&my_service);
    auto server(builder.BuildAndStart());

    // Enable address.AddressBook service and disable the default healthcheck service.
    auto *health_check_service = server->GetHealthCheckService();
    health_check_service->SetServingStatus("", false);
    health_check_service->SetServingStatus("address.AddressBook", true);

    auto logger = quill::get_logger();
    LOG_INFO(logger, "gRPC is listening at: {0}", ipaddress);

    server->Wait();
    return 0;
}

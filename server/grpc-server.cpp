#include "proto/address.pb.h"
#include "proto/addressbook.grpc.pb.h"

#include "grpc/grpc.h"
#include "grpcpp/server_builder.h"
#include <cassert>
#include <grpcpp/health_check_service_interface.h>

#include <iomanip>
#include <iostream>

class AddressBookService final : public address::AddressBook::Service {
  public:
    virtual ::grpc::Status GetAddress(::grpc::ServerContext *, const ::address::NameQuerry *request,
                                      ::address::Address *response) {
        std::cout << "grpc-server: username: " << std::quoted(request->name()) << "\n";
        response->set_name("John Doe");
        response->set_zip("12345");
        response->set_country("USA");
        return grpc::Status::OK;
    }
};

int main() {
    constexpr char ipaddress[] = "localhost:50051";

    // Enable the default health check service
    grpc::EnableDefaultHealthCheckService(true);
    assert(grpc::DefaultHealthCheckServiceEnabled());

    grpc::ServerBuilder builder;
    builder.AddListeningPort(ipaddress, grpc::InsecureServerCredentials());
    AddressBookService my_service;
    builder.RegisterService(&my_service);
    auto server(builder.BuildAndStart());
    std::cout << "Listening at " << ipaddress << "\n";
    server->Wait();
    return 0;
}

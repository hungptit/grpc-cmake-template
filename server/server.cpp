#include "proto/address.pb.h"
#include "proto/addressbook.grpc.pb.h"

#include "grpc/grpc.h"
#include "grpcpp/server_builder.h"

#include <iomanip>
#include <iostream>

class AddressBookService final : public address::AddressBook::Service {
  public:
    virtual ::grpc::Status GetAddress(::grpc::ServerContext *, const ::address::NameQuerry *request,
                                      ::address::Address *response) {
        std::cout << "Server: Query information for: " << std::quoted(request->name()) << "\n";
        response->set_name("John Doe");
        response->set_zip("12345");
        response->set_country("USA");
        return grpc::Status::OK;
    }
};

int main() {
    grpc::ServerBuilder builder;
    builder.AddListeningPort("0.0.0.0:50051", grpc::InsecureServerCredentials());

    AddressBookService my_service;
    builder.RegisterService(&my_service);

    std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
    server->Wait();

    return 0;
}

#include "proto/address.pb.h"
#include "proto/addressbook.grpc.pb.h"

#include <cstdlib>
#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <iomanip>
#include <iostream>
#include <ostream>

namespace std {
    ostream &operator<<(ostream &os, const address::Address &address) {
        os << "{" << std::quoted("name") << ":" << std::quoted(address.name()) << "," << std::quoted("street") << ":"
           << std::quoted(address.street()) << "," << std::quoted("zip") << ":" << std::quoted(address.zip()) << ","
           << std::quoted("city") << ":" << std::quoted(address.city()) << "," << std::quoted("country") << ":"
           << std::quoted(address.country()) << "}";
        return os;
    }
} // namespace std

int main(const int argc, const char *argv[]) {
    const int           count       = argc > 1 ? std::atoi(argv[1]) : 1;
    constexpr char      ipaddress[] = "localhost:50051";
    address::NameQuerry query;
    address::Address    response;
    query.set_name("John");
    auto channel = grpc::CreateChannel(ipaddress, grpc::InsecureChannelCredentials());
    auto stub    = address::AddressBook::NewStub(channel);
    for (int iter = 0; iter < count; ++iter) {
        grpc::ClientContext context;
        grpc::Status        status = stub->GetAddress(&context, query, &response);
        std::cout << "grpc-client: response " << iter << ": " << response << "\n";
    }
    return EXIT_SUCCESS;
}

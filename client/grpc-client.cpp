#include "proto/address.pb.h"
#include "proto/addressbook.grpc.pb.h"

#include <cstdlib>
#include <grpc/grpc.h>
#include <grpcpp/create_channel.h>

#include <iomanip>
#include <iostream>
#include <ostream>
#include <thread>

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

    constexpr std::chrono::milliseconds sleep_time(1);

    for (int iter = 0; iter < count; ++iter) {
        std::this_thread::sleep_for(sleep_time);

        const std::chrono::system_clock::time_point deadline =
            std::chrono::system_clock::now() + std::chrono::milliseconds(1000);
        grpc::ClientContext context;
        context.set_deadline(deadline);
        grpc::Status status = stub->GetAddress(&context, query, &response);
        std::cout << "grpc-client: response " << iter << ": " << response << "\n";
    }
}

int main(const int argc, const char *argv[]) {
    const int count = argc > 1 ? std::atoi(argv[1]) : 1;
    request("John", count);
    return EXIT_SUCCESS;
}

#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "caching_interceptor.h"
#include "grpcpp/grpcpp.h"
#include "proto/keyvaluestore.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using keyvaluestore::KeyValueStore;
using keyvaluestore::Request;
using keyvaluestore::Response;

class KeyValueStoreClient {
  public:
    KeyValueStoreClient(std::shared_ptr<Channel> channel) : stub_(KeyValueStore::NewStub(channel)) {}

    void GetValues(const std::vector<std::string> &keys) {
        ClientContext context;

        auto    stream = stub_->GetValues(&context);
        Request request;
        for (const auto &key : keys) {
            request.Clear();
            request.set_key(key);
            stream->Write(request);

            // Get the value for the sent key
            Response response;
            stream->Read(&response);
            std::cout << key << ": " << response.value() << "\n";
        }
        stream->WritesDone();
        Status status = stream->Finish();
        if (!status.ok()) {
            std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            std::cout << "RPC failed";
        }
    }

  private:
    std::unique_ptr<KeyValueStore::Stub> stub_;
};

int main() {
    const std::string      ipaddress = "localhost:50051";
    grpc::ChannelArguments args;

    // In this example, we are using a cache which has been added in as an
    // interceptor.
    std::vector<std::unique_ptr<grpc::experimental::ClientInterceptorFactoryInterface>> interceptor_creators;
    interceptor_creators.push_back(std::make_unique<CachingInterceptorFactory>());

    auto channel = grpc::experimental::CreateCustomChannelWithInterceptors(
        ipaddress, grpc::InsecureChannelCredentials(), args, std::move(interceptor_creators));

    KeyValueStoreClient            client(channel);
    const std::vector<std::string> keys = {"key1", "key2", "key3", "key4", "key5", "key1", "key2", "key4"};
    client.GetValues(keys);

    return EXIT_SUCCESS;
}

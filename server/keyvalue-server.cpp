/*
 *
 * Copyright 2018 gRPC authors.
 * Copyright 2021 Hung Dang.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#include <cstdlib>
#include <iostream>
#include <map>
#include <memory>
#include <string>

#include "grpcpp/grpcpp.h"

#include "keyvaluestore.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReaderWriter;
using grpc::Status;
using keyvaluestore::KeyValueStore;
using keyvaluestore::Request;
using keyvaluestore::Response;

// Logic and data behind the server's behavior.
class KeyValueStoreServiceImpl final : public KeyValueStore::Service {
    Status GetValues(ServerContext *, ServerReaderWriter<Response, Request> *stream) override {
        Request  request;
        Response response;
        while (stream->Read(&request)) {
            response.Clear();
            auto const it = db.find(request.key());
            response.set_value(it != db.cend() ? it->second : empty_value);
            std::cout << request.key() << ": " << response.value() << "\n";
            stream->Write(response);
        }
        return Status::OK;
    }

  private:
    const std::map<std::string, std::string> db = {
        {"key1", "value1"}, {"key2", "value2"}, {"key3", "value3"}, {"key4", "value4"}, {"key5", "value5"}};
    const std::string empty_value = "";
};

void RunServer(const std::string server_address = "0.0.0.0:50051") {
    KeyValueStoreServiceImpl service;

    ServerBuilder builder;
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    std::unique_ptr<Server> server(builder.BuildAndStart());
    std::cout << "Server listening on " << server_address << std::endl;
    server->Wait();
}

int main() {
    RunServer();
    return EXIT_SUCCESS;
}

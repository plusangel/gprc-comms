#ifndef SERVER_H
#define SERVER_H

#include <iostream>
#include <string>
#include <array>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "platformCommunications.grpc.pb.h"
#include "utils.hpp"

class PlatformCommunicationsImpl final : public platformcomms::PlatformCommunications::Service
{
    grpc::Status Initialize(grpc::ServerContext* context, 
        const platformcomms::InitializationRequest* request, 
        platformcomms::PlatformState* platformState) override;
    
    grpc::Status GoToHeight(grpc::ServerContext* context, 
        const platformcomms::HeightRequest* request, 
        platformcomms::PlatformState* platformState) override;
};

class gRPC_Server {
public:
    gRPC_Server() = delete;
    explicit gRPC_Server(const std::string address); 
    void spin() const;

private:
    std::string server_address;
    grpc::ServerBuilder builder;
    PlatformCommunicationsImpl service;
    std::unique_ptr<grpc::Server> server;
};

#endif //SERVER_H
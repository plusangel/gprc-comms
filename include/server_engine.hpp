#ifndef SERVER_ENGINE_H
#define SERVER_ENGINE_H

#include <iostream>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "platformCommunications.grpc.pb.h"
#include "utils.hpp"

class PlatformCommunicationsImpl final : public platformcomms::PlatformCommunications::Service
{
    // Initialises the mobile platform's state
    grpc::Status Initialize(grpc::ServerContext* context, 
        const platformcomms::InitializationRequest* request, 
        platformcomms::PlatformState* platformState) override;
    
    // Sends the platform to a given height
    grpc::Status GoToHeight(grpc::ServerContext* context, 
        const platformcomms::HeightRequest* request, 
        platformcomms::PlatformState* platformState) override;
    
    // Ensures the platform is stable
    grpc::Status Stabilize(grpc::ServerContext* context, 
        const platformcomms::StabilityRequest* request, 
        platformcomms::PlatformState* platformState) override;
    
    // Make the platform safe
    grpc::Status MakeSafe(grpc::ServerContext* context, 
        const platformcomms::MakeSafeRequest* request, 
        platformcomms::PlatformState* platformState) override;
    
    // Get the current state of the platform
    grpc::Status GetState(grpc::ServerContext* context, 
        const platformcomms::StateRequest* request, 
        platformcomms::PlatformState* platformState) override;
};

#endif //SERVER_H
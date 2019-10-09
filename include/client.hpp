#include <iostream>
#include <string>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "platformCommunications.grpc.pb.h"
#include "utils.hpp"

class PlatformCommunicationsClient {
    public:
    PlatformCommunicationsClient(std::shared_ptr<grpc::Channel> channel);
    
    bool Initialize();

    private:
    std::unique_ptr<platformcomms::PlatformCommunications::Stub> stub_;
};

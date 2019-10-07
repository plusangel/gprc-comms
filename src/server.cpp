#include "server.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::ServerReader;
using grpc::ServerReaderWriter;
using grpc::ServerWriter;
using grpc::Status;

using platformcomms::HeightRequest;
using platformcomms::InitializationRequest;
using platformcomms::MakeSafeRequest;
using platformcomms::StabilityRequest;
using platformcomms::StateRequest;
using platformcomms::TargetRequest;

using platformcomms::Pose;
using platformcomms::Quaternion;
using platformcomms::Vector3D;
using platformcomms::Map;

using platformcomms::Alert;
using platformcomms::PlatformState;

using platformcomms::PlatformCommunications;

class PlatformCommunicationsImpl final : public PlatformCommunications::Service
{
    Status Initialize(ServerContext* context, const InitializationRequest* request,
        PlatformState* platformState) override {
        
        platformState->set_status(platformcomms::Status::Ready);

        Utils::set_pose(platformState->mutable_alertpose(), {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0, 6.0});
        
        platformState->set_liftheight(3.1);
        platformState->set_stable(true);
        platformState->set_batterylevel(5.0);
        
        Alert* alert = platformState->add_alerts();
        Utils::set_alert(alert, "title", 11111, "topic", platformcomms::AlertLevel::Info);

        std::cout << "Hola!" << std::endl;
        return Status::OK;
    }
};

void RunServer()
{
    std::string server_address {"0.0.0.0:50051"};
    PlatformCommunicationsImpl service;

    ServerBuilder builder;
    // Listen on the given address without any authentication mechanism.
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    
    // Register "service" as the instance through which we'll communicate with
    // clients. In this case it corresponds to an *synchronous* service.
    builder.RegisterService(&service);

    std::unique_ptr<Server> server {builder.BuildAndStart()};
    std::cout << "Server listening on " <<server_address << std::endl;

    // Wait for the server to shutdown. Note that some other thread must be
    // responsible for shutting down the server for this call to ever return.
    server->Wait();
}

int main(int argc, char** argv) {
    RunServer();    
    return 0;
}
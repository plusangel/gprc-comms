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

Status PlatformCommunicationsImpl::Initialize(ServerContext* context, 
    const InitializationRequest* request,
    PlatformState* platformState)
{
    
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

gRPC_Server::gRPC_Server(const std::string address) : server_address{address}
{
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    server = builder.BuildAndStart();
    std::cout << "Server goes to listening mode on " <<server_address << std::endl;
}

void gRPC_Server::spin() const
{
    server->Wait();
}
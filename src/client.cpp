#include "client.hpp"

using grpc::Channel;
using grpc::ClientContext;
using grpc::ClientReader;
using grpc::ClientReaderWriter;
using grpc::ClientWriter;
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


PlatformCommunicationsClient::PlatformCommunicationsClient(std::shared_ptr<Channel> channel) :
    stub_(PlatformCommunications::NewStub(channel)) {}
    
    
bool PlatformCommunicationsClient::Initialize()
{
    unsigned int client_connection_timeout = 5000;
    ClientContext context;
    InitializationRequest initialRequest;
    PlatformState platformState;
    
    // Set timeout for API
    std::chrono::system_clock::time_point deadline =
    std::chrono::system_clock::now() + std::chrono::seconds(client_connection_timeout);

    context.set_wait_for_ready(true);
    context.set_deadline(deadline);

    Utils::set_pose(initialRequest.mutable_approximatepose(), {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0, 6.0});

    initialRequest.mutable_approximatemap()->set_imagewidth(2);
    initialRequest.mutable_approximatemap()->set_imageheight(2);
    initialRequest.mutable_approximatemap()->set_resolution(4.0);
    initialRequest.mutable_approximatemap()->set_localisationoccupiedthreshold(6.0);
    initialRequest.mutable_approximatemap()->set_pathplanningoccupiedthreshold(7.0);

    initialRequest.mutable_approximatemap()->mutable_origin()->set_x(0.0);
    initialRequest.mutable_approximatemap()->mutable_origin()->set_y(0.0);
    initialRequest.mutable_approximatemap()->mutable_origin()->set_z(0.0);

    Status status = stub_->Initialize(&context, initialRequest, &platformState);

    if (status.ok()) {
        return true;
    }
    return false;
}

bool PlatformCommunicationsClient::GoToHeight(double desiredHeight)
{
    unsigned int client_connection_timeout = 5000;
    ClientContext context;
    
    // Set timeout for API
    std::chrono::system_clock::time_point deadline =
    std::chrono::system_clock::now() + std::chrono::seconds(client_connection_timeout);

    context.set_wait_for_ready(true);
    context.set_deadline(deadline);

    HeightRequest heightRequest;
    heightRequest.set_height(desiredHeight);
    PlatformState platformState;

    Status status = stub_->GoToHeight(&context, heightRequest, &platformState);

    if (status.ok()) {
        return true;
    }
    return false;
}
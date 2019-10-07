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

class PlatformCommunicationsClient {
    public:
    PlatformCommunicationsClient(std::shared_ptr<Channel> channel) :
        stub_(PlatformCommunications::NewStub(channel)) {}
    
    
    void Initialize()
    {
        ClientContext context;
        InitializationRequest initialRequest;
        PlatformState platformState;
        
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
            std::cout << "GetFeature rpc good." << std::endl;
        }
    }

    private:
    std::unique_ptr<PlatformCommunications::Stub> stub_;
};

int main(int argc, char** argv)
{
    
    PlatformCommunicationsClient robot(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    
    robot.Initialize();
 
    return 0;
}
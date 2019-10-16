#include <vector>
#include "server_engine.hpp"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
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
using platformcomms::AlertLevel;
using platformcomms::PlatformState;
using pStatus = platformcomms::Status;

using platformcomms::PlatformCommunications;

Status PlatformCommunicationsImpl::Initialize(ServerContext* context, 
    const InitializationRequest* request,
    PlatformState* platformState)
{
    platformState->set_status(pStatus::Ready);

    Utils::set_pose(platformState->mutable_alertpose(), {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0, 6.0});
    
    platformState->set_liftheight(3.1);
    platformState->set_stable(true);
    platformState->set_batterylevel(5.0);
    
    Alert* alert = platformState->add_alerts();
    Utils::set_alert(alert, "Initiliazation State", 11111, "topic", AlertLevel::Info);

    std::cout << "Hola Initilization!" << std::endl;
    return Status::OK;
}

Status PlatformCommunicationsImpl::GoToTarget(ServerContext* context,
        const TargetRequest* request, ServerWriter<PlatformState>* writer)
{
    std::vector<PlatformState> dummyList;
    Utils::statesFactory(dummyList);

    for (const PlatformState& p : dummyList)
    {
        writer->Write(p);
    }
    
    return Status::OK;
}

Status PlatformCommunicationsImpl::GoToHeight(ServerContext* context, 
    const HeightRequest* request, PlatformState* platformState)
{
    platformState->set_status(pStatus::Ready);

    Utils::set_pose(platformState->mutable_alertpose(), {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0, 6.0});
    
    platformState->set_liftheight(3.1);
    platformState->set_stable(true);
    platformState->set_batterylevel(5.0);
    
    Alert* alert = platformState->add_alerts();
    Utils::set_alert(alert, "GoToHeight State", 11111, "topic", AlertLevel::Info);

    std::cout << "Hola GoToHeight!" << std::endl;
    return Status::OK;
}


Status PlatformCommunicationsImpl::Stabilize(ServerContext* context, 
    const StabilityRequest* request, PlatformState* platformState)
{
    platformState->set_status(pStatus::Ready);

    Utils::set_pose(platformState->mutable_alertpose(), {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0, 6.0});
    
    platformState->set_liftheight(3.1);
    platformState->set_stable(true);
    platformState->set_batterylevel(5.0);
    
    Alert* alert = platformState->add_alerts();
    Utils::set_alert(alert, "Stabilize State", 11111, "topic", AlertLevel::Info);

    std::cout << "Hola Stabilize!" << std::endl;
    return Status::OK;
}


Status PlatformCommunicationsImpl::MakeSafe(grpc::ServerContext* context, 
    const MakeSafeRequest* request, PlatformState* platformState) 
{
    platformState->set_status(pStatus::Ready);

    Utils::set_pose(platformState->mutable_alertpose(), {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0, 6.0});
    
    platformState->set_liftheight(3.1);
    platformState->set_stable(true);
    platformState->set_batterylevel(5.0);
    
    Alert* alert = platformState->add_alerts();
    Utils::set_alert(alert, "MakeSafe State", 11111, "topic", AlertLevel::Info);

    std::cout << "Hola MakeSafe!" << std::endl;
    return Status::OK;
}


Status PlatformCommunicationsImpl::GetState(grpc::ServerContext* context, 
    const StateRequest* request, PlatformState* platformState)
{
    platformState->set_status(pStatus::Ready);

    Utils::set_pose(platformState->mutable_alertpose(), {0.0, 1.0, 2.0}, {3.0, 4.0, 5.0, 6.0});
    
    platformState->set_liftheight(3.1);
    platformState->set_stable(true);
    platformState->set_batterylevel(5.0);
    
    Alert* alert = platformState->add_alerts();
    Utils::set_alert(alert, "GetState State", 11111, "topic", AlertLevel::Info);

    std::cout << "Hola GetState!" << std::endl;
    return Status::OK;
}
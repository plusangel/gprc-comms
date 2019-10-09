#include <gtest/gtest.h>
#include "client.hpp"

TEST Initialisation(basicComms, test1)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));

    robot.Initialize();

}
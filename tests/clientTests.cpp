#include <gtest/gtest.h>
#include "client.hpp"
#include "yaml-cpp/yaml.h"
#include <iostream>

std::string connection_string;

TEST(clientTests, handshakeInit)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials()));
    
    EXPECT_TRUE(robot.Initialize());
}

TEST(clientTests, handshakeGoToTarget)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials()));
    
    EXPECT_TRUE(robot.Initialize());
}

TEST(clientTests, handshakeGoToHeight)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials()));
    
    EXPECT_TRUE(robot.GoToHeight(3.1));
}

TEST(clientTests, handshakeStabilize)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials()));
    
    EXPECT_TRUE(robot.Stabilize(true));
}

TEST(clientTests, handshakeMakeSafe)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials()));
    
    EXPECT_TRUE(robot.MakeSafe(true));
}

TEST(clientTests, handshakeGetStae)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials()));
    
    EXPECT_TRUE(robot.GetState(true));
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    std::string local_root = argv[1];
    std::string config_file = "config.yaml";

    YAML::Node config = YAML::LoadFile(local_root + "/" + config_file);

    std::string ip = config["IP"].as<std::string>();
    std::string port = config["PORT"].as<std::string>();

    connection_string = ip + ":" + port;
    
    return RUN_ALL_TESTS();
}

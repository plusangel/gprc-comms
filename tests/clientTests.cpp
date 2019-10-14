#include <gtest/gtest.h>
#include "client.hpp"
#include "yaml-cpp/yaml.h"

std::string connection_string;

TEST(clientTests, handshake)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials()));
    
    EXPECT_TRUE(robot.Initialize());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);

    std::string local_root = argv[1];
    
    YAML::Node config = YAML::LoadFile("config.yaml");

    std::string ip = config["IP"].as<std::string>();
    std::string port = config["PORT"].as<std::string>();

    connection_string = ip + ":" + port;
    
    return RUN_ALL_TESTS();
}

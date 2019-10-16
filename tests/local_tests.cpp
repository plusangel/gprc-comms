#include "client.hpp"
#include "yaml-cpp/yaml.h"

int main(int argc, char* argv[])
{
    std::string connection_string;
    std::string local_root = argv[1];
    std::string config_file = "config.yaml";

    YAML::Node config = YAML::LoadFile(local_root + "/" + config_file);

    std::string ip = config["IP"].as<std::string>();
    std::string port = config["PORT"].as<std::string>();

    connection_string = ip + ":" + port;

    PlatformCommunicationsClient robot(grpc::CreateChannel(connection_string, grpc::InsecureChannelCredentials()));

    robot.GoToTarget();

    return 0;
}
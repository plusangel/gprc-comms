#include "server.hpp"
#include "yaml-cpp/yaml.h"
#include <thread>

int main(int argc, char** argv)
{
    std::string local_root = argv[1];
    std::string config_file = "config.yaml";

    YAML::Node config = YAML::LoadFile(local_root + "/" + config_file);

    std::string ip = config["IP"].as<std::string>();
    std::string port = config["PORT"].as<std::string>();

    std::string connection_string = ip + ":" + port;

    std::thread server_thread([connection_string]() {
        gRPC_Server myServer {connection_string};
        myServer.spin();
    });
    
    server_thread.join();

    return 0;
}
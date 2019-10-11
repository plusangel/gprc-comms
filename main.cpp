#include "client.hpp"
#include "server.hpp"
#include <thread>

int main(int argc, char** argv)
{
    std::thread server_thread([]() {
        gRPC_Server myServer {"0.0.0.0:50051"};
        myServer.spin();
    });

    std::thread client_thread([]() {
        PlatformCommunicationsClient robot(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    
        if (robot.Initialize())
            std::cout << "Initialisation sucessfully completed" << std:: endl;
        else
            std::cout << "Error in initialisation" << std::endl;
    });
    
    client_thread.join();
    server_thread.join();

    return 0;
}
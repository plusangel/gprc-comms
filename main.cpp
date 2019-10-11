#include "client.hpp"
#include "server.hpp"

int main(int argc, char** argv)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
   
    if (robot.Initialize())
        std::cout << "Initialisation sucessfully completed" << std:: endl;
    else
        std::cout << "Error in initialisation" << std::endl;

    gRPC_Server myServer {"0.0.0.0:50051"};
    myServer.spin();
     
    return 0;
}
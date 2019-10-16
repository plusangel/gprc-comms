#include "server.hpp"

gRPC_Server::gRPC_Server(const std::string address) : server_address{address}
{
    
    builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
    builder.RegisterService(&service);

    server = builder.BuildAndStart();
    std::cout << "Server goes to listening mode on " <<server_address << std::endl;
}

void gRPC_Server::spin() const
{
    server->Wait();
}
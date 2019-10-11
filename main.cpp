#include "server.hpp"
#include <thread>

int main(int argc, char** argv)
{
    std::thread server_thread([]() {
        gRPC_Server myServer {"0.0.0.0:50051"};
        myServer.spin();
    });
    
    server_thread.join();

    return 0;
}
#include <gtest/gtest.h>
#include "client.hpp"

TEST(basicComms, handshake)
{
    PlatformCommunicationsClient robot(grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials()));
    
    EXPECT_TRUE(robot.Initialize());
}

int main(int argc, char* argv[])
{
    testing::InitGoogleTest(&argc, argv);
    
    return RUN_ALL_TESTS();
}

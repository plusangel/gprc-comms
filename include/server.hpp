#include <iostream>
#include <string>
#include <array>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>
#include <grpcpp/server_context.h>
#include <grpcpp/security/server_credentials.h>

#include "platformCommunications.grpc.pb.h"
#include "utils.hpp"
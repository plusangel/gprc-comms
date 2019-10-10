project(grpc-route)
cmake_minimum_required(VERSION 3.2)

add_compile_options(-std=c++17)

include_directories(include)

# gtests stuff
# https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# utils library for convenience
add_library(utils ${CMAKE_CURRENT_SOURCE_DIR}/include/utils.hpp)
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)

# GRPC and Protocol Buffers libraries location
#list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")
LINK_DIRECTORIES(/usr/local/lib/)
TARGET_LINK_LIBRARIES(protobuf libprotobuf)
TARGET_LINK_LIBRARIES(gRPC libgrpc)
#list(APPEND CMAKE_PREFIX_PATH "/usr/local/lib/")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
if (Protobuf_FOUND)
    message(STATUS "Libraries for Protobuf found")
else()
    message(FATAL_ERROR "Failed to find Protobuf.")
endif()

find_package(GRPC REQUIRED)
if (GRPC_FOUND)
    message(STATUS "Libraries for GRPC found")
else()
    message(FATAL_ERROR "Failed to find GRPC.")
endif()

set(PROTOS
    ${CMAKE_CURRENT_SOURCE_DIR}/protos/platformCommunications.proto
)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

# Building server
add_executable(server
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_link_libraries(server
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    utils
)

# Building client
add_executable(client
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_link_libraries(client
    gRPC::grpc++_reflection
    protobuf::libprotobuf
    utils
)

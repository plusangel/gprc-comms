project(grpc-route)
cmake_minimum_required(VERSION 3.2)

add_compile_options(-std=c++17)


# gtests stuff
# https://www.eriksmistad.no/getting-started-with-google-test-on-ubuntu/
enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# utils library for convenience
add_library(utils ${CMAKE_CURRENT_SOURCE_DIR}/include/utils.hpp)
set_target_properties(utils PROPERTIES LINKER_LANGUAGE CXX)

# GRPC and Protocol Buffers libraries location
list(APPEND CMAKE_PREFIX_PATH "/opt/grpc" "/opt/protobuf")

# Cmake find modules
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

find_package(Protobuf REQUIRED)
set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
if (Protobuf_FOUND)
    message(STATUS "Libraries for Protobuf found")
    message(STATUS "Using protobuf ${protobuf_VERSION}")
else()
    message(FATAL_ERROR "Failed to find Protobuf.")
endif()

find_package(GRPC REQUIRED)
set(_GRPC_GRPCPP_REFLECTION gRPC::grpc++_reflection)
if (GRPC_FOUND)
    message(STATUS "Libraries for GRPC found")
    message(STATUS "Using gRPC ${gRPC_VERSION}")
else()
    message(FATAL_ERROR "Failed to find GRPC.")
endif()

set(PROTOS ${CMAKE_CURRENT_SOURCE_DIR}/proto/platformCommunications.proto)

set(PROTO_SRC_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto-src)
file(MAKE_DIRECTORY ${PROTO_SRC_DIR})
include_directories(${PROTO_SRC_DIR})

include_directories(
    ${CMAKE_SOURCE_DIR}/include
)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS ${PROTO_SRC_DIR} ${PROTOS})
grpc_generate_cpp(GRPC_SRCS GRPC_HDRS ${PROTO_SRC_DIR} ${PROTOS})

# Building server
add_library(server
    ${CMAKE_CURRENT_SOURCE_DIR}/src/server.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_link_libraries(server
    ${_GRPC_GRPCPP_REFLECTION}
    ${_PROTOBUF_LIBPROTOBUF}
    utils
)

# Building client
add_library(client
    ${CMAKE_CURRENT_SOURCE_DIR}/src/client.cpp
    ${PROTO_SRCS}
    ${GRPC_SRCS}
)

target_link_libraries(client
    ${_GRPC_GRPCPP_REFLECTION}
    ${_PROTOBUF_LIBPROTOBUF}
    utils
)

# Building demo main
add_executable(comm
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(comm
    server
)

# build the tests
add_executable(tests 
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/basicTests.cpp
)

target_link_libraries(tests 
    gtest 
    gtest_main
    client
)

add_test(tests 
    tests
)
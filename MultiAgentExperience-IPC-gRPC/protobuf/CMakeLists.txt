include(proto.cmake)

get_filename_component(maxrpc_proto "maxrpc.proto" ABSOLUTE)
get_filename_component(maxrpc_proto_path "${maxrpc_proto}" PATH)

# Generated sources
set(maxrpc_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/maxrpc.pb.cc")
set(maxrpc_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/maxrpc.pb.h")
set(maxrpc_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/maxrpc.grpc.pb.cc")
set(maxrpc_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/maxrpc.grpc.pb.h")

add_custom_command(
        OUTPUT "${maxrpc_proto_srcs}" "${maxrpc_proto_hdrs}" "${maxrpc_grpc_srcs}" "${maxrpc_grpc_hdrs}"
        COMMAND ${_PROTOBUF_PROTOC}
        ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
        -I "${maxrpc_proto_path}"
        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
        "${maxrpc_proto}"
        DEPENDS "${maxrpc_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
# rg_grpc_proto
add_library(maxrpc_grpc_proto
        ${maxrpc_grpc_srcs}
        ${maxrpc_grpc_hdrs}
        ${maxrpc_proto_srcs}
        ${maxrpc_proto_hdrs})

target_link_libraries(maxrpc_grpc_proto
        ${_REFLECTION}
        ${_GRPC_GRPCPP}
        ${_PROTOBUF_LIBPROTOBUF})


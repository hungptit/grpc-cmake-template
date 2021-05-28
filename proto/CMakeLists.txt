if(MSVC)
  add_definitions(-D_WIN32_WINNT=0x600)
endif()

find_package(Threads REQUIRED)

include(FetchContent)
FetchContent_Declare(
  grpc
  GIT_REPOSITORY https://github.com/grpc/grpc.git
  GIT_TAG master)
FetchContent_MakeAvailable(grpc)

set(PROTO_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(CODEGEN_DIR "${CMAKE_CURRENT_BINARY_DIR}/codegen")
set(SOURCE_FILES)
set(HEADER_FILES)
set(PROTO_FILES)
set(TARGETS address addressbook healthcheck helloworld keyvaluestore)

foreach(target ${TARGETS})
  set(BASE_PATH "${CODEGEN_DIR}/${target}")
  list(APPEND SOURCE_FILES "${BASE_PATH}.pb.cc" "${BASE_PATH}.grpc.pb.cc")
  list(APPEND HEADER_FILES "${BASE_PATH}.pb.h" "${BASE_PATH}.grpc.pb.h")
  list(APPEND PROTO_FILES "${PROTO_DIR}/${target}.proto")
endforeach()

file(MAKE_DIRECTORY ${CODEGEN_DIR})

# Generate code for given proto files.
add_custom_command(
  OUTPUT ${SOURCE_FILES} ${HEADER_FILES}
  COMMAND
    $<TARGET_FILE:protoc> ARGS --grpc_out "${CODEGEN_DIR}" --cpp_out
    "${CODEGEN_DIR}" --proto_path ${PROTO_DIR}
    --plugin=protoc-gen-grpc="$<TARGET_FILE:grpc_cpp_plugin>" ${PROTO_FILES}
  DEPENDS ${PROTO_FILES}
  COMMENT "Generate C++ header and source files.")

# Create the library.
set(LIBNAME "address")
add_library(${LIBNAME} STATIC ${SOURCE_FILES})
target_include_directories(${LIBNAME} PRIVATE "${CODEGEN_DIR}")
target_link_libraries(${LIBNAME} PUBLIC grpc grpc++ libprotobuf)

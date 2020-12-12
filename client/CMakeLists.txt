find_package(Threads)
set(SRC_FILE grpc-client)
add_executable(${SRC_FILE} ${SRC_FILE}.cpp)
target_link_libraries(${SRC_FILE} PRIVATE address)

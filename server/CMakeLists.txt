find_package(Threads)
set(SRC_FILE grpc-server)
add_executable(${SRC_FILE} ${SRC_FILE}.cpp)
target_link_libraries(${SRC_FILE} PRIVATE address)

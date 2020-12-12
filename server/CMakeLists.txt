find_package(Threads)
set(SRC_FILES server.cpp)
add_executable(server ${SRC_FILES})
target_link_libraries(server PRIVATE address)

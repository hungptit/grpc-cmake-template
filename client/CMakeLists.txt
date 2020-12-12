find_package(Threads)
set(SRC_FILES client.cpp)
add_executable(client ${SRC_FILES})
target_link_libraries(client PRIVATE address)

if(MSVC)
  add_compile_options(/W2 /WX)
else()
  add_compile_options(-Wall -Wextra -static)
endif()

find_package(Threads)
set(SRC_FILES grpc-server greeter_server keyvalue-server)

foreach(src_file ${SRC_FILES})
  add_executable(${src_file} ${src_file}.cpp)
  target_link_libraries(${src_file} PRIVATE address)
endforeach(src_file)

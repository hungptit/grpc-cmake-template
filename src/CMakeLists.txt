project(grpc-examples)

set(CPP_FILES greeter_server greeter_client)
foreach(src_file ${CPP_FILES})
  add_executable(${src_file} ${src_file}.cc)
  target_link_libraries(${src_file} grpc++)
endforeach(src_file)

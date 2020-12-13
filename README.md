# Introduction #

This repository is a CMake template for my C++ projects that use [gRPC](https://github.com/grpc/grpc). 

# Build instruction #

## macOS and Linux ##

### Build gRPC ###

``` shell
git submodule --init
git submodule --update
cd 3p
./build_using_cmake.sh 3p
```

### Build client and server examples ###

``` shell
cmake ./
make
```

Below is the sample output obtained using my Linux box

``` text
hungptit@hung-hien ~/working/grpc-cmake-template $ make -k
/home/hungptit/working/centos/bin/cmake -S/home/hungptit/working/grpc-cmake-template -B/home/hungptit/working/grpc-cmake-template --check-build-system CMakeFiles/Makefile.cmake 0
/home/hungptit/working/centos/bin/cmake -E cmake_progress_start /home/hungptit/working/grpc-cmake-template/CMakeFiles /home/hungptit/working/grpc-cmake-template//CMakeFiles/progress.marks
make  -f CMakeFiles/Makefile2 all
make[1]: Entering directory '/home/hungptit/working/grpc-cmake-template'
make  -f CMakeFiles/lint.dir/build.make CMakeFiles/lint.dir/depend
make[2]: Entering directory '/home/hungptit/working/grpc-cmake-template'
cd /home/hungptit/working/grpc-cmake-template && /home/hungptit/working/centos/bin/cmake -E cmake_depends "Unix Makefiles" /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template/CMakeFiles/lint.dir/DependInfo.cmake --color=
make[2]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
make  -f CMakeFiles/lint.dir/build.make CMakeFiles/lint.dir/build
make[2]: Entering directory '/home/hungptit/working/grpc-cmake-template'
[  5%] Lint Bash files with shellcheck.
shellcheck /home/hungptit/working/grpc-cmake-template/3p/build_using_cmake.sh /home/hungptit/working/grpc-cmake-template/3p/get_build_options.sh
touch .lint_shellcheck_stamp
[ 10%] Lint Bash and CMake files.
make[2]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
[ 10%] Built target lint
make  -f proto/CMakeFiles/address.dir/build.make proto/CMakeFiles/address.dir/depend
make[2]: Entering directory '/home/hungptit/working/grpc-cmake-template'
[ 15%] Running python protocol buffer compiler on addressbook.proto
cd /home/hungptit/working/grpc-cmake-template/proto && ../3p/bin/protoc-3.13.0.0 --python_out /home/hungptit/working/grpc-cmake-template/proto -I /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/addressbook.proto
[ 21%] Running grpc protocol buffer compiler on address.proto
cd /home/hungptit/working/grpc-cmake-template/proto && ../3p/bin/protoc-3.13.0.0 --grpc_out /home/hungptit/working/grpc-cmake-template/proto --plugin=protoc-gen-grpc=/home/hungptit/working/grpc-cmake-template/3p/bin/grpc_cpp_plugin -I /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/address.proto
[ 26%] Running cpp protocol buffer compiler on address.proto
cd /home/hungptit/working/grpc-cmake-template/proto && ../3p/bin/protoc-3.13.0.0 --cpp_out /home/hungptit/working/grpc-cmake-template/proto -I /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/address.proto
[ 31%] Running grpc protocol buffer compiler on address.proto
cd /home/hungptit/working/grpc-cmake-template/proto && ../3p/bin/protoc-3.13.0.0 --grpc_out /home/hungptit/working/grpc-cmake-template/proto --plugin=protoc-gen-grpc=/home/hungptit/working/grpc-cmake-template/3p/bin/grpc_python_plugin -I /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/address.proto
[ 36%] Running python protocol buffer compiler on address.proto
cd /home/hungptit/working/grpc-cmake-template/proto && ../3p/bin/protoc-3.13.0.0 --python_out /home/hungptit/working/grpc-cmake-template/proto -I /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/address.proto
[ 42%] Running grpc protocol buffer compiler on addressbook.proto
cd /home/hungptit/working/grpc-cmake-template/proto && ../3p/bin/protoc-3.13.0.0 --grpc_out /home/hungptit/working/grpc-cmake-template/proto --plugin=protoc-gen-grpc=/home/hungptit/working/grpc-cmake-template/3p/bin/grpc_cpp_plugin -I /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/addressbook.proto
[ 47%] Running cpp protocol buffer compiler on addressbook.proto
cd /home/hungptit/working/grpc-cmake-template/proto && ../3p/bin/protoc-3.13.0.0 --cpp_out /home/hungptit/working/grpc-cmake-template/proto -I /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/addressbook.proto
[ 52%] Running grpc protocol buffer compiler on addressbook.proto
cd /home/hungptit/working/grpc-cmake-template/proto && ../3p/bin/protoc-3.13.0.0 --grpc_out /home/hungptit/working/grpc-cmake-template/proto --plugin=protoc-gen-grpc=/home/hungptit/working/grpc-cmake-template/3p/bin/grpc_python_plugin -I /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/addressbook.proto
cd /home/hungptit/working/grpc-cmake-template && /home/hungptit/working/centos/bin/cmake -E cmake_depends "Unix Makefiles" /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template/proto /home/hungptit/working/grpc-cmake-template/proto/CMakeFiles/address.dir/DependInfo.cmake --color=
Scanning dependencies of target address
make[2]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
make  -f proto/CMakeFiles/address.dir/build.make proto/CMakeFiles/address.dir/build
make[2]: Entering directory '/home/hungptit/working/grpc-cmake-template'
[ 57%] Building CXX object proto/CMakeFiles/address.dir/address.pb.cc.o
cd /home/hungptit/working/grpc-cmake-template/proto && /home/hungptit/working/centos/bin/clang++ -DCARES_STATICLIB -I/home/hungptit/working/grpc-cmake-template -I/home/hungptit/working/grpc-cmake-template/proto -isystem /home/hungptit/working/grpc-cmake-template/3p/include -O3 -DNDEBUG -Wall -Wextra -pedantic -Werror -static -std=gnu++17 -o CMakeFiles/address.dir/address.pb.cc.o -c /home/hungptit/working/grpc-cmake-template/proto/address.pb.cc
[ 63%] Building CXX object proto/CMakeFiles/address.dir/addressbook.pb.cc.o
cd /home/hungptit/working/grpc-cmake-template/proto && /home/hungptit/working/centos/bin/clang++ -DCARES_STATICLIB -I/home/hungptit/working/grpc-cmake-template -I/home/hungptit/working/grpc-cmake-template/proto -isystem /home/hungptit/working/grpc-cmake-template/3p/include -O3 -DNDEBUG -Wall -Wextra -pedantic -Werror -static -std=gnu++17 -o CMakeFiles/address.dir/addressbook.pb.cc.o -c /home/hungptit/working/grpc-cmake-template/proto/addressbook.pb.cc
[ 68%] Building CXX object proto/CMakeFiles/address.dir/address.grpc.pb.cc.o
cd /home/hungptit/working/grpc-cmake-template/proto && /home/hungptit/working/centos/bin/clang++ -DCARES_STATICLIB -I/home/hungptit/working/grpc-cmake-template -I/home/hungptit/working/grpc-cmake-template/proto -isystem /home/hungptit/working/grpc-cmake-template/3p/include -O3 -DNDEBUG -Wall -Wextra -pedantic -Werror -static -std=gnu++17 -o CMakeFiles/address.dir/address.grpc.pb.cc.o -c /home/hungptit/working/grpc-cmake-template/proto/address.grpc.pb.cc
[ 73%] Building CXX object proto/CMakeFiles/address.dir/addressbook.grpc.pb.cc.o
cd /home/hungptit/working/grpc-cmake-template/proto && /home/hungptit/working/centos/bin/clang++ -DCARES_STATICLIB -I/home/hungptit/working/grpc-cmake-template -I/home/hungptit/working/grpc-cmake-template/proto -isystem /home/hungptit/working/grpc-cmake-template/3p/include -O3 -DNDEBUG -Wall -Wextra -pedantic -Werror -static -std=gnu++17 -o CMakeFiles/address.dir/addressbook.grpc.pb.cc.o -c /home/hungptit/working/grpc-cmake-template/proto/addressbook.grpc.pb.cc
[ 78%] Linking CXX static library libaddress.a
cd /home/hungptit/working/grpc-cmake-template/proto && /home/hungptit/working/centos/bin/cmake -P CMakeFiles/address.dir/cmake_clean_target.cmake
cd /home/hungptit/working/grpc-cmake-template/proto && /home/hungptit/working/centos/bin/cmake -E cmake_link_script CMakeFiles/address.dir/link.txt --verbose=1
/usr/bin/ar qc libaddress.a CMakeFiles/address.dir/address.pb.cc.o CMakeFiles/address.dir/addressbook.pb.cc.o CMakeFiles/address.dir/address.grpc.pb.cc.o CMakeFiles/address.dir/addressbook.grpc.pb.cc.o
/usr/bin/ranlib libaddress.a
make[2]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
[ 78%] Built target address
make  -f client/CMakeFiles/grpc-client.dir/build.make client/CMakeFiles/grpc-client.dir/depend
make[2]: Entering directory '/home/hungptit/working/grpc-cmake-template'
cd /home/hungptit/working/grpc-cmake-template && /home/hungptit/working/centos/bin/cmake -E cmake_depends "Unix Makefiles" /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template/client /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template/client /home/hungptit/working/grpc-cmake-template/client/CMakeFiles/grpc-client.dir/DependInfo.cmake --color=
Scanning dependencies of target grpc-client
make[2]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
make  -f client/CMakeFiles/grpc-client.dir/build.make client/CMakeFiles/grpc-client.dir/build
make[2]: Entering directory '/home/hungptit/working/grpc-cmake-template'
[ 84%] Building CXX object client/CMakeFiles/grpc-client.dir/grpc-client.cpp.o
cd /home/hungptit/working/grpc-cmake-template/client && /home/hungptit/working/centos/bin/clang++ -DCARES_STATICLIB -I/home/hungptit/working/grpc-cmake-template -I/home/hungptit/working/grpc-cmake-template/proto -isystem /home/hungptit/working/grpc-cmake-template/3p/include -O3 -DNDEBUG -Wall -Wextra -pedantic -Werror -static -std=gnu++17 -o CMakeFiles/grpc-client.dir/grpc-client.cpp.o -c /home/hungptit/working/grpc-cmake-template/client/grpc-client.cpp
[ 89%] Linking CXX executable grpc-client
cd /home/hungptit/working/grpc-cmake-template/client && /home/hungptit/working/centos/bin/cmake -E cmake_link_script CMakeFiles/grpc-client.dir/link.txt --verbose=1
/home/hungptit/working/centos/bin/clang++ -O3 -DNDEBUG CMakeFiles/grpc-client.dir/grpc-client.cpp.o -o grpc-client  ../proto/libaddress.a ../3p/lib/libgrpc++.a ../3p/lib64/libprotobuf.a ../3p/lib/libgrpc.a ../3p/lib/libssl.a ../3p/lib/libcrypto.a ../3p/lib/libz.a ../3p/lib/libcares.a -lnsl ../3p/lib/libre2.a ../3p/lib/libabsl_statusor.a ../3p/lib/libabsl_hash.a ../3p/lib/libabsl_bad_variant_access.a ../3p/lib/libabsl_city.a ../3p/lib/libabsl_raw_hash_set.a ../3p/lib/libabsl_hashtablez_sampler.a ../3p/lib/libabsl_exponential_biased.a ../3p/lib/libaddress_sorting.a ../3p/lib/libupb.a ../3p/lib/libgpr.a -ldl -lrt -lm -lpthread ../3p/lib/libabsl_status.a ../3p/lib/libabsl_cord.a ../3p/lib/libabsl_bad_optional_access.a ../3p/lib/libabsl_synchronization.a ../3p/lib/libabsl_stacktrace.a ../3p/lib/libabsl_symbolize.a ../3p/lib/libabsl_debugging_internal.a ../3p/lib/libabsl_demangle_internal.a ../3p/lib/libabsl_graphcycles_internal.a ../3p/lib/libabsl_time.a ../3p/lib/libabsl_civil_time.a ../3p/lib/libabsl_time_zone.a ../3p/lib/libabsl_malloc_internal.a ../3p/lib/libabsl_str_format_internal.a ../3p/lib/libabsl_strings.a ../3p/lib/libabsl_strings_internal.a ../3p/lib/libabsl_int128.a ../3p/lib/libabsl_throw_delegate.a ../3p/lib/libabsl_base.a ../3p/lib/libabsl_raw_logging_internal.a -lpthread ../3p/lib/libabsl_log_severity.a ../3p/lib/libabsl_spinlock_wait.a -lrt
make[2]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
[ 89%] Built target grpc-client
make  -f server/CMakeFiles/grpc-server.dir/build.make server/CMakeFiles/grpc-server.dir/depend
make[2]: Entering directory '/home/hungptit/working/grpc-cmake-template'
cd /home/hungptit/working/grpc-cmake-template && /home/hungptit/working/centos/bin/cmake -E cmake_depends "Unix Makefiles" /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template/server /home/hungptit/working/grpc-cmake-template /home/hungptit/working/grpc-cmake-template/server /home/hungptit/working/grpc-cmake-template/server/CMakeFiles/grpc-server.dir/DependInfo.cmake --color=
Scanning dependencies of target grpc-server
make[2]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
make  -f server/CMakeFiles/grpc-server.dir/build.make server/CMakeFiles/grpc-server.dir/build
make[2]: Entering directory '/home/hungptit/working/grpc-cmake-template'
[ 94%] Building CXX object server/CMakeFiles/grpc-server.dir/grpc-server.cpp.o
cd /home/hungptit/working/grpc-cmake-template/server && /home/hungptit/working/centos/bin/clang++ -DCARES_STATICLIB -I/home/hungptit/working/grpc-cmake-template -I/home/hungptit/working/grpc-cmake-template/proto -isystem /home/hungptit/working/grpc-cmake-template/3p/include -O3 -DNDEBUG -Wall -Wextra -pedantic -Werror -static -std=gnu++17 -o CMakeFiles/grpc-server.dir/grpc-server.cpp.o -c /home/hungptit/working/grpc-cmake-template/server/grpc-server.cpp
[100%] Linking CXX executable grpc-server
cd /home/hungptit/working/grpc-cmake-template/server && /home/hungptit/working/centos/bin/cmake -E cmake_link_script CMakeFiles/grpc-server.dir/link.txt --verbose=1
/home/hungptit/working/centos/bin/clang++ -O3 -DNDEBUG CMakeFiles/grpc-server.dir/grpc-server.cpp.o -o grpc-server  ../proto/libaddress.a ../3p/lib/libgrpc++.a ../3p/lib64/libprotobuf.a ../3p/lib/libgrpc.a ../3p/lib/libssl.a ../3p/lib/libcrypto.a ../3p/lib/libz.a ../3p/lib/libcares.a -lnsl ../3p/lib/libre2.a ../3p/lib/libabsl_statusor.a ../3p/lib/libabsl_hash.a ../3p/lib/libabsl_bad_variant_access.a ../3p/lib/libabsl_city.a ../3p/lib/libabsl_raw_hash_set.a ../3p/lib/libabsl_hashtablez_sampler.a ../3p/lib/libabsl_exponential_biased.a ../3p/lib/libaddress_sorting.a ../3p/lib/libupb.a ../3p/lib/libgpr.a -ldl -lrt -lm -lpthread ../3p/lib/libabsl_status.a ../3p/lib/libabsl_cord.a ../3p/lib/libabsl_bad_optional_access.a ../3p/lib/libabsl_synchronization.a ../3p/lib/libabsl_stacktrace.a ../3p/lib/libabsl_symbolize.a ../3p/lib/libabsl_debugging_internal.a ../3p/lib/libabsl_demangle_internal.a ../3p/lib/libabsl_graphcycles_internal.a ../3p/lib/libabsl_time.a ../3p/lib/libabsl_civil_time.a ../3p/lib/libabsl_time_zone.a ../3p/lib/libabsl_malloc_internal.a ../3p/lib/libabsl_str_format_internal.a ../3p/lib/libabsl_strings.a ../3p/lib/libabsl_strings_internal.a ../3p/lib/libabsl_int128.a ../3p/lib/libabsl_throw_delegate.a ../3p/lib/libabsl_base.a ../3p/lib/libabsl_raw_logging_internal.a -lpthread ../3p/lib/libabsl_log_severity.a ../3p/lib/libabsl_spinlock_wait.a -lrt
make[2]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
[100%] Built target grpc-server
make[1]: Leaving directory '/home/hungptit/working/grpc-cmake-template'
/home/hungptit/working/centos/bin/cmake -E cmake_progress_start /home/hungptit/working/grpc-cmake-template/CMakeFiles 0
```

## Windows ##

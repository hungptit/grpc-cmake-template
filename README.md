# Introduction #

This repository is a CMake template for my C++ projects that use [gRPC](https://github.com/grpc/grpc). 

Below are main gRPC features that are used in the examples:
1. Making a gRPC request from the client.
2. Handling handle client requests at the grpc server
3. Setting the deadline when making a request.
4. Monitoring the gRPC server status using the health check.

# Build instruction #

**Note: This instruction assumes there is a recent C++ toolchain in the build machine.**

## macOS and Linux ##

### Build gRPC ###

Run below command at the root level of the project to build [grpc](https://github.com/grpc/grpc) and all examples

``` shell
./build_all.sh
```

### Build all examples ###

Try below steps if you want to build all examples assuming the [grpc](https://github.com/grpc/grpc) libraries have already installed in the **3p** folder.

``` shell
cmake ./
make -k
```

**Compile all examples using clang++ **

``` shell
cmake ./ -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
make -k
```

**Compile all examples using the address sanitizer**

``` shell
cmake ./ -DCMAKE_BUILD_TYPE=Debug -DUSE_SANITIZER=address
make -k
```

**Compile all examples using the thread sanitizer**

``` shell
cmake ./ -DCMAKE_BUILD_TYPE=Debug -DUSE_SANITIZER=thread
make -k
```

*Note: There are data race warning if the thread sanitizer is used.*


## Windows ##

Go to the root level of the template folder then execute below commands to build grpc and examples in `Release` mode assuming the Visual Studio version >= 14 installed.

``` powershell
./build_all.ps1 Release
```

Use below command to build the grpc libraries and examples in `Debug` mode

``` powershell
./build_all.ps1 Debug
```

Note: This template is built successfully using Visual Studio 14 2015 version 14.0.27522.0.

# FAQs #

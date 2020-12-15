# Introduction #

This repository is a CMake template for my C++ projects that use [gRPC](https://github.com/grpc/grpc). 

# Build instruction #

**Note: This instruction assumes there is a recent C++ toolchain in the build machine.**

## macOS and Linux ##

### Build gRPC ###

Run below command at the root level of the project to build [grpc](https://github.com/grpc/grpc) and all examples

``` shell
./build_all.sh
```

### Build client and server examples ###

Try below steps if you want to build the client and server examples without rebuilding the [grpc](https://github.com/grpc/grpc) libraries.

``` shell
cmake ./
make -k
```

Or you want to change the C++ compiler and build mode for the sample code

``` shell
cmake ./ -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release
make -k
```

## Windows ##

Go to the root level of the template folder then execute below commands to build grpc and examples in `Release` mode assuming the Visual Studio version >= 15 installed.

``` powershell
./build_all.ps1 Release
```

Use below command to build the grpc libraries and examples in `Debug` mode

``` powershell
./build_all.ps1 Debug
```

Note: This template is built successfully using Visual Studio 14 2015 version 14.0.27522.0.

# FAQs #

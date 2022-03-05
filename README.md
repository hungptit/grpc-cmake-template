# Introduction #

This repository has a template for a gRPC C++ CMake projects. 

# Build instruction #

**Note: This instruction assumes there is a LLVM toolchain and ccache is available in the build machine.**

## macOS and Linux ##

``` shell
./build_all.sh Release
```

## Windows ##

Go to the root level of the template folder then execute below commands to build grpc and examples in `Release` mode assuming the Visual Studio version >= 14 installed.

``` powershell
./build_all.ps1 Release
```

# FAQs #

# Known issues #

* grpc_cpp_plugin does not work with the shared library build.

param (
    [Parameter(Mandatory=$true)][ValidateSet('Release', 'Debug')]$config
)

& 'C:\Program Files\CMake\bin\cmake.exe' -G "Visual Studio 14 2015" -A x64 $grpc_path -DCMAKE_INSTALL_PREFIX="$PWD"
& 'C:\Program Files\CMake\bin\cmake.exe' --build . --config $config -- /maxcpucount
& 'C:\Program Files\CMake\bin\cmake.exe' --build . --config $config --target install


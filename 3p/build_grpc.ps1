param (
    [Parameter(Mandatory=$true)][ValidateSet('Release', 'Debug')]$config
)

cmake -G "Visual Studio 14 2015" -A x64 $grpc_path -DCMAKE_INSTALL_PREFIX="$PWD"
cmake --build . --config $config -- /maxcpucount
cmake --build . --config $config --target install


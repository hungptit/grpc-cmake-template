param (
    [Parameter(Mandatory=$true)][ValidateSet('Release', 'Debug')]$config
)

$root_path = Get-Location
$third_party_path = "$root_path\3p"
$grpc_path = "$third_party_path\src\grpc"

Write-Output "root_path: $root_path"
Write-Output "third_party_path: $third_party_path"
Write-Output "grpc_path: $grpc_path"

# Init grpc and its submodules
git submodule update --init
cd $grpc_path
git submodule update --init

# Build grpc
cmake -G "Visual Studio 14 2015 Win64" . -DABSL_ENABLE_INSTALL=OFF -DCMAKE_INSTALL_PREFIX="$third_party_path" -DgRPC_PROTOBUF_PACKAGE_TYPE=MODULE
cmake --build . --config $config -- /maxcpucount
cmake --build . --config $config --target install

# Build examples
cd $root_path
cmake -G "Visual Studio 14 2015 Win64" .
cmake --build . --config $config -- /maxcpucount


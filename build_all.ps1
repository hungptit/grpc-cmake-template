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
git submodule update --init --recursive

# Build grpc
cd $root_path
rm -rf build
mkdir build
cd build
cmake -G "Visual Studio 14 2015" -A x64 $grpc_path -DABSL_ENABLE_INSTALL=OFF -DCMAKE_INSTALL_PREFIX="$third_party_path" -DgRPC_PROTOBUF_PACKAGE_TYPE=module -DgRPC_PROTOBUF_PROVIDER=module
cmake --build . --config $config -- /maxcpucount
cmake --build . --config $config --target install
rm build                        # Cleanup the build directory.

# Build examples
cd $root_path
cmake -G "Visual Studio 14 2015"  -A x64 .
cmake --build . --config $config -- /maxcpucount


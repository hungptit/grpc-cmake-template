param (
    [Parameter(Mandatory=$true)][ValidateSet('Release', 'Debug')]$config
)

$root_dir = "$PWD"
$examples_dir = "$root_dir\examples"
$msvc_version = "Visual Studio 14 2015"

# Build gRPC libraries
Push-Location "$examples_dir"

git clean -df

# TODO: Update CMAKE_C_COMPILER and CMAKE_CXX_COMPILER using the local msvc.
cmake -G "$msvc_version" -A x64 "." -DCMAKE_CXX_STANDARD=17 -DSTEM="$config"
if ($LASTEXITCODE) {
    throw "Cannot configure smoke tests for a '${config}' build"
}

cmake --build . --config $config -- /maxcpucount
if ($LASTEXITCODE) {
    throw "Cannot build smoke tests for a '${config}' build"
}

Pop-Location

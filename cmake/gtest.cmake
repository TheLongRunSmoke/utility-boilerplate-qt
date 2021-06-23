# ----------------------------------
#
# Google Test include script.
#
# See https://github.com/google/googletest
#
# ----------------------------------

# Let's start with including fetcher, to make possible to load code from external source.
include(FetchContent)
# Load Google Test source code. Use hash of HEAD commit on master branch.
FetchContent_Declare(googletest URL https://github.com/google/googletest/archive/355d57d90d9744c41ac7c99f1e960778f1c63040.zip)
# Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt
    ON
    CACHE BOOL "" FORCE
)
# Include library to build environment and enable CTest support.
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

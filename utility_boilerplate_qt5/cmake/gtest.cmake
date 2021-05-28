#----------------------------------
#
#   Google Test include script.
#
#   See https://github.com/google/googletest
#
#----------------------------------

# Let's start with including fetcher, to make possible to load code from external source.
include(FetchContent)
# Load Google Test source code. Use hash of HEAD commit on master branch.
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/a3460d1aeeaa43fdf137a6adefef10ba0b59fe4b.zip
)
# Prevent overriding the parent project's compiler/linker settings.
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
# Include library to build environment and enable test support.
FetchContent_MakeAvailable(googletest)
enable_testing()
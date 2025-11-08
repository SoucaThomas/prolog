# Fetch GoogleTest
include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.14.0
)
FetchContent_MakeAvailable(googletest)

# Add tests
add_executable(PrologTests
    unifier_test.cpp
)
target_include_directories(PrologTests PRIVATE ../include)
target_link_libraries(PrologTests gtest gtest_main)

# Register tests
add_test(NAME PrologTests COMMAND PrologTests)
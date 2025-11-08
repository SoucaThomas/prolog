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
    term_test.cpp
    rule_test.cpp
    knowledgeBase_test.cpp
    utils_test.cpp
    unifier_test.cpp
)

target_include_directories(PrologTests PRIVATE ../include)
target_link_libraries(PrologTests 
    gtest 
    gtest_main
)

# Link source files needed for tests
target_sources(PrologTests PRIVATE
    ../src/term.cpp
    ../src/rule.cpp
    ../src/knowledgeBase.cpp
    ../src/utils.cpp
    ../src/unifier.cpp
)

# Register tests
add_test(NAME PrologTests COMMAND PrologTests)
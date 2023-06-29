FetchContent_Declare(
    googletest

    # GIT_REPOSITORY https://github.com/google/googletest.git
    URL https://github.com/google/googletest/archive/refs/tags/v1.13.0.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(treeceratops_test
    test.cpp
)

target_compile_features(treeceratops_test PRIVATE cxx_std_20)
target_link_libraries(treeceratops_test PRIVATE treeceratops GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(treeceratops_test)
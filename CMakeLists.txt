cmake_minimum_required(VERSION 3.22)

project(ImmerBench)
set(CMAKE_CXX_STANDARD 20)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

include(FetchContent)

FetchContent_Declare(immer GIT_REPOSITORY https://github.com/arximboldi/immer.git)
FetchContent_Declare(abseil GIT_REPOSITORY https://github.com/abseil/abseil-cpp.git)


set(immer_BUILD_TESTS OFF)
set(immer_BUILD_EXAMPLES OFF)
set(immer_BUILD_DOCS OFF)
set(immer_BUILD_EXTRAS OFF)
set(immer_INSTALL_FUZZERS OFF)

FetchContent_Populate(immer)
FetchContent_MakeAvailable(abseil)

include_directories(${immer_SOURCE_DIR})
# include_directories(${abseil_SOURCE_DIR})

add_executable(main Main.cpp)
target_link_libraries(main PRIVATE absl::flat_hash_map)

add_executable(test Test.cpp)

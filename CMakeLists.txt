cmake_minimum_required(VERSION 3.25)

project(app)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(FetchContent)

FetchContent_Declare(
  consolecolors
  GIT_REPOSITORY https://github.com/kubsnn/ConsoleColors.git
)
FetchContent_MakeAvailable(consolecolors)
FetchContent_GetProperties(consolecolors)
if(NOT consolecolors_POPULATED)
  FetchContent_Populate(consolecolors)
endif()
include_directories(${consolecolors_SOURCE_DIR}/include)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/kubsnn/json.git
)
FetchContent_MakeAvailable(json)
FetchContent_GetProperties(json)
if(NOT json_POPULATED)
  FetchContent_Populate(json)
endif()
include_directories(${json_SOURCE_DIR}/include)

find_package(Boost REQUIRED COMPONENTS system)

include_directories(${Boost_INCLUDE_DIRS})

include_directories(src)

add_subdirectory(src)
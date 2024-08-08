cmake_minimum_required(VERSION 3.25)

project(mochi VERSION 0.1.0)

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

add_subdirectory(src)

include_directories(include)

add_subdirectory(ut)

# Configure a Config file for find_package
include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/MochiConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY AnyNewerVersion
)

configure_file(CMakeModules/MochiConfig.cmake
        "${CMAKE_CURRENT_BINARY_DIR}/MochiConfig.cmake"
        COPYONLY
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/MochiConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/MochiConfigVersion.cmake"
        DESTINATION lib/cmake/mochi
)


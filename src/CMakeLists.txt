add_library(mochi_lib STATIC
        controller_base.cpp
        http/http_server.cpp
        http/http_session.cpp
        http/web_app_builder.cpp)

target_include_directories(mochi_lib PUBLIC
        ${Boost_INCLUDE_DIRS}
        ${consolecolors_SOURCE_DIR}/include
        ${json_SOURCE_DIR}/include)
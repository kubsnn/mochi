add_subdirectory(services)
add_subdirectory(controllers)
add_subdirectory(core)
#add_subdirectory(models)

add_executable(app main.cpp)

target_link_libraries(app PRIVATE
        ${Boost_LIBRARIES}
        services_lib
        core_lib
        controllers_lib)
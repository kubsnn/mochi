add_library(controllers_lib STATIC
        device_controller.cpp
        test_controller.cpp)

target_link_libraries(controllers_lib PRIVATE services_lib)
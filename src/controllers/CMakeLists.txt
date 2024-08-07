add_library(controllers_lib STATIC
        DeviceController.cpp
        TestController.cpp)

target_link_libraries(controllers_lib PRIVATE services_lib)